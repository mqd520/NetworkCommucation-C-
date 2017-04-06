#include "stdafx.h"
#include "Package3Mgr.h"
#include "ProtocolTool.h"
#include "Common.h"

using namespace ProtocolTool;
using namespace Common;

namespace Protocol3
{
	BYTE* CPackage3Mgr::Package31Unparse(LPPackage3Base data, int* len)
	{
		LPPackage31 data1 = (LPPackage31)data;
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

	LPPackage3Base CPackage3Mgr::Package31Parse(BYTE* buf, int len)
	{
		LPPackage31 p = new Package31;
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

	void CPackage3Mgr::Package31Release(LPPackage3Base data)
	{
		LPPackage31 data1 = (LPPackage31)data;
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