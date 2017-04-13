#pragma once

#include "ProtocolMgr.h"
#include "DemoPackage.h"

namespace NetworkCommunication
{
	class CDemoProtocolMgr :public CProtocolMgr < DemoPackageType, DemoPackageBase >
	{
	private:
		//CProtocolMgr基类别名
		typedef CProtocolMgr < DemoPackageType, DemoPackageBase > CDemoProtocolMgrBase;

	protected:
		void AssoicatePackageType();
		void InitPackageHeadBuf(DemoPackageType type, int len);
		bool ValidateKeepAlivePackage(DemoPackageBase* data);

	public:
		CDemoProtocolMgr();
		~CDemoProtocolMgr(){};

		int GetDataLen(BYTE buf[], int len);
		DemoPackageType GetPackageType(BYTE buf[], int len);
	};
}