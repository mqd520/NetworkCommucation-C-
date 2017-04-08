#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	{if(p){delete p;p=NULL;}}
#endif // !SAFE_DELETE

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p){delete[] p;  p=NULL;} }
#endif // !SAFE_DELETE_ARRAY


//����ָ��:�յ�tcp����
typedef void(*LPOnRecvTCPData)(BYTE buf[], int len);

//��Ա����
//template<typename T>
//typedef void(T::*LPOnMemRecvData)(BYTE buf[], int len);

//TcpClient�ͻ�����
class CSocketClient
{
private:
	typedef struct tagThreadInfo
	{
		HANDLE hThread;
		DWORD nThreadID;
	}ThreadInfo;

public:
	CSocketClient();
	~CSocketClient();

	//��ʼ��
	void Init(const TCHAR* ip, int port, LPOnRecvTCPData lpfn = NULL);
	//���ӵ������
	bool StartConnect();
	//�ر�����������
	void CloseConnect();
	//��ȡ���һ�δ�����Ϣ
	TCHAR* GetLastError();
	//��ȡSocket
	SOCKET GetServerSocket();
	//���������¼�
	void OnRecvData(BYTE buf[], int len);
	//�����ͷ���Դ
	void Dispose();
	//��������
	bool SendData(BYTE buf[], int len);
	//�Ƿ��ѳ�ʼ��
	bool IsInited();

protected:
	const TCHAR* m_strServerIP;//�����IP
	int m_nServerPort;//����˶˿�
	bool m_bIsCleaned;//�Ƿ�������
	bool m_bIsConnected;//�Ƿ��Ѿ������Ϸ����
	TCHAR* m_strLastError;//���һ�δ�����Ϣ
	SOCKADDR_IN m_addrSrv;//����˵�ַ
	SOCKET m_socket;//�ͻ���Socket
	ThreadInfo m_readThreadInfo;//���ݶ�ȡ�߳���Ϣ
	bool m_bInited;//��ʼ��
	LPOnRecvTCPData m_lpOnRecvData;//���ݻص�ָ��
	TCHAR* m_strClientIP;//�ͻ���IP
	int m_nClientPort;//�ͻ��˶˿�

protected:
	//��ʼ��
	bool InitSocket();
	//����Socket
	void CleanSocket();
	//д��һ����־
	void WriteLine(string log);
	//�����߳�
	void CleanThread();
	//************************************
	// Method:    ���ÿͻ���IP�Ͷ˿�
	// FullName:  CSocketClient::SetAddressBySocket
	// Access:    protected 
	// Returns:   bool
	// Qualifier:
	// Parameter: SOCKET socket
	//************************************
	bool SetAddressBySocket(SOCKET socket);
};