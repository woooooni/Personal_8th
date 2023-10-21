#pragma once

#include "Client_Defines.h"
#include "State.h"
BEGIN(Engine)
class CModel;
END

BEGIN(Client)

class CState_Tanjiro_Run final : public CState
{
private:
	CState_Tanjiro_Run(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CTransform* pTransform, class CStateMachine* pStateMachine, class CModel* pModel);
	virtual ~CState_Tanjiro_Run() = default;

public:
	HRESULT Initialize(const list<wstring>& AnimationList);

public:
	virtual void Enter_State(void* pArg = nullptr) override;
	virtual void Tick_State(_float fTimeDelta) override;
	virtual void Exit_State() override;

public:
	_float m_fMoveSpeed = 0.f;


public:
	static CState_Tanjiro_Run* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, class CTransform* pTransform, class CStateMachine* pStateMachine, class CModel* pModel, const list<wstring>& AnimationList);
	virtual void Free() override;
};

END