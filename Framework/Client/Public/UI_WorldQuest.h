#pragma once

#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_WorldQuest final : public CUI
{
protected:
	CUI_WorldQuest(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CUI_WorldQuest(const CUI_WorldQuest& rhs);
	virtual ~CUI_WorldQuest() = default;

public:
	virtual HRESULT Initialize_Prototype(const UI_INFO& tInfo);
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

protected:
	virtual HRESULT Ready_Components() override;

private:
	HRESULT Bind_ShaderResources();

public:
	static CUI_WorldQuest* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const UI_INFO& tInfo);
	virtual CGameObject* Clone(void* pArg) override; /* 사본객체를 생성할때 원본데이터로부터 복제해올 데이터외에 더 추가해 줘야할 데이터가 있다라면 받아오겠다. */
	virtual void Free() override;
};

END