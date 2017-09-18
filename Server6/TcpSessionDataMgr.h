#pragma once
#include "Def.h"
#include <vector>

using namespace std;

//tcp会话数据管理
class CTcpDataSessionDataMgr
{
private:
	vector<TcpSessionData> m_vec;//tcp会话数据集合

public:
	CTcpDataSessionDataMgr();
	~CTcpDataSessionDataMgr();

	//************************************
	// Method:    增加一个tcp session数据
	// Returns:   返回新增加数据的索引
	// Parameter: tcp session数据
	//************************************
	int Push(TcpSessionData data);

	//************************************
	// Method:    获取指定索引的数据
	//************************************
	TcpSessionData GetDataByIndex(int index);

	//************************************
	// Method:    移除指定客户端的socket的tcp会话数据
	// Parameter: 客户端的socket
	//************************************
	int RemoveByClientSocket(SOCKET client);
};