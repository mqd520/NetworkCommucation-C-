
// Client1.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Client1.h"
#include "Client1Dlg.h"
#include "NetCommuMgr.h"
#include "ConnectSrvResultEvt.h"
#include "RecvPeerDataEvt.h"
#include "TimeoutMgr.h"

using namespace NetworkCommunication;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//************************************
// Method:    tcp�¼�����
// Parameter: tcp�¼�
//************************************
void OnRecvTcpEvent(CTcpEvt* pEvent);

// CClient1App

BEGIN_MESSAGE_MAP(CClient1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



// CClient1App ����

CClient1App::CClient1App()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CClient1App ����

CClient1App theApp;

// CClient1App ��ʼ��

BOOL CClient1App::InitInstance()
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

	CNetworkCommuMgr::Init();
	m_pTcpClient = new CTcpClient(_T("192.168.0.68"), 8040);
	m_pTcpClient->RegTcpEventCallback(OnRecvTcpEvent);


	CClient1Dlg dlg;
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

int CClient1App::ExitInstance()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CNetworkCommuMgr::Exit();

	return CWinApp::ExitInstance();
}

void OnRecvTcpEvent(CTcpEvt* pEvent)
{
	switch (pEvent->GetEvtType())
	{
	case ETcpEvent::ConnectSrvResult:
	{
		//CConnectCmpEvt* pConnCmpEvt = (CConnectCmpEvt*)pEvent;
		//if (!pConnCmpEvt->GetConnectResult())
		//{
		//	TRACE(_T("����ʧ��,���ڽ�����������!!!!!!!!!!!!!!!! \n"));
		//}
		//else
		//{
		//	TRACE(_T("���ӳɹ�!!!!!!!!!!! \n"));
		//}
	}
	case  ETcpEvent::RecvPeerData:
	{
		CRecvPeerDataEvt* pRecvPeerDataEvt = (CRecvPeerDataEvt*)pEvent;
		//PeerData* pData = new PeerData();
		//pData->buf = pRecvPeerDataEvt->GetRecvBuf();
		//pData->len = pRecvPeerDataEvt->GetBufLen();
		//_tcscpy(pData->ip, ip);
		//pData->port = port;
		//SendMessage(theApp.m_pMainWnd->m_hWnd, WM_RECVPEERDATA, (WPARAM)pData, 0);
		//delete pData;
	}
	break;
	}
}
