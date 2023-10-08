#include "stdafx.h"
#include "ClientPacketHandler.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "Client_Defines.h"
#include "Level_Loading.h"
#include "Network_Manager.h"
#include "ServerSession.h"
#include "Level_Manager.h"
#include "Utils.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return true;
}

bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
{
	
	return true;
}

bool Handle_C_ENTER_LEVEL(PacketSessionRef& session, Protocol::C_ENTER_LEVEL& pkt)
{
	return true;
}

bool Handle_C_EXIT_LEVEL(PacketSessionRef& session, Protocol::C_EXIT_LEVEL& pkt)
{
	return false;
}

bool Handle_C_CREATE_OBJECT(PacketSessionRef& session, Protocol::C_CREATE_OBJECT& pkt)
{
	CGameObject* pObj = nullptr;
	if(FAILED(GAME_INSTANCE->Add_GameObject(pkt.ilevelindex(), pkt.ilayerindex(), CUtils::ToWString(pkt.strprototypename()), nullptr, &pObj)))
		return false;

	if (nullptr == pObj)
		return false;

	pObj->Set_ObjectTag(CUtils::ToWString(pkt.strname()));

	if (pkt.imodeltype() == CModel::TYPE::TYPE_ANIM)
	{

	}

	CTransform* pTranform = dynamic_cast<CTransform*>(pObj->Get_Component(L"Com_Transform"));
	if (nullptr == pTranform)
		return false;

	
}

bool Handle_C_DELETE_OBJECT(PacketSessionRef& session, Protocol::C_DELETE_OBJECT& pkt)
{
	return true;
}

bool Handle_C_WORLD_MATRIX(PacketSessionRef& session, Protocol::C_WORLD_MATRIX& pkt)
{
	return true;
}

bool Handle_C_CHANGE_ANIMATION(PacketSessionRef& session, Protocol::C_CHANGE_ANIMATION& pkt)
{
	return true;
}

bool Handle_C_CREATE_OBJECT(PacketSessionRef& session, Protocol::C_ENTER_LEVEL& pkt)
{
	
	return true;
}

