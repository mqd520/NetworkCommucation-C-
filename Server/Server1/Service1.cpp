#include "stdafx.h"
#include "Service1.h"
#include "Server1.h"
#include "MSG.h"

#include "tc/TcpEvt.h"
#include "tc/RecvNewConnEvt.h"
#include "tc/ConnDisconnectEvt.h"
#include "tc/RecvDataEvt.h"

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

		char ch[100] = { 0 };
		sprintf_s(ch, "recv new conn %s:%d, socketId: %d", pEvt1->GetClientIP().c_str(), pEvt1->GetClientPort(), pEvt1->GetSendRecvSocketId());
		//OutputDebugStringA(ch);
		//OutputDebugStringA("\n");

		theApp.GetLogSrv()->Add(ch);

		ClientConnInfoMgr* mgr = theApp.GetSrv1()->GetClientConnInfoMgr();
		int id = mgr->Add(pEvt1->GetClientIP(), pEvt1->GetClientPort(), pEvt1->GetSendRecvSocketId());
		PostMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_RECVNEWCLIENT, id, NULL);
		SendMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_LOGINFO, (WPARAM)ch, NULL);
	}
	else if (pEvt->GetEvtType() == ETcpEvt::RecvData)
	{
		RecvDataEvt* pEvt1 = static_cast<RecvDataEvt*>(pEvt);

		string strBuf = "";
		BYTE* pBuf1 = pEvt1->GetRecvBuf();
		for (int i = 0; i < pEvt1->GetBufLen(); i++)
		{
			char ch[10] = { 0 };
			sprintf_s(ch, "%02X", pBuf1[i]);
			strBuf = strBuf + ch + " ";
		}
		char ch[2048] = { 0 };
		sprintf_s(ch, "recv data from %s:%d, len: %d, buf: %s", pEvt1->GetPeerIp().c_str(), pEvt1->GetPeerPort(), pEvt1->GetBufLen(), strBuf.c_str());
		//OutputDebugStringA(ch);
		//OutputDebugStringA("\n");

		theApp.GetLogSrv()->Add(ch);

		SendMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_LOGINFO, (WPARAM)ch, NULL);

		string response = "";
		response += "HTTP/1.1 200 OK\r\n";
		response += "Content-Type: text/html\r\n";
		response += "Server: Microsoft-IIS/7.5\r\n";
		response += "X-Powered-By: ASP.NET\r\n";
		response += "Date: Mon, 24 Jun 2019 15:27:59 GMT\r\n";
		response += "Content-Length: 2\r\n";
		response += "\r\n";

		response += "OK";

		theApp.GetSrv1()->GetMainTcpSrv()->Send(pEvt1->GetSendRecvSocketId(), (BYTE*)response.c_str(), response.size());
	}
	else if (pEvt->GetEvtType() == ETcpEvt::ConnDisconnect)
	{
		ConnDisconnectEvt* pEvt1 = static_cast<ConnDisconnectEvt*>(pEvt);

		char ch[100] = { 0 };
		sprintf_s(ch, "connection disconn %s:%d, socketId: %d", pEvt1->GetPeerIp().c_str(), pEvt1->GetPeerPort(), pEvt1->GetSendRecvSocketId());
		//OutputDebugStringA(ch);
		//OutputDebugStringA("\n");

		ClientConnInfoMgr* mgr = theApp.GetSrv1()->GetClientConnInfoMgr();
		mgr->Remove(pEvt->GetSendRecvSocketId());
		PostMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_CLIENTDISCONN, NULL, NULL);
		SendMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_LOGINFO, (WPARAM)ch, NULL);
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

