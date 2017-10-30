
// Server6.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Server6.h"
#include "Server6Dlg.h"
#include "NetCommuMgr.h"
#include "RecvNewConnEvt.h"
#include "RecvPeerDataEvt.h"
#include "RecvConnResultEvt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//************************************
// Method:    tcp�¼�����
// Parameter: tcp�¼�
//************************************
void OnRecvTcpEvent(CTcpEvt* pEvent);

// CServer6App

BEGIN_MESSAGE_MAP(CServer6App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CServer6App ����

CServer6App::CServer6App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CServer6App ����

CServer6App theApp;

// CServer6App ��ʼ��

BOOL CServer6App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	m_pTcpSrv = new CTcpServer();
	CNetworkCommuMgr::Init();//��ʼ������ͨ��
	m_pTcpSrv->RegTcpEventCallback(OnRecvTcpEvent);//ע��tcp�¼��ص�

	CServer6Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CServer6App::ExitInstance()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CNetworkCommuMgr::Exit();

	return CWinApp::ExitInstance();
}

void OnRecvTcpEvent(CTcpEvt* pEvent)
{
	CSocketAPI api;
	TCHAR ip[20];
	int port = 0;
	api.GetPeerIpAndPort(pEvent->GetSendRecvSocket(), ip, &port);

	switch (pEvent->GetEvtType())
	{
	case ETcpEvent::RecvNewConnection://�յ�������
	{
		CRecvNewConnEvt* pRecvEvent = (CRecvNewConnEvt*)pEvent;

		//pRecvEvent->m_bRefuse = true;
		//return;

		//if (_tcscmp(ip, _T("192.168.0.2")) == 0)
		//{
		//	pRecvEvent->m_bRefuse = true;
		//	return;
		//}
	}
	break;
	case ETcpEvent::RecvConnResult://���������ӽ��
	{
		CRecvConnResultEvt* pRecvResultEvt = (CRecvConnResultEvt*)pEvent;
		if (pRecvResultEvt->GetRecvResult())
		{
			TcpSessionData data;
			data.server = theApp.m_pTcpSrv->GetSocket();
			data.client = pRecvResultEvt->GetSendRecvSocket();
			_tcscpy(data.ip, ip);
			data.port = port;
			int index = theApp.m_sessionMgr.Push(data);
			PostMessage(theApp.m_pMainWnd->m_hWnd, WM_RECVNEWCONNECTION, index, 0);
		}
		else
		{
			SendMessage(theApp.m_pMainWnd->m_hWnd, WM_REFUSENEWCONNECTION, (WPARAM)pRecvResultEvt->GetClientIP(), pRecvResultEvt->GetClientPort());
		}
	}
	break;
	case  ETcpEvent::RecvPeerData://�յ��Զ�����
	{
		CRecvPeerDataEvt* pRecvPeerDataEvt = (CRecvPeerDataEvt*)pEvent;
		PeerData* pData = new PeerData();
		pData->buf = pRecvPeerDataEvt->GetRecvBuf();
		pData->len = pRecvPeerDataEvt->GetBufLen();
		_tcscpy(pData->ip, ip);
		pData->port = port;
		SendMessage(theApp.m_pMainWnd->m_hWnd, WM_RECVPEERDATA, (WPARAM)pData, 0);
		delete pData;
	}
	break;
	case ETcpEvent::ConnDisconnect://���ӶϿ�
	{
		int index = theApp.m_sessionMgr.RemoveByClientSocket(pEvent->GetSendRecvSocket());
		SendMessage(theApp.m_pMainWnd->m_hWnd, WM_PEERCLOSE, (WPARAM)index, NULL);
	}
	break;
	case  ETcpEvent::AsyncSendDataResult://�첽���ͽ��
	{

	}
	break;
	}
}
