#pragma once

#include <string>

using namespace std;

// ��־����
enum ELogType
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
	int socket;			// 
}ClientConnInfo;

