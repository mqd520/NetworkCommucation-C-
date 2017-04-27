#pragma once

#include "ProtocolMgr.h"
#include "DemoProtocol.h"
#include "EncryptBuffer.h"

namespace NetworkCommunication
{
	//DemoProtocol协议管理
	class CDemoProtocolMgr :public CProtocolMgr
	{
	protected:
		CEncryptBuffer m_entrypy;//字节加密对象

	protected:
		void AssociatePackageType();
		BYTE* GetPackageHeadBuf(int type, int len);
		bool ValidateKeepAlivePackage(LPPackageBase data);
		bool ValidatePackageHead(BYTE buf[]);
		bool ValidatePackageType(int type);
		void OnSendBufReadyCmp(BYTE* buf, int len);
		bool OnRecvBufReadyCmp(BYTE* buf, int len);
		void OnTcpConnectSuccess(TCHAR* msg);
		bool AnalyticsPackage(int type, LPPackageBase data);
		void OnPackageHeadInvalid();

	public:
		CDemoProtocolMgr();
		~CDemoProtocolMgr();

		int GetDataLen(BYTE buf[], int len);
		int GetPackageType(BYTE buf[], int len);
	};
}