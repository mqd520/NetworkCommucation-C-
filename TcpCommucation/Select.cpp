#include "stdafx.h"
#include "Select.h"
#include "Include/tc/SocketTool.h"
#include "Include/tc/TcpCommuMgr.h"
#include "RecvNewConnSocEvt.h"
#include "RecvPeerDataSocEvt.h"
#include "ConnDisconnSocEvt.h"

namespace tc
{
	Select::Select()
	{

	}

	Select::~Select()
	{

	}

	void Select::QuerySingal(vector<SocketInfoData>& vec)
	{
		//Sleep(1 * 1000);	// 调试时使用,无意义,可注释掉

		CalcSocketGroup(vec);	// 对socket进行分组

		if (vecGroupSocket.size() > 0)
		{
			fd_set fsRead = { 0 };
			fd_set fsExcept = { 0 };

			// 遍历分组集合
			for (int i = 0; i < (int)vecGroupSocket.size(); i++)
			{
				FD_ZERO(&fsRead);
				FD_ZERO(&fsExcept);

				// 遍历分组, 将socket分别加入异常集合和可读集合
				for (int j = 0; j < (int)vecGroupSocket[i].size(); j++)
				{
					FD_SET(vecGroupSocket[i][j].socket, &fsRead);
					FD_SET(vecGroupSocket[i][j].socket, &fsExcept);
				}

				timeval t = { 0, 10 };
				int ret = SocketTool::Select(0, &fsRead, NULL, &fsExcept, &t);

				if (ret > 0)
				{
					bool b1 = fsExcept.fd_count > 0;	// 是否有异常信号
					bool b2 = fsRead.fd_count > 0;		// 是否有可读信号
					for (int k = 0; k < (int)vecGroupSocket[i].size(); k++)
					{
						if (b1)
						{
							OnSocketExcept(vecGroupSocket[i][k], fsExcept);
						}
						if (b2)
						{
							OnSocketRead(vecGroupSocket[i][k], fsRead);
						}
					}
				}
			}
		}
	}

	void Select::CalcSocketGroup(vector<SocketInfoData>& vec)
	{
		vecGroupSocket.clear();
		int nSocketCount = (int)vec.size();	// socket总数
		int nGroupCount = nSocketCount / FD_SETSIZE + (nSocketCount % FD_SETSIZE == 0 ? 0 : 1);	// 分组数
		for (int i = 0; i < nGroupCount; i++)
		{
			vector<SocketInfoData> vec1;
			vecGroupSocket.push_back(vec1);
		}

		//遍历所有socket
		for (int i = 0; i < nSocketCount; i++)
		{
			int groupIndex = (i + 1) / FD_SETSIZE + ((i + 1) % FD_SETSIZE == 0 ? 0 : 1) - 1;	// 计算当前socket所在分组索引
			vecGroupSocket[groupIndex].push_back(vec[i]);	// 将socket填入对应的组中
		}
	}

	void Select::OnSocketExcept(SocketInfoData& socketData, fd_set& fs)
	{
		int result = FD_ISSET(socketData.socket, &fs);
		if (result > 0)
		{

		}
	}

	void Select::OnSocketRead(SocketInfoData& socketData, fd_set& fs)
	{
		int result = FD_ISSET(socketData.socket, &fs);
		if (result > 0)
		{
			char ch[50] = { 0 };
			sprintf_s(ch, "process socket readable singal: %d", socketData.socket);
			OutputDebugStringA(ch);
			OutputDebugStringA("\n");

			if (socketData.type == ESocketType::Accept)
			{
				OnRecvNewConn(socketData);
			}
			else if (socketData.type == ESocketType::SendRecvData)
			{
				OnRecvData(socketData);
			}
		}
	}

	void Select::OnRecvNewConn(SocketInfoData& socketData)
	{
		vector<SOCKET> clients;

		while (true)
		{
			SOCKET client = SocketTool::Accept(socketData.socket, socketData.localIP, socketData.localPort, false);
			if (client != INVALID_SOCKET)
			{
				clients.push_back(client);
			}
			else
			{
				break;
			}
		}

		if (!clients.empty())
		{
			RecvNewConnSocEvt* pEvt = new RecvNewConnSocEvt(socketData.socket, clients);
			TcpCommu::GetRecvHandler()->PushSocketEvt(pEvt);
		}
	}

	void Select::OnRecvData(SocketInfoData& socketData)
	{
		BYTE* pRecvBuf = new BYTE[TC_TCPRECVBUFFERSIZE];
		int len = 0;

		bool b = SocketTool::Recv(socketData.socket, pRecvBuf, TC_TCPRECVBUFFERSIZE, &len);
		if (len > 0)	// 接收数据成功
		{
			RecvPeerDataSocEvt* pEvt = new RecvPeerDataSocEvt(socketData.socket, pRecvBuf, len);
			TcpCommu::GetRecvHandler()->PushSocketEvt(pEvt);
		}
		else   // 接收数据失败
		{
			delete pRecvBuf;

			if (!b)	// 指示连接已断开, 应该关闭socket
			{
				ConnDisconnSocEvt* pEvt = new ConnDisconnSocEvt(socketData.socket);
				TcpCommu::GetRecvHandler()->PushSocketEvt(pEvt);
			}
		}
	}
}