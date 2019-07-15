#pragma once
#include "TcpEvt.h"

namespace tc
{
	// Recv peer data evt
	class RecvPeerDataEvt : public TcpEvt
	{
	public:
		//************************************
		// Method:    constructor
		// Parameter: Associated TcpService obj
		// Parameter: peer socket
		// Parameter: BYTE * buf:	buf
		// Parameter: int len:		buf length
		//************************************
		RecvPeerDataEvt(TcpService* pSrv, SOCKET recv, BYTE* pBuf, int len);
		~RecvPeerDataEvt();

	private:
		BYTE* pBuf;		// recv buf pointer
		int nLen;		// recv buf length

	public:
		//************************************
		// Method:    Get recv buf
		//************************************
		BYTE* GetRecvBuf();

		//************************************
		// Method:    Get recv buf length
		//************************************
		int GetBufLen();

		//************************************
		// Method:    Read to buf
		// Parameter: BYTE * buf:	buf
		// Parameter: int len:		buf length
		int Read(BYTE* buf, int len);

		//************************************
		// Method:    Write to buf
		// Parameter: BYTE * buf:	buf
		// Parameter: int len:		buf length
		//************************************
		void Write(BYTE* buf, int len);

		//************************************
		// Method:    Reset buf 
		// Parameter: BYTE * buf:	buf
		// Parameter: int len:		buf length
		//************************************
		void ResetBuf(BYTE* buf, int len);
	};
}