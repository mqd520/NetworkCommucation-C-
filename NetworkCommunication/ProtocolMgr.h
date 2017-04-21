#pragma once

#include <tchar.h>
#include <vector>
#include "MemoryTool.h"
#include "Def.h"
#include "TcpClientT.h"

namespace NetworkCommunication
{
	//协议管理事件类型
	enum ProtocolEvtType
	{
		tcpError = TcpEvtType::error,//发生了tcp错误
		keepAliveFail = 2,//心跳包失败
		online = 10,//服务端已上线
		offline = 11//服务端已下线
	};

	//协议管理
	class CProtocolMgr
	{
	protected:
		//************************************
		// Method:    客户端收到包体数据函数指针
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::LPOnRecvBusinessData
		// Access:    protected 
		// Returns:   void
		// Qualifier: 包类型
		// Parameter: 包体结构体指针
		//************************************
		typedef void(*LPOnRecvPackageData)(int type, LPPackageBase data);

		//************************************
		// Method:    收到协议事件处理
		// FullName:  NetworkCommunication::CProtocolMgr::LPOnRecvProtocolEvt
		// Access:    protected 
		// Returns:   是否已处理事件
		// Qualifier: 事件类型
		// Parameter: 消息
		//************************************
		typedef bool(*LPOnRecvProtocolEvt)(ProtocolEvtType type, TCHAR* msg);

		//包管理信息
		typedef struct tagPackageMgrInfo
		{
			int type;//包类型
			IPackageMgr* mgr;//包管理器
		}PackageMgrInfo, *LPPackageMgrInfo;

		//线程信息
		typedef struct tagThreadInfo
		{
			HANDLE hThread;//线程句柄
			DWORD dwThreadID;//线程ID
		}ThreadInfo, *LPThreadInfo;

	protected:
		CTcpClientT<CProtocolMgr> m_tcp;//tcp客户端对象
		CByteStream* m_stream;//字节流对象
		LPOnRecvPackageData m_lpfnRecvData;//收到包体数据函数指针
		int m_nPackageHeadLen;//包头长度
		int m_nKeepAlive;//心跳包类型
		vector<PackageMgrInfo> m_vecPackageMgr;//包管理器集合
		HANDLE m_hMutexStream;//字节流互斥对象
		ThreadInfo m_tiTimer;//心跳包线程信息
		int m_nKeepAliveTimespan;//心跳包间隔时间
		bool m_bRecvKeepAlive;//是否已收到心跳包
		int m_nKeepAliveFailCount;//心跳包失败计数,0代表已收到对方心跳包
		int m_nKeepAliveFailMaxCount;//心跳包失败计数最大值,超过值后认为对方已掉线
		int m_nReconnectServerMaxCount;//失去服务端连接(非tcp连接,检测不到指定次数的心跳包),自动重连的最大值(0:无限制)
		int m_nReconnectServerCount;//失去服务端连接后,已连接服务端的次数
		bool m_bIsOnlineCallEvt;//是否已触发掉线事件
		bool m_bIsOfflineCallEvt;//是否已触发上线事件
		LPPackageBase m_pKeepAlive;//心跳包指针
		BYTE* m_pKeepAliveBuf;//心跳包缓冲区
		int m_nKeepAliveBufLen;//心跳包缓冲区长度
		LPOnRecvProtocolEvt m_lpfnRecvProtocolEvt;//收到协议事件函数指针
		int m_nStreamBufLen;//流缓冲区长度
		int m_nTcpBufLen;//tcp接收缓冲区长度
		bool m_bAutoReconnect;//是否自动重连
		int m_nReconnectTimes;//允许重连次数
		int m_nReconnectTimeSpan;//重连间隔时间
		int m_nConnectTimeout;//连接超时时间

	private:
		//************************************
		// Method:    初始化心跳包
		// FullName:  NetworkCommunication::CProtocolMgr::InitKeepAlive
		// Access:    private 
		// Returns:   void
		// Qualifier:
		//************************************
		void InitKeepAlive();

	protected:
		//************************************
		// Method:    关联包类型到包管理器
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::AssoicatePackageType
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void AssociatePackageType();

		//************************************
		// Method:    验证心跳包
		// FullName:  ProtocolMgr::CProtocolMgr<TPackageType, TPackageBase>::ValidateKeepAlivePackage
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		// Parameter: 心跳包
		//************************************
		virtual bool ValidateKeepAlivePackage(LPPackageBase data);

