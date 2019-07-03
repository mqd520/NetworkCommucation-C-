#pragma once
#include "Def.h"

#include "tc/PacketSrv.h"
#include "tc/Packet.h"
using namespace tc;

namespace pck
{
	// IGPacketSrv
	class IGPacketSrv : public PacketSrv
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: void * pObj: TcpService
		// Parameter: EServerType localType:	本地服务器类型
		// Parameter: EServerType peerType:		对端服务器类型
		//************************************
		IGPacketSrv(EServerType localType = EServerType::None, EServerType peerType = EServerType::None);
		virtual ~IGPacketSrv();

	protected:
		EServerType localType;		// 本地服务器类型
		EServerType peerType;		// 对端服务器类型

	protected:
		//************************************
		// Method:    获取包头对象
		//************************************
		virtual PacketHead* GetPacketHead(int cmd, int len) override;

		//************************************
		// Method:    获取包头长度
		//************************************
		virtual int GetPacketHeadLen() override;

		//************************************
		// Method:    解析包体缓冲区
		// Parameter: PacketHead * pHead:	包头
		// Parameter: pBuf:		缓冲区
		// Parameter: len:		缓冲区长度
		// Parameter: int * len1 实际缓冲区长度
		//************************************
		virtual BYTE* ParsePacketBody(PacketHead* pHead, BYTE* pBuf, int len, int* len1) override;

		//************************************
		// Method:    缓冲区转换成包
		// Parameter: cmd:		包命令
		// Parameter: pBuf:		缓冲区
		// Parameter: len:		缓冲区长度
		//************************************
		virtual Packet* BufToPacket(int cmd, BYTE* pBuf, int len) override;

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
		virtual void SendPacket(Packet& pck, int clientId = 0) override;

	public:
		//************************************
		// Method:    获取本地服务器类型
		// Returns:   pck::EServerType
		//************************************
		virtual EServerType GetLocalServerType();

		//************************************
		// Method:    获取对端服务器类型
		// Returns:   pck::EServerType
		//************************************
		virtual EServerType GetPeerServerType();
	};
}