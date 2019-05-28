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
		//************************************
		static void RegErrorCallback(LPErrorCallback lpfn, void* lpParam);

		//************************************
		// Method:    �Ƴ��ص�����ָ��
		//************************************
		static void RemoveErrorCallback(LPErrorCallback lpfn);

		static bool Init(bool b = true);

		static void Release();

		static SOCKET CreateTcpSocket(bool b = true);

		static SOCKADDR_IN GetSocketAddr(string ip, int port);

		static bool Bind(SOCKET socket, string ip, int port, bool b = true);

		static string GetPeerIpAndPort(SOCKET socket, int* port);

		//************************************
		// Method:    ��ȡ����IP
		//************************************
		static string GetLocalIP();
	};
}