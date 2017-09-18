#pragma once
#include "Def.h"
#include <vector>

using namespace std;

//tcp�Ự���ݹ���
class CTcpDataSessionDataMgr
{
private:
	vector<TcpSessionData> m_vec;//tcp�Ự���ݼ���

public:
	CTcpDataSessionDataMgr();
	~CTcpDataSessionDataMgr();

	//************************************
	// Method:    ����һ��tcp session����
	// Returns:   �������������ݵ�����
	// Parameter: tcp session����
	//************************************
	int Push(TcpSessionData data);

	//************************************
	// Method:    ��ȡָ������������
	//************************************
	TcpSessionData GetDataByIndex(int index);

	//************************************
	// Method:    �Ƴ�ָ���ͻ��˵�socket��tcp�Ự����
	// Parameter: �ͻ��˵�socket
	//************************************
	int RemoveByClientSocket(SOCKET client);
};