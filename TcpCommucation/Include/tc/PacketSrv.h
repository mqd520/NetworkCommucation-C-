#pragma once
#include "PacketHead.h"
#include "Packet.h"
#include "MemoryStream.h"
#include "TcpEvt.h"

namespace tc
{
	// 基于包的通信服务
	class PacketSrv
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: void * pObj:	TcpServce
		// Parameter: bool bBigByteOrder:	是否使用大端字节序
		//************************************
		PacketSrv(void* pObj = NULL, bool bBigByteOrder = true);
		virtual ~PacketSrv();

	protected:
		MemoryStream ms;			// 内存流对象
		void* pObjPS;				// 关联的tcp服务对象
		bool bBigByteOrder;			// 是否采用大端字节序

	private:
		//************************************
		// Method:    获取对端ip
		// Parameter: int clientId
		//************************************
		string GetPeerIp(int clientId = 0);

		//************************************
		// Method:    获取对端port
		// Parameter: int clientId
		//************************************
		int GetPeerPort(int clientId = 0);

	protected:
		//************************************
		// Method:    附加TcpServce对象
		// Parameter: void pObj
		//************************************
		virtual void AttachTcpServiceObj(void* pObj);

		//************************************
		// Method:    获取包头对象
		// Parameter: 包命令
		// Parameter: 包体长度
		//************************************
		virtual PacketHead* GetPacketHead(int cmd, int len);

		//************************************
		// Method:    获取包头长度
		//************************************
		virtual int GetPacketHeadLen();

		//************************************
		// Method:    处理接收缓冲区数据
		// Parameter: pBuf:		缓冲区
		// Parameter: len:		缓冲区长度
		// Parameter: clientId:	客户端id
		//************************************
		virtual void ProcessRecvBuf(BYTE* pBuf, int len, int clientId = 0);

		//************************************
		// Method:    解析包
		//************************************
		virtual void ParsePacket(vector<PacketData>& vec);

		//************************************
		// Method:    解析包头缓冲区
		// Parameter: pBuf:		缓冲区
		// Parameter: len:		缓冲区长度
		//************************************
		virtual PacketHead* ParsePacketHead(BYTE* pBuf, int len);

		//************************************
		// Method:    解析包体缓冲区
		// Parameter: PacketHead * pHead:	包头
		// Parameter: pBuf:		缓冲区
		// Parameter: len:		缓冲区长度
		// Parameter: int * len1 实际缓冲区长度
		//************************************
		virtual BYTE* ParsePacketBody(PacketHead* pHead, BYTE* pBuf, int len, int* len1);

		//************************************
		// Method:    缓冲区转换成包
		// Parameter: cmd:		包命令
		// Parameter: pBuf:		缓冲区
		// Parameter: len:		缓冲区长度
		//************************************
		virtual Packet* BufToPacket(int cmd, BYTE* pBuf, int len);

		//************************************
		// Method:    预处理处理包
		// Parameter: data:	包数据
		//************************************
		virtual void PreProcessPck(PacketData& pd);

		//************************************
		// Method:    处理包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnProcessPck(PacketData& pd);

		//************************************
		// Method:    生成包缓冲区
		// Returns:   缓冲区字节长度
		// Parameter: Packet & pck
		// Parameter: BYTE * pBuf:	缓冲区
		// Parameter: int len:		缓冲区长度
		// Parameter: void * pHeadParam1:	包头附加参数1
		// Parameter: void * pHeadParam2:	包头附加参数2
		// Parameter: void * pPacketParam1:	包体附加参数1
		// Parameter: void * pPacketParam2: 包体附加参数2
		//************************************
		virtual int BuildPacketBuf(Packet& pck, BYTE* pBuf, int len,
			void* pHeadParam1 = NULL, void* pHeadParam2 = NULL, void* pPacketParam1 = NULL, void* pPacketParam2 = NULL);

		//************************************
		// Method:    生成包头缓冲区
		// Returns:   缓冲区字节长度
		// Parameter: int cmd:	包命令
		// Parameter: int len:	包体长度
		// Parameter: BYTE * pBuf:	缓冲区
		// Parameter: int nLen:		缓冲区长度
		// Parameter: void * pParam1:	包头附加参数1
		// Parameter: void * pParam2:	包头附加参数
		//************************************
		virtual int BuildPacketHeadBuf(int cmd, int len, BYTE* pBuf, int nLen, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    生成包体缓冲区
		// Returns:   缓冲区字节长度
		// Parameter: Packet & pck
		// Parameter: BYTE * pBuf:	缓冲区
		// Parameter: int len:		缓冲区长度
		// Parameter: void * pParam1:	包体附加参数1
		// Parameter: void * pParam2:	包体附加参数2
		//************************************
		virtual int BuildPacketBodyBuf(Packet& pck, BYTE* pBuf, int len, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    发包
		// Parameter: Packet & pck
		// Parameter: int clientId
		//************************************
		virtual void SendPacket(Packet& pck, int clientId = 0);

		//************************************
		// Method:    发包
		// Parameter: BYTE * pBuf:	缓冲区
		// Parameter: int len:		缓冲区长度
		// Parameter: int clientId
		//************************************
		virtual void SendPacketBuf(BYTE* pBuf, int len, int clientId = 0);

	public:
		//************************************
		// Method:    是否使用大端字节序
		//************************************
		bool IsBigByteOrder() const;

		//************************************
		// Method:    退出
		//************************************
		virtual void Exit();
	};
}