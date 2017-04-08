#include "stdafx.h"
#include "ProtocolTool.h"
#include "Common.h"
#include "DemoPackageMgr.h"

using namespace ProtocolTool;
using namespace Common;
using namespace PackageMgr;

namespace PackageMgr
{
	BYTE* CDemoPackageMgr::DemoPackage1Unparse(LPDemoPackageBase data, int* len)
	{
		LPDemoPackage1 data1 = (LPDemoPackage1)data;
		int usernameByteLen = GetStrByteCount(data1->strUsername);
		int pwdByteLen = GetStrByteCount(data1->strPwd);
		*len = 2 + usernameByteLen + 2 + pwdByteLen;
		BYTE* buf = new BYTE[*len];
		buf[0] = GetTrdByteFromInt(usernameByteLen);
		buf[1] = GetFouthByteFromInt(usernameByteLen);
		memcpy(buf + 2, data1->strUsername, usernameByteLen);
		buf[2 + usernameByteLen + 0] = GetTrdByteFromInt(pwdByteLen);
		buf[2 + usernameByteLen + 1] = GetFouthByteFromInt(pwdByteLen);
		memcpy(buf + 2 + usernameByteLen + 2, data1->strPwd, pwdByteLen);
		return buf;
	}

	LPDemoPackageBase CDemoPackageMgr::DemoPackage1Parse(BYTE* buf, int len)
	{
		LPDemoPackage1 p = new DemoPackage1;
		if (len > 2)
		{
			int usernameByteLen = MergeByte(buf[1], buf[0]);
			p->strUsername = new wchar_t[usernameByteLen / 2];
			memcpy(p->strUsername, buf + 2, usernameByteLen);
			if (len > (2 + usernameByteLen + 2))
			{
				int pwdByteLen = MergeByte(buf[2 + usernameByteLen + 1], buf[2 + usernameByteLen + 0]);
				p->strPwd = new wchar_t[pwdByteLen / 2];
				memcpy(p->strPwd, buf + 2 + usernameByteLen + 2, pwdByteLen);
			}
		}
		else
		{
			p->strUsername = NULL;
			p->strPwd = NULL;
		}
		return p;
	}

	void CDemoPackageMgr::DemoPackage1Release(LPDemoPackageBase data)
	{
		LPDemoPackage1 data1 = (LPDemoPackage1)data;
		if (data1)
		{
			if (data1->strUsername)
			{
				delete data1->strUsername;
				data1->strUsername = NULL;
			}
			if (data1->strPwd)
			{
				delete data1->strPwd;
				data1->strPwd = NULL;
			}
			delete data1;
		}
	}
}