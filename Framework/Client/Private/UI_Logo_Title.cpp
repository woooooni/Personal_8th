#include "stdafx.h"
#include "UI_Logo_Title.h"
#include "Transform.h"
#include "Shader.h"
#include "Transform.h"
#include "VIBuffer_Rect.h"
#include "Texture.h"
#include "Renderer.h"

CUI_Logo_Title::CUI_Logo_Title(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CUI(pDevice, pContext, L"UI_Logo_Title")
{

}

CUI_Logo_Title::CUI_Logo_Title(const CUI_Logo_Title & rhs)
	: CUI(rhs)
{
	
}

HRESULT CUI_Logo_Title::Initialize_Prototype(const UI_INFO& tInfo)
{
	m_tInfo = tInfo;

	

	return S_OK;
}

HRESULT CUI_Logo_Title::Initialize(void* pArg)
{
	if (FAILED(Ready_Components()))
		return E_FAIL;
	
	m_pTransformCom->Set_Scale(XMLoadFloat3(&_float3(m_tInfo.fCX, m_tInfo.fCY, 1.f)));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION,
		XMVectorSet(m_tInfo.fX - g_iWinSizeX * 0.5f, -m_tInfo.fY + g_iWinSizeY * 0.5f, 0.f, 1.f));

	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH(g_iWinSizeX, g_iWinSizeY, 0.f, 1.f));


	return S_OK;
}

void CUI_Logo_Title::Tick(_float fTimeDelta)
{
	Debug_Input(fTimeDelta);
}

void CUI_Logo_Title::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_UI, this);
}

HRESULT CUI_Logo_Title::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	m_pShaderCom->Begin(0);

	m_pVIBufferCom->Render();


	return S_OK;
}

HRESULT CUI_Logo_Title::Ready_Components()
{
	/* Com_Renderer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"),
		TEXT("Com_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTex"),
		TEXT("Com_Shader"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* Com_VIBuffer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"),
		TEXT("Com_VIBuffer"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;


	/* Com_Texture*/
	if (FAILED(__super::Add_Component(LEVEL_LOGO, TEXT("Prototype_Component_Texture_Logo_Title"),
		TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof TransformDesc);

	TransformDesc.fSpeedPerSec = 0.f;
	TransformDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CUI_Logo_Title::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResources(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_ViewMatrix)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_ProjMatrix)))
		return E_FAIL;

	if (FAILED(m_pTextureCom->Bind_ShaderResource(m_pShaderCom, "g_DiffuseTexture", 0)))
		return E_FAIL;

	return S_OK;
}

CUI_Logo_Title * CUI_Logo_Title::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const UI_INFO& tInfo)
{
	CUI_Logo_Title*	pInstance = new CUI_Logo_Title(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype(tInfo)))
	{
		MSG_BOX("Failed to Created : CUI_Logo_Title");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Logo_Title::Clone(void* pArg)
{
	CUI_Logo_Title*	pInstance = new CUI_Logo_Title(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CUI_Logo_Title");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Logo_Title::Free()
{
	__super::Free();
}
