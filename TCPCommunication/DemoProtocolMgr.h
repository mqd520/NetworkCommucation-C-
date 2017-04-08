#pragma once

#include "ProtocolMgr.h"
#include "DemoPackage.h"

namespace TCPCommunication
{
	//CDemoProtocolMgrµÄ»ùÀà
	typedef CProtocolMgr < DemoPackageType, DemoPackageBase >	CDemoProtocolMgrBase;

	class CDemoProtocolMgr :public CDemoProtocolMgrBase
	{
	public:
		CDemoProtocolMgr();
		~CDemoProtocolMgr(){};

		void Init();
		BYTE* PacketFromBuf(DemoPackageType type, BYTE buf[], int bodyLen, int* packetLen);
		bool ValidateKeepAlivePackage(DemoPackageBase* data);
	private:

	};
}