		//************************************
		// Method:    验证接收到的包头缓冲区是否有效(缓冲区长度为包头长度)
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::ValidatePackageHead
		// Access:    virtual protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: 缓冲区
		//************************************
		virtual bool ValidatePackageHead(BYTE buf[]);

		//************************************
		// Method:    验证包类型是否有效
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::ValidatePackageType
		// Access:    virtual protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: 包类型
		//************************************
		virtual bool ValidatePackageType(int type);

		//************************************
		// Method:    接收数据事件处理
		// FullName:  CServer3Mgr::OnRecvData
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual bool OnRecvData(BYTE buf[], int len);

		//************************************
		// Method:    开始解包(循环从流中解包,直到流中长度不足包头长度)
		// FullName:  CServer3Mgr::Unpacket
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void StartUnpacket();

		//************************************
		// Method:    分析包,表示是否交由调用者处理包
		// FullName:  CServer3Mgr::AnalyticsPackage
		// Access:    public 
		// Returns:   是否交由调用者处理
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
		//************************************
		virtual bool AnalyticsPackage(int type, LPPackageBase data);

		//************************************
		// Method:    清理线程
		// FullName:  NetworkCommunication::CProtocolMgr::CleanThread
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		void CleanThread();

		//************************************
		// Method:    收到tcp事件处理
		// FullName:  NetworkCommunication::CProtocolMgr::OnRecvTcpEvt
		// Access:    protected 
		// Returns:   bool
		// Qualifier:
		// Parameter: TcpClientEvtType type
		// Parameter: TCHAR * msg
		//************************************
		bool OnRecvTcpEvt(TcpEvtType type, TCHAR* msg);

		//************************************
		// Method:    tcp连接成功事件处理
		// FullName:  NetworkCommunication::CProtocolMgr::OnTcpConnectSuccess
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnTcpConnectSuccess();

		//************************************
		// Method:    tcp连接失败事件处理
		// FullName:  NetworkCommunication::CProtocolMgr::OnTcpConnectFail
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnTcpConnectFail();

		//************************************
		// Method:    连接服务端成功事件处理
		// FullName:  NetworkCommunication::CProtocolMgr::OnConnectServerSuccsss
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnConnectServerSuccsss();

		//************************************
		// Method:    连接服务端失败事件处理
		// FullName:  NetworkCommunication::CProtocolMgr::OnConnectServerFail
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnConnectServerFail();

		//************************************
		// Method:    发送协议事件
		// FullName:  NetworkCommunication::CProtocolMgr::SendProtocolEvt
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 事件类型
		// Parameter: 消息
		//************************************
		void SendProtocolEvt(ProtocolEvtType type, TCHAR* msg);

		//************************************
		// Method:    发送缓冲区准备完成事件处理
		// FullName:  NetworkCommunication::CProtocolMgr::OnSendBufReadyCmp
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual void OnSendBufReadyCmp(BYTE* buf, int len);

		//************************************
		// Method:    接收缓冲区(完整包)准备完成事件处理
		// FullName:  NetworkCommunication::CProtocolMgr::OnRecvBufReadyCmp
		// Access:    virtual protected 
		// Returns:   缓冲区是否有效
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		virtual bool OnRecvBufReadyCmp(BYTE* buf, int len);

		//************************************
		// Method:    开始心跳包
		// FullName:  NetworkCommunication::CProtocolMgr::StartKeepAlive
		// Access:    virtual protected 
		// Returns:   void
		// Qualifier:
		//************************************
		void StartKeepAlive();

		//************************************
		// Method:    是否指定了心跳包
		// FullName:  NetworkCommunication::CProtocolMgr::IsAssignedKeepAlive
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		bool IsAssignedKeepAlive();

	public:
		CProtocolMgr();
		~CProtocolMgr();

		//************************************
		// Method:    初始化
		// FullName:  NetworkCommunication::CProtocolMgr::Init
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: TCHAR * ip
		// Parameter: int port
		// Parameter: LPOnRecvPackageBodyData lpfnRecvData
		// Parameter: LPOnRecvNotifyEvt lpfnNotifyEvt
		//************************************
		virtual void Init(TCHAR* ip, int port, LPOnRecvPackageData lpfnRecvData, LPOnRecvProtocolEvt lpfnRecvProtocolEvt = NULL);

		//************************************
		// Method:    封包(调用方释放缓冲区指针)
		// FullName:  Protocol3::CProtocol3Handle::Packet
		// Access:    public 
		// Returns:   包缓冲区指针
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体数据缓冲区指针
		// Parameter: 包体数据缓冲区长度
		// Parameter: 包缓冲区长度(输出)
		//************************************
		virtual BYTE* PacketFromBuf(int type, BYTE buf[], int bufLen, int* packetLen);

