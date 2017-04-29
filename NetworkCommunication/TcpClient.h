#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#include <tchar.h>
#include <WinSock2.h>
#include <string>
#include <queue>
#include "Timer.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp事件类型
	enum TcpEvtType
	{
		error,//错误
		connfailed,//连接失败
		connectsuccess,//连接成功,
		disconnect,//服务器断开连接,
		Net,//网络错误,
		TcpInfo//消息
	};

	//tcp数据接收方式
	enum TcpDataRecvType
	{
		que,//队列
		single,//单线程(接收线程)
		multi//多线程
	};

	//缓冲区信息
	typedef struct tagBufInfo
	{
		BYTE* buf;//缓冲区
		int len;//缓冲区长度
	}BufInfo, *LPBufInfo;

	//************************************
	// Method:    收到tcp数据函数指针
	// FullName:  NetworkCommunication::LPOnRecvTcpData
	// Access:    public 
	// Returns:   指示调用者是否已释放缓冲区
	// Qualifier: 缓冲区
	// Parameter: 缓冲区长度
	//************************************
	typedef bool(*LPOnRecvTcpData)(BYTE buf[], int len);

	//************************************
	// Method:    收到tcp事件函数指针
	// FullName:  NetworkCommunication::LPOnRecvTcpEvt
	// Access:    public 
	// Returns:   void
	// Qualifier: 事件类型
	// Parameter: 消息
	//************************************
	typedef void(*LPOnRecvTcpEvt)(TcpEvtType type, TCHAR* msg);

	//tcp客户端
	class CTcpClient
	{
	private:
		//线程信息
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//线程句柄
			DWORD dwThreadID;//线程ID
			bool bPause;//是否暂停
		}ThreadInfo, *LPThreadInfo;

	protected:
		//const TCHAR* m_strServerIP;//服务端IP
		TCHAR m_strServerIP[20];//服务端IP
		int m_nServerPort;//服务端端口
		SOCKADDR_IN m_addrSrv;//服务端地址
		SOCKET m_socket;//客户端Socket
		bool m_bInited;//是否初始化
		LPOnRecvTcpData m_lpfnOnRecvTcpData;//接收tcp数据回调函数
		int m_nRecvTcpBufLen;//接收tcp缓冲区总长度
		char* m_pRecvTcpBuf;//接收tcp缓冲区
		LPOnRecvTcpEvt m_lpfnOnRecvTcpEvt;//接收tcp事件回调函数
		bool m_bHaslpfnRecvTcpData;//是否已有接收tcp数据回调函数
		int m_nReconnectTimeSpan;//连接失败后再次连接间隔时间(毫秒)
		int m_nAllowReconnectCount;//允许重连计数(-1:不允许重连,0:无限制,>0:允许次数)
		int m_nReconnectCount;//已重连计数(连接成功后立即重置0)
		int m_nConnectTimeout;//连接超时时间(0:无限制等待,>0:限制指定时间)
		bool m_bAllowReconnect;//连接断开后是否允许重新连接
		ThreadInfo m_tiConnect;//连接线程信息
		ThreadInfo m_tiReadTcpData;//读取tcp数据线程信息
		CTimerT<CTcpClient>* m_timer;//连接超时对象
		TcpDataRecvType m_sendType;//tcp数据发送方式
		queue<BufInfo> m_queue;//队列对象
		ThreadInfo m_tiQueue;//队列线程信息
		bool m_bSocketAvaliabled;//socket是否可用

	protected:
		//初始化socket环境
		void InitSocket();

		//初始化服务端地址信息
		void InitServerAddr();

		//创建socket
		void CreateSocket();

		//************************************
		// Method:    发送tcp事件
		// Parameter: 事件类型
		// Parameter: 消息
		//************************************
		virtual void SendTcpEvt(TcpEvtType type, TCHAR* msg);

		//连接成功事件处理
		void OnConnectSuccess();

		//************************************
		// Method:    连接超时事件处理
		// Returns:   是否继续计时
		//************************************
		bool OnConnectTimeout();

		//************************************
		// Method:    暂停(恢复)指定线程
		// Parameter: 线程信息指针
		// Parameter: 暂停与否
		//************************************
		void PauseThread(ThreadInfo* ti, bool b);

		//清理线程
		void CleanThread();

		//关闭socket
		void CloseSocket();

		//************************************
		// Method:    收到tcp数据事件处理
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		void OnRecvTcpData(BYTE buf[], int len);

		//************************************
		// Method:    发送接收到的tcp数据
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual void SendTcpData(BYTE buf[], int len);

		//************************************
		// Method:    单线程处理接收到的数据
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		void OnSingle(BYTE buf[], int len);

		//************************************
		// Method:    队列处理接收到的数据
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		void OnQueue(BYTE buf[], int len);

		//************************************
		// Method:    多线程处理接收到的数据
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		void OnMulti(BYTE buf[], int len);

		//连接断开后重新连接
		void Reconnect();

	public:
		CTcpClient();
		~CTcpClient();

		//************************************
		// Method:    初始化
		// Parameter: 服务端IP
		// Parameter: 服务端端口
		// Parameter: 发送接收到的tcp数据方式
		// Parameter: 接收缓冲区长度
		// Parameter: 允许重连计数(-1:不允许重连,0:无限制,>0:允许次数)
		// Parameter: 重连间隔
		// Parameter: 连接超时时间
		// Parameter: 断开后是否允许重连
		//************************************
		void Init(TCHAR* ip, int port, TcpDataRecvType type = TcpDataRecvType::single, int socketBufLen = 1024, int allowReconnectCount = 0,
			int reconnectTimeSpan = 2000, int connectTimeout = 2000, bool allowReconnect = true);

		//************************************
		// Method:    设置回调函数
		// FullName:  NetworkCommunication::CTcpClient::SetCallback
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: 接收tcp数据回调函数
		// Parameter: 接收tcp事件回调函数
		//************************************
		void SetCallback(LPOnRecvTcpData lpfnOnRecvTcpData, LPOnRecvTcpEvt lpfnOnRecvTcpEvt = NULL);

		//开始连接
		void Connect();

		//关闭连接
		void CloseConnect();

		//************************************
		// Method:    发送数据
		// Returns:   是否发送成功
		// Parameter: 字节数组
		// Parameter: 字节数组长度
		// Parameter: 实际发送长度
		//************************************
		bool SendData(BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    模拟一次服务端发包
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		void SimulateServerData(BYTE* buf, int len);

		//读取队列线程入口(无需调用)
		void ReadQueue();

		//连接服务端线程入口(无需调用)
		void ConnectServer();

		//读取tcp数据线程入口(无需调用)
		void ReadTcpData();

		//************************************
		// Method:    多线程处理接收的tcp数据线程入口(无需调用)
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		void MultiSendTcpData(BYTE buf[], int len);
	};
}