#pragma once

#include "ProtocolMgr.h"
#include "DemoProtocol.h"

namespace NetworkCommunication
{
	class CDemoProtocolMgr :public CProtocolMgr
	{
	protected:
		void AssociatePackageType();
		BYTE* GetPackageHeadBuf(int type, int len);
		bool ValidateKeepAlivePackage(LPPackageBase data);
		bool ValidatePackageHead(BYTE buf[]);
		bool ValidatePackageType(int type);

	public:
		CDemoProtocolMgr();
		~CDemoProtocolMgr(){};

		int GetDataLen(BYTE buf[], int len);
		int GetPackageType(BYTE buf[], int len);
	};
}