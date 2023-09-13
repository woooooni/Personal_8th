#pragma once
#include "Character.h"

BEGIN(Client)
class CTanjiro final : public CCharacter
{
private:
	CTanjiro(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strObjectTag);
	CTanjiro(const CTanjiro& rhs);
	virtual ~CTanjiro() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;


protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Ready_States() override;

private:
	HRESULT Ready_Sockets();
	HRESULT Ready_Parts();
	HRESULT Update_Weapon();

public:
	static CTanjiro* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strObjectTag);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

