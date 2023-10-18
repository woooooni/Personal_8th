#pragma once

#include "Client_Defines.h"
#include "Part.h"

BEGIN(Engine)
class CHierarchyNode;
class CModel;
class CShader;
class CRenderer;
class CTransform;
END

BEGIN(Client)

class CSweath final : public CPart
{
public:
	typedef struct tagWeaponDesc : public CPart::PART_DESC
	{		
		CHierarchyNode*	pSocketBone = { nullptr };
		_float4x4		SocketPivot;
	} SWEATH_DESC;

protected:
	/* ������ ������ �� */
	CSweath(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strObjectTag);
	/* �纻�� ������ �� */
	CSweath(const CSweath& rhs); /* ���� ������. */

	virtual ~CSweath() = default;

public:
	virtual HRESULT Initialize_Prototype(const wstring& strPrototypeModelName);
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

private:
	wstring					m_strModelPrototype;
	CHierarchyNode*			m_pSocketBone = { nullptr };
	_float4x4				m_SocketPivotMatrix;


private:
	HRESULT Ready_Components();
	HRESULT Bind_ShaderResources();

public:
	static CSweath* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strObjectTag, const wstring& strPrototypeModelName);
	virtual CGameObject* Clone(void* pArg) override; /* �纻��ü�� �����Ҷ� ���������ͷκ��� �����ؿ� �����Ϳܿ� �� �߰��� ����� �����Ͱ� �ִٶ�� �޾ƿ��ڴ�. */
	virtual void Free() override;
};

END