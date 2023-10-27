#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CModel;
class CShader;
class CTexture;
class CRenderer;
class CTransform;
class CRigidBody;
class CPipeLine;
class CStateMachine;
class CNavigation;
class CHierarchyNode;
END


BEGIN(Client)
class CMonster abstract : public CGameObject
{

public:
#pragma region MONSTER_STATES
	enum MONSTER_STATE { 
		REGEN,
		IDLE, 
		TRACE,  
		JUMP,		
		ATTACK,
		SKILL,
		DAMAGED_BASIC, 
		DAMAGED_BLOW,
		DAMAGED_AIRBORN,
		KNOCKDOWN,
		DIE,
		STATE_END
	};

#pragma endregion
	enum DAMAGE_TYPE { BASIC, BLOW, AIRBONE, TYPE_END};
	enum SOCKET_TYPE { SOCKET_LEFT_FIST, SOCKET_RIGHT_FIST, SOCKET_LEFT_FOOT, SOCKET_RIGTH_FOOT, SOCKET_END };

protected:
	CMonster(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strObjectTag);
	CMonster(const CMonster& rhs);
	virtual ~CMonster() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

public:
	virtual void Collision_Enter(const COLLISION_INFO& tInfo) PURE;
	virtual void Collision_Continue(const COLLISION_INFO& tInfo) PURE;
	virtual void Collision_Exit(const COLLISION_INFO& tInfo) PURE;

public:
	virtual void Set_Infinite(_float fInfiniteTime, _bool bInfinite)
	{
		m_bInfinite = bInfinite;
		m_fInfiniteTime = fInfiniteTime;
		m_fAccInfinite = 0.f;

		Set_ActiveColliders(CCollider::DETECTION_TYPE::HEAD, !bInfinite);
		Set_ActiveColliders(CCollider::DETECTION_TYPE::BODY, !bInfinite);
	}
	_bool Is_Infinite() { return m_bInfinite; }

public:
	CShader* Get_ShaderCom() { return m_pShaderCom; }
	CTransform* Get_TransformCom() { return m_pTransformCom; }
	CModel* Get_ModelCom() { return m_pModelCom; }
	CStateMachine* Get_StateCom() { return m_pStateCom; }
	CRigidBody* Get_RigidBodyCom() { return m_pRigidBodyCom; }

	


public:
	CHierarchyNode* Get_Socket(const wstring& strSocketName);

protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Ready_States() PURE;
	virtual HRESULT Ready_Colliders() PURE;


public:
	virtual void On_Damaged(CGameObject* pAttacker, DAMAGE_TYPE eDamageType, _float fPushPower, _float fAirBornPower = 0.f) {};


protected:
	virtual void AirBorne(_float fForce);
	


protected: /* 해당 객체가 사용해야할 컴포넌트들을 저장하낟. */
	CShader* m_pShaderCom = nullptr;
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CModel* m_pModelCom = nullptr;
	CRigidBody* m_pRigidBodyCom = nullptr;
	CStateMachine* m_pStateCom = nullptr;
	CNavigation* m_pNavigationCom = nullptr;



protected:
	vector<CGameObject*>				m_Parts;
	typedef vector<CGameObject*>		PARTS;

	vector<class CHierarchyNode*>		m_Sockets;
	typedef vector<CGameObject*>		Sockets;
	
	_float m_fAccInfinite = 0.f;
	_float m_fInfiniteTime = 0.2f;
	_bool m_bInfinite = false;

public:
	virtual void Free() override;


};

END

