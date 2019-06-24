#pragma once

#include <string>

using namespace std;

// ��־����
enum class ELogType : int
{
	Info,	// ��Ϣ
	Debug,	// ����
	Error,	// ����
	Fatal,	// ���ش���

	None	// ��
};

// �ͻ���������Ϣ
typedef struct tagClientConnInfo
{
	string ip;			// ip
	int port;			// �˿�
	int clientId;		// client id
}ClientConnInfo;

