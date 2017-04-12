#pragma once

#include "ProtocolMgr.h"
#include "DemoPackage.h"

namespace NetworkCommunication
{
	//CDemoProtocolMgrµÄ»ùÀà
	typedef CProtocolMgr < DemoPackageType, DemoPackageBase >	CDemoProtocolMgrBase;

	class CDemoProtocolMgr :public CDemoProtocolMgrBase
	{
	public:
		CDemoProtocolMgr();
		~CDemoProtocolMgr(){};

		void Init();
		BYTE* PacketFromBuf(DemoPackageType type, BYTE buf[], int bufLen, int* packetLen);
		bool ValidateKeepAlivePackage(DemoPackageBase* data);
		int GetDataLen(BYTE buf[], int len);
		DemoPackageType GetPackageType(BYTE buf[], int len);
	};
}