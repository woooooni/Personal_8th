#pragma once

#include "Base.h"

BEGIN(Engine)

class CTarget_Manager final : public CBase
{
	DECLARE_SINGLETON(CTarget_Manager)
private:
	typedef struct tagValueDataInfoDesc
	{
		void* pData;
		_uint iByte;
	}VALUEDATAINFODESC;

public:
	CTarget_Manager();
	virtual ~CTarget_Manager() = default;



public:
	HRESULT Ready_ShadowDepthStencilRenderTargetView(ID3D11Device * pDevice, _uint iWinCX, _uint iWinCY);
	HRESULT Add_RenderTarget(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const wstring& strTargetTag, _uint iSizeX, _uint iSizeY, DXGI_FORMAT eFormat, const _float4* pClearColor);
	HRESULT Add_MRT(const wstring& strMRTTag, const wstring& strTargetTag);

public:
	HRESULT Bind_SRV(const wstring& strTargetTag, class CShader* pShader, const char* pConstantName);

	/* ������ �ִ� ����Ÿ���� ����, ������ ����Ÿ�ٵ�(mrt)�� ��ġ�� ������� ���ε��Ѵ�. */
	HRESULT Begin_MRT(ID3D11DeviceContext* pContext, const wstring& strMRTTag, _bool bClear = true);
	HRESULT Begin_ShadowMRT(ID3D11DeviceContext* pContext, const wstring& strMRTTag);



	/* ���� ���·� �����Ѵ�.(BackBuffer�� ��ġ�� ���Ѵ�.) */
	HRESULT End_MRT(ID3D11DeviceContext* pContext);

#ifdef _DEBUG
public:
	HRESULT Initialize_Debug(const wstring& strTargetTag, _float fX, _float fY, _float fSizeX, _float fSizeY);
	HRESULT Render_Debug(const wstring& strMRTTag, class CVIBuffer* pVIBuffer, class CShader* pShader);
#endif // _DEBUG





public:
	void Set_WipsData(_float* pWispRatios, _float4* pWispPoss, _int pWispNum);
	void Get_WispData(_float** Out_pWispRatios, _float4** Out_pWispPoss, _bool* Out_bIsWisp, _int* Out_iWispNum);
	_float Get_MaxWispRatio() { return m_fMaxRatio; }

	_float Get_RendomNum(_float fMin, _float fMax);
	_int Get_RendomNum_Int(_int iMin, _int iMax);

	_bool Get_Dark() { return m_bDark; }
	void Set_Dark(_bool bDark) { m_bDark = bDark; }

	void Set_PlayerPos(_float3 vPos) { m_vPlayerPos = vPos; }
	_float3 Get_PlayerPos() { return m_vPlayerPos; }


private: // Ŭ�󿡼� �Ѿ�� ���̴� �����͵�
	_bool			m_bIsWisp = false;
	_int			m_iWispNum = 0;
	_float			m_WispRatios[256];
	_float4			m_WispPoss[256];

	_float			m_fMaxRatio = 0.f;

	_bool			m_bDark = false;

	_float3			m_vPlayerPos;


private: /* ������ ����Ÿ�ٵ��� ��ü �� ��Ƴ��´�. */
	map<wstring, class CRenderTarget*>			m_RenderTargets;
	typedef map<wstring, class CRenderTarget*>	RENDERTARGETS;

private: /* ���ÿ� ���ε��Ǿ���� ����Ÿ�ٵ��� LIST�� ������´�. (Diffuse + Normal + Depth, Shader + Specular) */
	map<wstring, list<class CRenderTarget*>>			m_MRTs;
	typedef map<wstring, list<class CRenderTarget*>>	MRTS;

private:
	ID3D11RenderTargetView*					m_pOldRenderTargets[8] = { nullptr };
	ID3D11DepthStencilView*					m_pOldDepthStencil = nullptr;
	ID3D11DepthStencilView*					m_pShadowDeptheStencil = nullptr;


private:
	class CRenderTarget* Find_RenderTarget(const wstring& strTargetTag);
	list<class CRenderTarget*>* Find_MRT(const wstring& strMRTTag);

public:
	virtual void Free() override;
};

END