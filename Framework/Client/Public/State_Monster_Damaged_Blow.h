#pragma once

#include "Client_Defines.h"
#include "State.h"
BEGIN(Engine)
class CRigidBody;
END

BEGIN(Client)

class CState_Monster_Damaged_Blow final : public CState
{
private:
	CState_Monster_Damaged_Blow(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CStateMachine* pStateMachine);
	virtual ~CState_Monster_Damaged_Blow() = default;

public:
	HRESULT Initialize(const list<wstring>& AnimationList);

public:
	virtual void Enter_State(void* pArg = nullptr) override;
	virtual void Tick_State(_float fTimeDelta) override;
	virtual void Exit_State() override;

private:
	class CRigidBody* m_pRigidBodyCom = nullptr;
	_bool m_bFirstGround = false;
	_float m_fAccRecovery = 0.f;
	_float m_fRecoveryTime = 3.f;

private:
	class CMonster* m_pOwnerMonster = nullptr;

public:
	static CState_Monster_Damaged_Blow* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CStateMachine* pStateMachine, const list<wstring>& AnimationList);
	virtual void Free() override;
};

END