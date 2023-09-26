#pragma once

#include "Base.h"

BEGIN(Engine)

class CData_Manager final : public CBase
{
	DECLARE_SINGLETON(CData_Manager);
public:
	CData_Manager();
	virtual ~CData_Manager() = default;

public:
	HRESULT Reserve_Manager(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	
public:
	HRESULT Export_Model_Data(class CModel* pModel, const wstring& strFolderName, const wstring& strFileName);
	class CModel* Import_Model_Data(_uint eType, wstring strFolderPath, wstring strFileName, _fmatrix PivotMatrix = XMMatrixIdentity());

	

private:
	HRESULT Export_Mesh(const wstring& strFinalPath, class CModel* pModel);
	HRESULT Export_Material(const wstring& strFinalPath, class CModel* pModel);
	HRESULT Export_Animation(const wstring& strFinalPath, class CModel* pModel);
	string Export_Texture(const wstring& strOriginFolder, const string& strSaveFolder, class CTexture* pTexture, _uint iIdx = 0);


private:
	HRESULT Import_Mesh(const wstring strFinalPath, class CModel* pModel);
	HRESULT Import_Material(const wstring strFinalPath, const wstring strFolderPath, class CModel* pModel);
	HRESULT Import_Animation(const wstring strFinalPath, class CModel* pModel);
	HRESULT Import_Texture(const wstring strFinalPath, class CModel* pModel);

private:
	wstring m_strExportFolderPath = L"../Bin/Export/";

private:
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;

public:
	virtual void Free() override;
};

END