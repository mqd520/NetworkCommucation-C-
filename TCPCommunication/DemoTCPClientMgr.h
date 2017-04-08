#pragma once

#include "TCPClientMgr.h"
#include "DemoPackage.h"
#include "DemoPackageMgr.h"
#include "DemoProtocolMgr.h"

using namespace ProtocolMgr;
using namespace TCPCLientMgr;

typedef CTCPClientMgr < DemoPackageType, DemoPackageBase, CDemoProtocolMgr >	CDemoTCPClientMgrBase;

class CDemoTCPClientMgr :public CDemoTCPClientMgrBase
{
public:
	CDemoTCPClientMgr();
	~CDemoTCPClientMgr();

private:

};