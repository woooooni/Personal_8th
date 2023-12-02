#pragma once

#include "Client_Defines.h"
#include "State.h"
BEGIN(Engine)
class CRigidBody;
END

BEGIN(Client)

class CState_Tanjiro_Attack final : public CState
{
private:
	CState_Tanjiro_Attack(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CStateMachine* pStateMachine);
	virtual ~CState_Tanjiro_Attack() = default;

public:
	HRESULT Initialize(const list<wstring>& AnimationList);

public:
	virtual void Enter_State(void* pArg = nullptr) override;
	virtual void Tick_State(_float fTimeDelta) override;
	virtual void Exit_State() override;


private:
	class CCharacter* m_pCharacter = nullptr;
	class CSword* m_pSword = nullptr;
	class CGameObject* m_pTarget = nullptr;

private:
	void Input(_float fTimeDelta);
	void Find_Near_Target();
	void Trace_Near_Target();

private:
	_bool m_bSlashEffect[5] = { false, false, false , false, false };

public:
	static CState_Tanjiro_Attack* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CStateMachine* pStateMachine, const list<wstring>& AnimationList);
	virtual void Free() override;
};

END