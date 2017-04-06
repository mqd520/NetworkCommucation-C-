#pragma once

#include <tchar.h>
#include "TcpClient.h"
#include "MemoryTool.h"
#include "Package3.h"

using namespace Protocol3;
using namespace MemoryTool;

//数据回调指针
typedef void(*LPOnServer3RecvData)(Package3Type type, void* data);

class CServer3Mgr
{
private:
	CTcpClient m_tcp;
	CByteStream* m_stream;//字节流对象
	CByteStream* m_streamCatch;//字节流缓存对象
	LPOnServer3RecvData m_lpfn;//数据回调指针
public:
	CServer3Mgr();
	~CServer3Mgr();

	//************************************
	// Method:    初始化
	// FullName:  CServer3Mgr::Init
	// Access:    public static 
	// Returns:   bool
	// Qualifier:
	// Parameter: TCHAR * ip
	// Parameter: int port
	//************************************
	bool Init(TCHAR* ip, int port, LPOnServer3RecvData lpfn);

	//************************************
	// Method:    接收数据事件处理
	// FullName:  CServer3Mgr::OnRecvData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: BYTE buf[]
	// Parameter: int len
	//************************************
	void OnRecvData(BYTE buf[], int len);

	//************************************
	// Method:    解包
	// FullName:  CServer3Mgr::Unpacket
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void Unpacket();

	//************************************
	// Method:    释放包体结构体
	// FullName:  CServer3Mgr::ReleasePackage
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: 包类型
	// Parameter: 包体结构体指针
	//************************************
	void ReleasePackage(Package3Type type, LPPackage3Base data);

	//************************************
	// Method:    发包
	// FullName:  CServer3Mgr::Send
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: 包类型
	// Parameter: 包体结构体指针
	//************************************
	bool Send(Package3Type type, LPPackage3Base data);

	//************************************
	// Method:    模拟一次服务端发包
	// FullName:  CServer3Mgr::SimulateServer3Data
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: 包类型
	// Parameter: 包体结构体指针
	//************************************
	void SimulateServer3Data(Package3Type type, Package3Base* data);
};