#pragma once
#pragma warning(disable:4996)

#include <string>
#include <WinSock2.h>

using namespace std;

namespace NetworkCommunication
{
	//************************************
	// Method:    ��ӡ��Ϣ
	// FullName:  NetworkCommunication::Printf
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: TCHAR * msg
	//************************************
	void Printf(TCHAR* msg);

	//************************************
	// Method:    ��ȡ����IP
	// FullName:  NetworkCommunication::GetLocalIP
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: TCHAR * ip
	//************************************
	bool GetLocalIP(TCHAR* ip);
}
