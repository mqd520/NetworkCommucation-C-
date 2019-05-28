#pragma once
#include <WinSock2.h>
#include <string>
#include <vector>

using namespace std;

namespace tc
{
	// �ص�����ԭ��
	// string err:		������Ϣ
	// void* lpParam:	���Ӳ���
	typedef void(*LPErrorCallback)(string err, void* lpParam);

	// �ص���Ϣ
	typedef struct tagSocketCallbackInfo
	{
		LPErrorCallback lpfn;	// �ص�����ָ��
		void* lpParam;			// ���Ӳ���
	}SocketCallbackInfo;

	// socket������
	class SocketTool
	{
	public:
		SocketTool();
		~SocketTool();

	private:
		static vector<SocketCallbackInfo> vecFNs;	// �ص���Ϣ����

	private:
		//************************************
		// Method:    ���������Ϣ
		// Parameter: fn:		��������
		// Parameter: code:		ϵͳ������
		// Parameter: remark:	��ע��Ϣ
		// Parameter: b:		�Ƿ���
		//************************************
		static void ProcessErrorInfo(string fn, int code, string remark = "", bool b = true);

	public:
		//************************************
		// Method:    ע��ص�����ָ��
		// Parameter: lpfn:	�ص�����ָ��
		// Parameter: lpParam: ���Ӳ���
		//************************************
		static void RegErrorCallback(LPErrorCallback lpfn, void* lpParam);

		//************************************
		// Method:    �Ƴ��ص�����ָ��
		// Parameter: lpfn:	�ص�����ָ��
		//************************************
		static void RemoveErrorCallback(LPErrorCallback lpfn);

		//************************************
		// Method:    ��ʼ��
		//************************************
		static bool Init(bool b = true);

		//************************************
		// Method:    �ͷ���Դ
		//************************************
		static void Release();

		//************************************
		// Method:    ����һ��SOCKET
		//************************************
		static SOCKET CreateTcpSocket(bool b = true);

		//************************************
		// Method:    ��ȡSOCKADDR_IN
		//************************************
		static SOCKADDR_IN GetSocketAddr(string ip, int port);

		//************************************
		// Method:    bind socket
		//************************************
		static bool Bind(SOCKET socket, string ip, int port, bool b = true);

		//************************************
		// Method:    ��ʼ���������
		//************************************
		static bool Listen(SOCKET socket, string ip, int port, int backlog = SOMAXCONN, bool b = true);

		//************************************
		// Method:    ����������
		//************************************
		static SOCKET Accept(SOCKET socket, string ip, int port, bool b = true);

		//************************************
		// Method:    �ر�socket
		//************************************
		static void CloseSocket(SOCKET socket);

		//************************************
		// Method:    ����socket������
		//************************************
		static void SetNonBlock(SOCKET socket, bool nonblock = true);

		//************************************
		// Method:    ��ȡ�Զ�socket��ip�Ͷ˿�
		//************************************
		static string GetPeerIpAndPort(SOCKET socket, int* port);

		//************************************
		// Method:    ��ȡ����IP
		//************************************
		static string GetLocalIP();
	};
}