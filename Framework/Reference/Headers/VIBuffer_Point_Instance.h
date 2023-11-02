#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Point_Instance final : public CVIBuffer
{
private:
	CVIBuffer_Point_Instance(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVIBuffer_Point_Instance(const CVIBuffer_Point_Instance& rhs);
	virtual ~CVIBuffer_Point_Instance() = default;

public:
	virtual HRESULT Initialize_Prototype(_uint iNumInstance);
	virtual HRESULT Initialize(void* pArg);

public:
	void Update(_float fTimeDelta);

public:
	virtual HRESULT Render();

private:
	_uint					m_iNumInstance = 0;
	_uint					m_iInstanceStride = 0;
	ID3D11Buffer*			m_pVBInstance = nullptr;

	_float*					m_pInstanceSpeeds = nullptr;

public:
	static CVIBuffer_Point_Instance* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, _uint iNumInstance);
	virtual CComponent* Clone(void* pArg);
	virtual void Free();
};

END