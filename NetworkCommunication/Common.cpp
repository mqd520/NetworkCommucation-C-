#include "stdafx.h"
#include "Common.h"

namespace NetworkCommunication
{
	void StrCopy(TCHAR* dest, TCHAR* src)
	{
#ifdef UNICODE
		wcscpy(dest, src);
#else
		
#endif // UNICODE

	}
}