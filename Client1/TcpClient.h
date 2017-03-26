#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <string>

using namespace std;

#define TCPClientRecvMsg	(WM_USER+1000)

//�߳���Ϣ
typedef struct tagThreadInfo
{
	HANDLE hThread;
	DWORD nThreadID;
}ThreadInfo;

//TcpClient�ͻ�����
class CTcpClient
{
public:
	CTcpClient(HWND hwnd, const TCHAR* ip, int port);
	~CTcpClient();

	//���ӵ������
	bool StartConnect();
	//�ر�����������
	void CloseConnect();
	//��ȡ���һ�δ�����Ϣ
	TCHAR* GetLastError();
	//��ȡSocket
	SOCKET GetServerSocket();
	//��������
	void OnRecvData(char* buf);
	//�����ͷ���Դ
	void Dispose();
protected:
	HWND m_hwnd;//�����Ĵ��ھ��
	const TCHAR* m_strIP;//IP
	int m_nPort;//�˿�
	bool m_bIsCleaned;//�Ƿ�������
	bool m_bIsConnected;//�Ƿ��Ѿ������Ϸ����
	TCHAR* m_strLastError;//���һ�δ�����Ϣ
	SOCKADDR_IN m_addrSrv;//����˵�ַ
	SOCKET m_socket;//�ͻ���Socket
	ThreadInfo m_readThreadInfo;//���ݶ�ȡ�߳���Ϣ


	//��ʼ��
	bool Init();
	//����Socket
	void CleanSocket();
	//д��һ����־
	void WriteLine(string log);
	//�����߳�
	void CleanThread();
};