		//************************************
		// Method:    获取包头缓冲区
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::GetPackageHeadBuf
		// Access:    virtual protected 
		// Returns:   缓冲区
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体数据长度
		//************************************
		virtual BYTE* GetPackageHeadBuf(int type, int len);

		//************************************
		// Method:    封包(调用方释放缓冲区指针)
		// FullName:  Protocol3::CProtocol3Handle::Packet
		// Access:    public static 
		// Returns:   包缓冲区指针
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
		// Parameter: 包缓冲区长度(输出)
		//************************************
		virtual BYTE* Packet(int type, LPPackageBase data, int* packetLen);

		//************************************
		// Method:    从缓冲区中(包含包头和包体)解析出一个包体结构体数据
		// FullName:  Protocol3::CProtocol3Handle::Unpacket
		// Access:    public 
		// Returns:   包体结构体指针
		// Qualifier:
		// Parameter: 完整包缓冲区指针
		// Parameter: 缓冲区长度
		//************************************
		virtual LPPackageBase Unpacket(BYTE buf[], int len);

		//************************************
		// Method:    获取包头长度
		// FullName:  Protocol3::CProtocol3Handle::GetHeadLen
		// Access:    public 
		// Returns:   包头长度
		// Qualifier:
		//************************************
		virtual int GetHeadLen();

		//************************************
		// Method:    从缓冲区中获取包体数据长度
		// FullName:  Protocol3::CProtocol3Handle::GetDataLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区长度
		//************************************
		virtual int GetDataLen(BYTE buf[], int len);

		//************************************
		// Method:    从缓冲区中获取包类型
		// FullName:  Protocol3::CProtocol3Handle::GetPackageType
		// Access:    public 
		// Returns:   包类型
		// Qualifier:
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区长度
		//************************************
		virtual int GetPackageType(BYTE buf[], int len);

		//************************************
		// Method:    获取包管理器(调用方无需释放指针)
		// FullName:  Protocol3::CProtocol3Handle::GetMgr
		// Access:    protected static 
		// Returns:   Protocol3::Package3Mgr*
		// Qualifier:
		// Parameter: 包类型
		//************************************
		virtual IPackageMgr* GetPackageMgr(int type);

		//************************************
		// Method:    获取包体缓冲区指针
		// FullName:  Protocol3::CProtocol3Handle::GetDataBuf
		// Access:    public static 
		// Returns:   包体缓冲区指针
		// Qualifier:
		// Parameter: 包缓冲区指针 
		// Parameter: 包缓冲区长度
		//************************************
		virtual BYTE* GetDataBuf(BYTE* buf, int len);

		//************************************
		// Method:    释放包体结构体
		// FullName:  CServer3Mgr::ReleasePackage
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
		//************************************
		virtual void ReleasePackage(int type, LPPackageBase data);

		//************************************
		// Method:    发包
		// FullName:  CServer3Mgr::Send
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
		//************************************
		virtual bool SendData(int type, LPPackageBase data);

		//************************************
		// Method:    关闭连接
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::CloseConnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void CloseConnect();

		//************************************
		// Method:    连接服务端
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::Reconnect
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void Connect();

		//************************************
		// Method:    获取tcp客户端对象
		// FullName:  NetworkCommunication::CProtocolMgr<TPackageType, TPackageBase>::GetTcpObj
		// Access:    virtual public 
		// Returns:   NetworkCommunication::CTcpClientT*
		// Qualifier:
		//************************************
		virtual CTcpClient GetTcpClientObj();

		//************************************
		// Method:    模拟一次服务端发包
		// FullName:  CServer3Mgr::SimulateServer3Data
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 包类型
		// Parameter: 包体结构体指针
		//************************************
		virtual void SimulateServerData(int type, LPPackageBase data);

		//************************************
		// Method:    心跳包定时器事件发生(由CProtocolMgr或其派生类调用,客户端无需调用)
		// FullName:  NetworkCommunication::CProtocolMgr::OnTimerKeepAlive
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void OnTimerKeepAlive();

		//************************************
		// Method:    对方是否在线
		// FullName:  NetworkCommunication::CProtocolMgr::IsOnline
		// Access:    protected 
		// Returns:   void
		// Qualifier:
		//************************************
		bool IsOnline();
	};
}