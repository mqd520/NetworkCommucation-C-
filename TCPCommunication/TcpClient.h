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



//���ݻص�ָ��
typedef void(*LPOnRecvData)(BYTE buf[], int len);

//TcpClient�ͻ�����
class CTcpClient
{
private:
	typedef struct tagThreadInfo
	{
		HANDLE hThread;
		DWORD nThreadID;
	}ThreadInfo;

public:
	CTcpClient();
	~CTcpClient();

	//��ʼ��
	void Init(const TCHAR* ip, int port, LPOnRecvData lpfn = NULL);
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
	const TCHAR* m_strIP;//IP
	int m_nPort;//�˿�
	bool m_bIsCleaned;//�Ƿ�������
	bool m_bIsConnected;//�Ƿ��Ѿ������Ϸ����
	TCHAR* m_strLastError;//���һ�δ�����Ϣ
	SOCKADDR_IN m_addrSrv;//����˵�ַ
	SOCKET m_socket;//�ͻ���Socket
	ThreadInfo m_readThreadInfo;//���ݶ�ȡ�߳���Ϣ
	bool m_bInited;//��ʼ��
	LPOnRecvData m_lpOnRecvData;//���ݻص�ָ��

	//��ʼ��
	bool InitSocket();
	//����Socket
	void CleanSocket();
	//д��һ����־
	void WriteLine(string log);
	//�����߳�
	void CleanThread();
};