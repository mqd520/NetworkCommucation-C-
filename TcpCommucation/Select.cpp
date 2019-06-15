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
		//Sleep(1 * 1000);	// 调试时使用,无意义,可注释掉

		if (TcpCommu::IsExited())	// 指示需要退出了
		{
			return;	// 立刻返回
		}

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

				timeval t = { 0, 0 };
				SocketTool::Select(0, &fsRead, NULL, &fsExcept, &t);

				// 检查socket的"异常"信号
				if (fsExcept.fd_count > 0)
				{
					for (int k = 0; k < (int)vecGroupSocket[i].size(); k++)
					{
						processSocketExcept(vecGroupSocket[i][k], fsExcept);
					}
				}

				// 检查socket的"可读"信号
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
		int nSocketCount = (int)vec.size();	// socket总数
		int nGroupCount = nSocketCount / FD_SETSIZE + (nSocketCount % FD_SETSIZE == 0 ? 0 : 1);	// 分组数
		for (int i = 0; i < nGroupCount; i++)
		{
			vector<SelectSocketData> vec1;
			vecGroupSocket.push_back(vec1);
		}

		//遍历所有socket
		for (int i = 0; i < nSocketCount; i++)
		{
			int groupIndex = (i + 1) / FD_SETSIZE + ((i + 1) % FD_SETSIZE == 0 ? 0 : 1) - 1;	// 计算当前socket所在分组索引
			vecGroupSocket[groupIndex].push_back(vec[i]);	// 将socket填入对应的组中
		}
	}

	bool Select::IsProcessingSingal(SOCKET socket, ESocketSingalType type)
	{
		lock2.Lock();

		bool b = false;	// 指示当前socket信号是否正在被处理
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
			// 标记当前socket信号正在被处理
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