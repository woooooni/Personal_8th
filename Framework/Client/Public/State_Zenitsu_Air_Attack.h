#pragma once

#include "Client_Defines.h"
#include "State.h"

BEGIN(Client)

class CState_Zenitsu_Air_Attack final : public CState
{
private:
	CState_Zenitsu_Air_Attack(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CStateMachine* pStateMachine);
	virtual ~CState_Zenitsu_Air_Attack() = default;

public:
	HRESULT Initialize(const list<wstring>& AnimationList);

public:
	virtual void Enter_State(void* pArg = nullptr) override;
	virtual void Tick_State(_float fTimeDelta) override;
	virtual void Exit_State() override;


private:
	class CGameObject* m_pTarget = nullptr;
	class CCharacter* m_pCharacter = nullptr;
	class CSword* m_pSword = nullptr;

private:
	void Input(_float fTimeDelta);
	void Find_Near_Target();
	void Use_Skill(_float fTimeDelta);

public:
	static CState_Zenitsu_Air_Attack* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CStateMachine* pStateMachine, const list<wstring>& AnimationList);
	virtual void Free() override;
};

END