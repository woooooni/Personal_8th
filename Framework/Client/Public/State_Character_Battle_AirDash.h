#pragma once

#include "Client_Defines.h"
#include "State.h"

BEGIN(Engine)

class CRigidBody;
class CModel;

END

BEGIN(Client)

class CState_Character_Battle_AirDash final : public CState
{
private:
	CState_Character_Battle_AirDash(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CStateMachine* pStateMachine);
	virtual ~CState_Character_Battle_AirDash() = default;

public:
	HRESULT Initialize(const list<wstring>& AnimationList);

public:
	virtual void Enter_State(void* pArg = nullptr) override;
	virtual void Tick_State(_float fTimeDelta) override;
	virtual void Exit_State() override;

private:
	class CRigidBody* m_pRigidBody = nullptr;

public:
	static CState_Character_Battle_AirDash* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CStateMachine* pStateMachine, const list<wstring>& AnimationList);
	virtual void Free() override;
};

END