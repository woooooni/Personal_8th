#pragma once

#include "Client_Defines.h"
#include "State.h"

BEGIN(Engine)

class CRigidBody;
class CModel;

END

BEGIN(Client)

class CState_Character_Battle_Dash final : public CState
{
private:
	CState_Character_Battle_Dash(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CStateMachine* pStateMachine);
	virtual ~CState_Character_Battle_Dash() = default;

public:
	HRESULT Initialize(const list<wstring>& AnimationList);

public:
	virtual void Enter_State(void* pArg = nullptr) override;
	virtual void Tick_State(_float fTimeDelta) override;
	virtual void Exit_State() override;


private:
	void Input();

private:
	class CRigidBody* m_pRigidBody = nullptr;
	_bool m_bRight = false;

public:
	static CState_Character_Battle_Dash* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CStateMachine* pStateMachine, const list<wstring>& AnimationList);
	virtual void Free() override;
};

END