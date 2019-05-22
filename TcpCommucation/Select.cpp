#include "stdafx.h"
#include "Select.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Def.h"
#include "Common.h"

namespace tc
{
	CSelect::CSelect() :
		m_selectTimeout({ 0, 0 })
	{

	}

	CSelect::~CSelect()
	{

	}

	bool CSelect::IsEmpty()
	{
		m_lock1.Lock();

		bool b = m_vecSocket.size() == 0;

		m_lock1.Unlock();

		return b;
	}

	void CSelect::AddSocket(SOCKET socket, int type)
	{
		m_lock1.Lock();

		m_vecSocket.push_back({ socket, type });

		m_lock1.Unlock();
	}

	void CSelect::RemoveSocket(SOCKET socket, bool close/* = true*/)
	{
		m_lock1.Lock();

		for (vector<SelectSocketData>::iterator it = m_vecSocket.begin(); it != m_vecSocket.end(); it++)
		{
			if (it->socket == socket)
			{
				m_vecSocket.erase(it);
				if (close)
				{
					m_socketAPI.CloseSocket(socket);//�ر�socket
				}
				RemoveProcessingSocket(socket);//�Ƴ����ڴ����socket
				break;
			}
		}

		m_lock1.Unlock();
	}

	void CSelect::Select()
	{
		//Sleep(3 * 1000);	//����ʱʹ��,������,��ע�͵�

		if (CTcpCommuMgr::IsExited())	//ָʾ��Ҫ�˳���
		{
			return;	//���̷���
		}

		CalcSocketGroup();//��socket���з���

		if (m_group.size() > 0)
		{
			//�������鼯��
			for (int i = 0; i < (int)m_group.size(); i++)
			{
				FD_ZERO(&m_readFdSet);
				FD_ZERO(&m_writeFdSet);
				FD_ZERO(&m_exceptFdSet);

				//��������,��socket�ֱ�����쳣���ϺͶ�д����
				for (int j = 0; j < (int)m_group[i].size(); j++)
				{
					FD_SET(m_group[i][j].socket, &m_readFdSet);
					FD_SET(m_group[i][j].socket, &m_writeFdSet);
					FD_SET(m_group[i][j].socket, &m_exceptFdSet);
				}

				m_socketAPI.Select(0, &m_readFdSet, &m_writeFdSet, &m_exceptFdSet, &m_selectTimeout);

				//���socket��"�쳣"�ź�
				if (m_exceptFdSet.fd_count > 0)
				{
					for (int k = 0; k < (int)m_group[i].size(); k++)
					{
						if (CTcpCommuMgr::IsExited())//ָʾ��Ҫ�˳���
						{
							return;//���̷���,���ٴ������Ķ���
						}
						CheckSocketExcept(m_group[i][k]);
					}
				}

				//���socket��"�ɶ�"�ź�
				if (m_readFdSet.fd_count > 0)
				{
					for (int k = 0; k < (int)m_group[i].size(); k++)
					{
						if (CTcpCommuMgr::IsExited())//ָʾ��Ҫ�˳���
						{
							return;//���̷���,���ٴ������Ķ���
						}
						CheckSocketCanRead(m_group[i][k]);
					}
				}

				//���socket��"��д"�ź�
				if (m_writeFdSet.fd_count > 0)
				{
					for (int k = 0; k < (int)m_group[i].size(); k++)
					{
						if (CTcpCommuMgr::IsExited())//ָʾ��Ҫ�˳���
						{
							return;//���̷���,���ٴ������Ķ���
						}
						CheckSocketCanWrite(m_group[i][k]);
					}
				}
			}
		}
	}

	void CSelect::CalcSocketGroup()
	{
		m_lock1.Lock();

		m_group.clear();
		int nSocketCount = (int)m_vecSocket.size();//socket����
		int nGroupCount = nSocketCount / FD_SETSIZE + (nSocketCount % FD_SETSIZE == 0 ? 0 : 1);//������
		for (int i = 0; i < nGroupCount; i++)
		{
			vector<SelectSocketData> vec;
			m_group.push_back(vec);
		}

		//��������socket
		for (int i = 0; i < nSocketCount; i++)
		{
			int groupIndex = (i + 1) / FD_SETSIZE + ((i + 1) % FD_SETSIZE == 0 ? 0 : 1) - 1;//���㵱ǰsocket���ڷ�������
			m_group[groupIndex].push_back(m_vecSocket[i]);//��socket�����Ӧ������
		}

		m_lock1.Unlock();
	}

	bool CSelect::IsProcessingSingal(SOCKET socket, int type)
	{
		m_lock2.Lock();

		bool b = false;//ָʾ��ǰsocket�ź��Ƿ����ڱ�����
		for (int i = 0; i < (int)m_vecProcessingData.size(); i++)
		{
			if (m_vecProcessingData[i].socket == socket && m_vecProcessingData[i].type == type)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			//��ǵ�ǰsocket�ź����ڱ�����
			m_vecProcessingData.push_back({ socket, type });
		}

		m_lock2.Unlock();

		return b;
	}

	void CSelect::CheckSocketExcept(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &m_exceptFdSet);
		if (result > 0)
		{
			//���socket�쳣�ź��Ƿ����ڱ�����
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Except))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Except, socketData.type };
				CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
			}
		}
	}

	void CSelect::CheckSocketCanRead(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &m_readFdSet);
		if (result > 0)
		{
			//���socket�ɶ��ź��Ƿ����ڱ�����
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Read))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Read, socketData.type };
				if (socketData.type == ESelectSocketType::Accept)//ָʾsocket���ڽ���������
				{
					CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
				}
				else if (socketData.type == ESelectSocketType::ReadWriteData)//ָʾsocket���ڶ�д����
				{
					CTcpCommuMgr::GetRecvDataSingal()->PushSocket(data);
				}
			}
		}
	}

	void CSelect::CheckSocketCanWrite(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &m_writeFdSet);
		if (result > 0)
		{
			//���socket�ɶ��ź��Ƿ����ڱ�����
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Write))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Write, socketData.type };
				if (socketData.type == ESelectSocketType::ReadWriteData)//ָʾsocket���ڶ�д����
				{
					CTcpCommuMgr::GetSendDataSingal()->PushSocket(data);
				}
				else if (socketData.type == ESelectSocketType::Connect)//ָʾsocket�������ӷ����
				{
					CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
				}
			}
		}
	}

	void CSelect::OnProcessingSocketCmp(SOCKET socket, int type)
	{
		m_lock2.Lock();

		for (vector<ProcessingSocketData>::iterator it = m_vecProcessingData.begin(); it < m_vecProcessingData.end(); it++)
		{
			if (it->socket == socket && it->type == type)
			{
				m_vecProcessingData.erase(it);
				break;
			}
		}

		m_lock2.Unlock();
	}

	void CSelect::RemoveProcessingSocket(SOCKET socket)
	{
		m_lock2.Lock();

		for (vector<ProcessingSocketData>::iterator it = m_vecProcessingData.begin(); it != m_vecProcessingData.end();)
		{
			if (it->socket == socket)
			{
				it = m_vecProcessingData.erase(it);
			}
			else
			{
				it++;
			}
		}

		m_lock2.Unlock();
	}

	void CSelect::Exit()
	{
		//�ر�����socket
		for (int i = 0; i < (int)m_vecSocket.size(); i++)
		{
			m_socketAPI.CloseSocket(m_vecSocket[i].socket);
		}
	}
}