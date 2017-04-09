#pragma once

//包管理接口
__interface IPackageMgr
{
	BYTE* Unparse(void* data, int* len);
	void* Parse(BYTE* buf, int len);
	void Release(void* data);
};