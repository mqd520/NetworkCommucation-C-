#pragma once

#include <tchar.h>
#include "MemoryTool.h"
#include "Package3.h"
#include "ProtocolMgr.h"
#include "TcpClient.h"

using namespace Protocol3;
using namespace MemoryTool;

//���ݻص�ָ��
typedef void(*LPOnServer3RecvData)(Package3Type type, void* data);

class CService3Mgr
{
private:
	CTcpClient m_tcp;//tcp�ͻ��˹������
	CProtocolMgr m_protocol;//Э��������
	CByteStream* m_stream;//�ֽ�������
	CByteStream* m_streamCatch;//�ֽ����������
	LPOnServer3RecvData m_lpfn;//���ݻص�ָ��
public:
	CService3Mgr();
	~CService3Mgr();

	//************************************
	// Method:    ��ʼ��
	// FullName:  CServer3Mgr::Init
	// Access:    public static 
	// Returns:   bool
	// Qualifier:
	// Parameter: TCHAR * ip
	// Parameter: int port
	//************************************
	bool Init(TCHAR* ip, int port, LPOnServer3RecvData lpfn);

	//************************************
	// Method:    ���������¼�����
	// FullName:  CServer3Mgr::OnRecvData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: BYTE buf[]
	// Parameter: int len
	//************************************
	void OnRecvData(BYTE buf[], int len);

	//************************************
	// Method:    ���
	// FullName:  CServer3Mgr::Unpacket
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void Unpacket();

	//************************************
	// Method:    ������,��ʾ�Ƿ���Ҫ��������
	// FullName:  CServer3Mgr::AnalyticsPackage
	// Access:    public 
	// Returns:   ����Ҫ��������
	// Qualifier:
	// Parameter: ������
	// Parameter: ����ṹ��ָ��
	//************************************
	bool AnalyticsPackage(Package3Type type, LPPackage3Base data);

	//************************************
	// Method:    �ͷŰ���ṹ��
	// FullName:  CServer3Mgr::ReleasePackage
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: ������
	// Parameter: ����ṹ��ָ��
	//************************************
	void ReleasePackage(Package3Type type, LPPackage3Base data);

	//************************************
	// Method:    ����
	// FullName:  CServer3Mgr::Send
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: ������
	// Parameter: ����ṹ��ָ��
	//************************************
	bool Send(Package3Type type, LPPackage3Base data);

	//************************************
	// Method:    ģ��һ�η���˷���
	// FullName:  CServer3Mgr::SimulateServer3Data
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: ������
	// Parameter: ����ṹ��ָ��
	//************************************
	void SimulateServer3Data(Package3Type type, Package3Base* data);
};