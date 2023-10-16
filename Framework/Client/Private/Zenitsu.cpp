#include "stdafx.h"
#include "Zenitsu.h"
#include "GameInstance.h"
#include "HierarchyNode.h"
#include "Sword.h"
#include "Sweath.h"

USING(Client)


CZenitsu::CZenitsu(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strObjectTag)
	: CCharacter(pDevice, pContext, strObjectTag)
{
}

CZenitsu::CZenitsu(const CZenitsu& rhs)
	: CCharacter(rhs)
{

}

HRESULT CZenitsu::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CZenitsu::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	if (FAILED(Ready_Sockets()))
		return E_FAIL;

	if (FAILED(Ready_Parts()))
		return E_FAIL;

	if (FAILED(Ready_States()))
		return E_FAIL;

	return S_OK;
}

void CZenitsu::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CZenitsu::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CZenitsu::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CZenitsu::Ready_Components()
{
	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Shader_AnimModel"), TEXT("Com_Shader"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Model_Zenitsu"), TEXT("Com_Model"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_StateMachine"), TEXT("Com_StateMachine"), (CComponent**)&m_pStateCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CZenitsu::Ready_States()
{
	return S_OK;
}

HRESULT CZenitsu::Ready_Sockets()
{
	if (nullptr == m_pModelCom)
		return E_FAIL;

	m_Sockets.resize(SOCEKT_END);

	m_Sockets[SOCKET_SWORD] = m_pModelCom->Get_HierarchyNode(L"R_HandCommon_1_Lct");
	m_Sockets[SOCKET_RIGHT_HAND] = m_pModelCom->Get_HierarchyNode(L"R_Hand_1");
	m_Sockets[SOCKET_SWEATH] = m_pModelCom->Get_HierarchyNode(L"L_Weapon_1_Lct");

	return S_OK;
}

HRESULT CZenitsu::Ready_Parts()
{
	CSweath::SWEATH_DESC			SweathDesc;
	SweathDesc.pParentTransform = m_pTransformCom;
	SweathDesc.pSocketBone = m_Sockets[SOCKET_SWEATH];
	XMStoreFloat4x4(&SweathDesc.SocketPivot, m_pModelCom->Get_PivotMatrix());

	CGameObject* pGameObject = GI->Clone_GameObject(TEXT("Prototype_GameObject_Zenitsu_Sweath"), LAYER_TYPE::LAYER_CHARACTER, &SweathDesc);
	if (nullptr == pGameObject)
		return E_FAIL;

	m_Parts.push_back(pGameObject);


	CSword::SWORD_DESC			SwordDesc;

	SwordDesc.pParentTransform = m_pTransformCom;
	SwordDesc.pSocketBone = m_Sockets[SOCKET_SWORD];
	XMStoreFloat4x4(&SwordDesc.SocketPivot, m_pModelCom->Get_PivotMatrix());

	pGameObject = GI->Clone_GameObject(TEXT("Prototype_GameObject_Zenitsu_Sword"), LAYER_TYPE::LAYER_CHARACTER, &SwordDesc);
	if (nullptr == pGameObject)
		return E_FAIL;

	m_Parts.push_back(pGameObject);


	return S_OK;
}


CZenitsu* CZenitsu::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strObjectTag)
{
	CZenitsu* pInstance = new CZenitsu(pDevice, pContext, strObjectTag);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Create Failed : CZenitsu");
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

CGameObject* CZenitsu::Clone(void* pArg)
{
	CZenitsu* pInstance = new CZenitsu(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CZenitsu");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CZenitsu::Free()
{
	__super::Free();
}

