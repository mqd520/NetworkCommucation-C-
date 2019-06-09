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

		bool b = vecListenSocket.size() == 0;

		m_lock1.Unlock();

		return b;
	}

	void CSelect::AddSocket(SOCKET socket, int type)
	{
		m_lock1.Lock();

		vecListenSocket.push_back({ socket, type });

		m_lock1.Unlock();
	}

	void CSelect::RemoveSocket(SOCKET socket, bool close/* = true*/)
	{
		m_lock1.Lock();

		for (vector<SelectSocketData>::iterator it = vecListenSocket.begin(); it != vecListenSocket.end(); it++)
		{
			if (it->socket == socket)
			{
				vecListenSocket.erase(it);
				RemoveProcessingSocket(socket);	// �Ƴ����ڴ����socket
				
				if (close)
				{
					SocketTool::ShutDown(socket, false);
					SocketTool::CloseSocket(socket, false);
				}

				break;
			}
		}

		m_lock1.Unlock();
	}

	void CSelect::Select()
	{
		//Sleep(1 * 1000);	// ����ʱʹ��,������,��ע�͵�

		if (CTcpCommuMgr::IsExited())	// ָʾ��Ҫ�˳���
		{
			return;	// ���̷���
		}

		CalcSocketGroup();	// ��socket���з���

		if (groupSocket.size() > 0)
		{
			// �������鼯��
			for (int i = 0; i < (int)groupSocket.size(); i++)
			{
				FD_ZERO(&fsRead);
				FD_ZERO(&fsExcept);

				// ��������,��socket�ֱ�����쳣���ϺͶ�д����
				for (int j = 0; j < (int)groupSocket[i].size(); j++)
				{
					FD_SET(groupSocket[i][j].socket, &fsRead);
					FD_SET(groupSocket[i][j].socket, &fsExcept);
				}

				SocketTool::Select(0, &fsRead, NULL, &fsExcept, &m_selectTimeout);

				// ���socket��"�쳣"�ź�
				if (fsExcept.fd_count > 0)
				{
					for (int k = 0; k < (int)groupSocket[i].size(); k++)
					{
						if (CTcpCommuMgr::IsExited())	// ָʾ��Ҫ�˳���
						{
							return;	//���̷���, ���ٴ������Ķ���
						}
						CheckSocketExcept(groupSocket[i][k]);
					}
				}

				// ���socket��"�ɶ�"�ź�
				if (fsRead.fd_count > 0)
				{
					for (int k = 0; k < (int)groupSocket[i].size(); k++)
					{
						if (CTcpCommuMgr::IsExited())	// ָʾ��Ҫ�˳���
						{
							return;	//���̷���, ���ٴ������Ķ���
						}
						CheckSocketCanRead(groupSocket[i][k]);
					}
				}
			}
		}
	}

	void CSelect::CalcSocketGroup()
	{
		m_lock1.Lock();

		groupSocket.clear();
		int nSocketCount = (int)vecListenSocket.size();	// socket����
		int nGroupCount = nSocketCount / FD_SETSIZE + (nSocketCount % FD_SETSIZE == 0 ? 0 : 1);	// ������
		for (int i = 0; i < nGroupCount; i++)
		{
			vector<SelectSocketData> vec;
			groupSocket.push_back(vec);
		}

		//��������socket
		for (int i = 0; i < nSocketCount; i++)
		{
			int groupIndex = (i + 1) / FD_SETSIZE + ((i + 1) % FD_SETSIZE == 0 ? 0 : 1) - 1;	// ���㵱ǰsocket���ڷ�������
			groupSocket[groupIndex].push_back(vecListenSocket[i]);	// ��socket�����Ӧ������
		}

		m_lock1.Unlock();
	}

	bool CSelect::IsProcessingSingal(SOCKET socket, int type)
	{
		m_lock2.Lock();

		bool b = false;	// ָʾ��ǰsocket�ź��Ƿ����ڱ�����
		for (int i = 0; i < (int)vecProcessingSocketData.size(); i++)
		{
			if (vecProcessingSocketData[i].socket == socket && vecProcessingSocketData[i].type == type)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			// ��ǵ�ǰsocket�ź����ڱ�����
			vecProcessingSocketData.push_back({ socket, type });
		}

		m_lock2.Unlock();

		return b;
	}

	void CSelect::CheckSocketExcept(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &fsExcept);
		if (result > 0)
		{
			// ���socket�쳣�ź��Ƿ����ڱ�����
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Except))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Except, socketData.type };
				CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
			}
		}
	}

	void CSelect::CheckSocketCanRead(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &fsRead);
		if (result > 0)
		{
			// ���socket�ɶ��ź��Ƿ����ڱ�����
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Read))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Read, socketData.type };
				if (socketData.type == ESocketType::Accept)	// ָʾsocket���ڽ���������
				{
					CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
				}
				else if (socketData.type == ESocketType::SendRecvData)	// ָʾsocket���ڶ�д����
				{
					CTcpCommuMgr::GetRecvDataSingal()->PushSocket(data);
				}
			}
		}
	}

	void CSelect::CheckSocketCanWrite(SelectSocketData socketData)
	{
		int result = FD_ISSET(socketData.socket, &fsWrite);
		if (result > 0)
		{
			// ���socket�ɶ��ź��Ƿ����ڱ�����
			if (!IsProcessingSingal(socketData.socket, ESocketSingalType::Write))
			{
				SocketSingalData data = { socketData.socket, ESocketSingalType::Write, socketData.type };
				if (socketData.type == ESocketType::SendRecvData)	// ָʾsocket���ڶ�д����
				{
					CTcpCommuMgr::GetSendDataSingal()->PushSocket(data);
				}
				else if (socketData.type == ESocketType::Connect)		// ָʾsocket�������ӷ����
				{
					CTcpCommuMgr::GetOtherSingal()->PushSocket(data);
				}
			}
		}
	}

	void CSelect::OnProcessingSocketCmp(SOCKET socket, int type)
	{
		m_lock2.Lock();

		for (vector<ProcessingSocketData>::iterator it = vecProcessingSocketData.begin(); it < vecProcessingSocketData.end(); it++)
		{
			if (it->socket == socket && it->type == type)
			{
				vecProcessingSocketData.erase(it);
				break;
			}
		}

		m_lock2.Unlock();
	}

	void CSelect::RemoveProcessingSocket(SOCKET socket)
	{
		m_lock2.Lock();

		for (vector<ProcessingSocketData>::iterator it = vecProcessingSocketData.begin(); it != vecProcessingSocketData.end();)
		{
			if (it->socket == socket)
			{
				it = vecProcessingSocketData.erase(it);
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
		// �ر�����socket
		for (int i = 0; i < (int)vecListenSocket.size(); i++)
		{
			SocketTool::ShutDown(vecListenSocket[i].socket, false);
			SocketTool::CloseSocket(vecListenSocket[i].socket, false);
		}
	}
}