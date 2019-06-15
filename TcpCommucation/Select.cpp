#include "stdafx.h"
#include "Select.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Def.h"
#include "Common.h"

namespace tc
{
	Select::Select()
	{

	}

	Select::~Select()
	{

	}

	void Select::QuerySingal(vector<SelectSocketData>& vec)
	{
		//Sleep(1 * 1000);	// ����ʱʹ��,������,��ע�͵�

		if (TcpCommu::IsExited())	// ָʾ��Ҫ�˳���
		{
			return;	// ���̷���
		}

		CalcSocketGroup(vec);	// ��socket���з���

		if (vecGroupSocket.size() > 0)
		{
			fd_set fsRead = { 0 };
			fd_set fsExcept = { 0 };

			// �������鼯��
			for (int i = 0; i < (int)vecGroupSocket.size(); i++)
			{
				FD_ZERO(&fsRead);
				FD_ZERO(&fsExcept);

				// ��������, ��socket�ֱ�����쳣���ϺͿɶ�����
				for (int j = 0; j < (int)vecGroupSocket[i].size(); j++)
				{
					FD_SET(vecGroupSocket[i][j].socket, &fsRead);
					FD_SET(vecGroupSocket[i][j].socket, &fsExcept);
				}

				timeval t = { 0, 0 };
				SocketTool::Select(0, &fsRead, NULL, &fsExcept, &t);

				// ���socket��"�쳣"�ź�
				if (fsExcept.fd_count > 0)
				{
					for (int k = 0; k < (int)vecGroupSocket[i].size(); k++)
					{
						processSocketExcept(vecGroupSocket[i][k], fsExcept);
					}
				}

				// ���socket��"�ɶ�"�ź�
				if (fsRead.fd_count > 0)
				{
					for (int k = 0; k < (int)vecGroupSocket[i].size(); k++)
					{
						processSocketRead(vecGroupSocket[i][k], fsRead);
					}
				}
			}
		}
	}

	void Select::CalcSocketGroup(vector<SelectSocketData>& vec)
	{
		vecGroupSocket.clear();
		int nSocketCount = (int)vec.size();	// socket����
		int nGroupCount = nSocketCount / FD_SETSIZE + (nSocketCount % FD_SETSIZE == 0 ? 0 : 1);	// ������
		for (int i = 0; i < nGroupCount; i++)
		{
			vector<SelectSocketData> vec1;
			vecGroupSocket.push_back(vec1);
		}

		//��������socket
		for (int i = 0; i < nSocketCount; i++)
		{
			int groupIndex = (i + 1) / FD_SETSIZE + ((i + 1) % FD_SETSIZE == 0 ? 0 : 1) - 1;	// ���㵱ǰsocket���ڷ�������
			vecGroupSocket[groupIndex].push_back(vec[i]);	// ��socket�����Ӧ������
		}
	}

	bool Select::IsProcessingSingal(SOCKET socket, ESocketSingalType type)
	{
		lock2.Lock();

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

		lock2.Unlock();

		return b;
	}

	void Select::processSocketExcept(SelectSocketData socketData, fd_set& fs)
	{
		int result = FD_ISSET(socketData.socket, &fs);
		if (result > 0)
		{
			SocketSingalData data = { socketData.socket, ESocketSingalType::Except, socketData.type };
			TcpCommu::GetSelectSingal()->PushSocketSingal(data);
		}
	}

	void Select::processSocketRead(SelectSocketData socketData, fd_set& fs)
	{
		int result = FD_ISSET(socketData.socket, &fs);
		if (result > 0)
		{
			SocketSingalData data = { socketData.socket, ESocketSingalType::Read, socketData.type };
			TcpCommu::GetSelectSingal()->PushSocketSingal(data);
		}
	}

	void Select::Exit()
	{

	}
}