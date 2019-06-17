#include "stdafx.h"
#include "Service1.h"
#include "Server1.h"
#include "MSG.h"

#include "tc/TcpEvt.h"
#include "tc/RecvNewConnEvt.h"
#include "tc/ConnDisconnectEvt.h"

using namespace tc;

//************************************
// Method:    tcp事件回调函数
// Parameter: tcp事件对象
// Parameter: 附加参数1
// Parameter: 附加参数2
//************************************
void OnTcpEvt(TcpEvt* pEvt, void* pParam1, void* pParam2)
{
	if (pEvt->GetEvtType() == ETcpEvt::RecvNewConn)
	{
		RecvNewConnEvt* pEvt1 = (RecvNewConnEvt*)pEvt;

		char ch[50] = { 0 };
		sprintf_s(ch, "recv new conn %s:%d", pEvt1->GetClientIP().c_str(), pEvt1->GetClientPort());

		//OutputDebugStringA(ch);
		//OutputDebugStringA("\n");

		theApp.GetLogSrv()->Add(ch);

		ClientConnInfoMgr* mgr = theApp.GetSrv1()->GetClientConnInfoMgr();
		int id = mgr->Add(pEvt1->GetClientIP(), pEvt1->GetClientPort(), pEvt1->GetSendRecvSocket());
		::PostMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_RECVNEWCLIENT, id, NULL);
	}
	else if (pEvt->GetEvtType() == ETcpEvt::RecvData)
	{
		SOCKET socket = pEvt->GetSendRecvSocket();
	}
	else if (pEvt->GetEvtType() == ETcpEvt::ConnDisconnect)
	{
		ConnDisconnectEvt* pEvt1 = static_cast<ConnDisconnectEvt*>(pEvt);
		char ch[100] = { 0 };
		sprintf_s(ch, "connection disconn %s:%d, socket: %d", pEvt1->GetPeerIp().c_str(), pEvt1->GetPeerPort(), pEvt1->GetSendRecvSocket());
		OutputDebugStringA(ch);
		OutputDebugStringA("\n");

		ClientConnInfoMgr* mgr = theApp.GetSrv1()->GetClientConnInfoMgr();
		mgr->Remove(pEvt->GetSendRecvSocket());
		::PostMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_CLIENTDISCONN, NULL, NULL);
	}
}

Service1::Service1()
{

}

Service1::~Service1()
{

}

void Service1::Init()
{
	mainTcpSrv.RegTcpEventCallback(OnTcpEvt, &theApp, NULL);
}

TcpServer* Service1::GetMainTcpSrv()
{
	return &mainTcpSrv;
}

ClientConnInfoMgr* Service1::GetClientConnInfoMgr()
{
	return &ccMgr;
}

