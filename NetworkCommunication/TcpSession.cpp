#include "stdafx.h"
#include "TcpSession.h"
#include "MemoryTool.h"

namespace NetworkCommunication
{
	CTcpSession::CTcpSession(SOCKET serverSocket, SOCKET clientSocket) :
		m_serverSocket(serverSocket),
		m_clientSocket(clientSocket),
		m_nBufLen(1024)
	{
		m_pBuf = new BYTE[m_nBufLen];
	}

	CTcpSession::~CTcpSession()
	{
		if (m_pBuf)
		{
			//delete m_pBuf;
		}
	}

	SOCKET CTcpSession::GetClientSocket()
	{
		return m_clientSocket;
	}

	void CTcpSession::StartRecvData()
	{
		int result = ::recv(m_clientSocket, (char*)m_pBuf, m_nBufLen, 0);
		if (result > 0)
		{
			//_tprintf(_T("Recv byte: %d \n"), result);
			string wstr = ReadMultiByteStr(m_pBuf, result);
			wstring str = MultiByteToUTF8(wstr.c_str());
			_tprintf(_T("Recv data: %s \n"), str.c_str());
		}
	}
}