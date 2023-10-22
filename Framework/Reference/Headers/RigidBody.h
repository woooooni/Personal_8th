#pragma once
#include "Component.h"



BEGIN(Engine)

class ENGINE_DLL CRigidBody : public CComponent
{
public:
    typedef struct tagRigidBodyDesc
    {
        class CTransform* pTransform = nullptr;
        class CNavigation* pNavigation = nullptr;

    } RIGID_BODY_DESC;
private:
    CRigidBody(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    CRigidBody(CRigidBody& rhs);
    virtual ~CRigidBody() = default;


public:
    virtual HRESULT Initialize_Prototype();
    virtual HRESULT Initialize(void* pArg);

public:
    void Tick_RigidBody(_float fTimeDelta);
    void Set_Gravity(_float fGravity) { m_fGravity = fGravity; }
    void Set_Gravity(_bool bGravity) { m_bIsGravity = bGravity; }

    _bool Is_Gravity() { return m_bIsGravity; }

    _bool Is_Ground() { return m_bIsGround; }
    void Set_Ground(_bool bGround) { m_bIsGround = bGround; }

    void Add_Velocity(_fvector vVelocity);
    void Add_Velocity(_fvector vDir, _float fForce);

    void Set_RefHeight(_float fHeight) { m_fRefHeight = fHeight; }
    _float Get_RefHeight() { return m_fRefHeight; }
    

private:
    void Update_Gravity(_float fTimeDelta);
    void Update_Velocity(_float fTimeDelta);

private:
    _float m_fGravity = 9.8f;               // �߷� ���
    _float3 m_vVelocity = { 0.f, 0.f, 0.f };    // ���� �ӵ�
    _float3 m_vMaxVelocity = { 100.f, 100.f, 100.f }; // �ӵ� �ִ�ġ.
    _float3 m_vFriction = { 0.f, 0.f, 0.f };    // ���� �ӵ��� �����ϴ� ������.

    _bool m_bIsGround = true;   // ���� ���� �ִ°�?
    _bool m_bIsGravity = true;  // �߷��� ������ �޴°�?

    _float m_fFrictionScale = 1.f; // ������ ũ��.
    _float m_fRefHeight = 0.f; // ���� Y

private:
    class CTransform* m_pTransformCom = nullptr;
    class CNavigation* m_pNavigationCom = nullptr;

public:
    static CRigidBody* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    virtual CComponent* Clone(void* pArg);
    virtual void Free() override;

};
END