#pragma once
#include "Monster.h"

BEGIN(Client)
class CMonster_Normal_1 final : public CMonster
{


private:
	CMonster_Normal_1(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strObjectTag, const MONSTER_STAT& tStat);
	CMonster_Normal_1(const CMonster_Normal_1& rhs);
	virtual ~CMonster_Normal_1() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual void Enter_Scene() override;
	virtual void Return_Pool() override;

public:
	virtual void Collision_Enter(const COLLISION_INFO& tInfo) override;
	virtual void Collision_Continue(const COLLISION_INFO& tInfo) override;
	virtual void Collision_Exit(const COLLISION_INFO& tInfo) override;
	virtual void On_Damaged(CGameObject* pAttacker, _uint eDamageType, _float fDamage) override;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Ready_States() override;
	virtual HRESULT Ready_Colliders() override;



	

private:
	HRESULT Ready_Sockets();
	HRESULT Ready_Parts();
	

public:
	static CMonster_Normal_1* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strObjectTag, const MONSTER_STAT& tStat);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
