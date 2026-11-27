#include "CAssetManager.h"
CAssetManager::CAssetManager()
	:m_hWnd()
{
}
CAssetManager::~CAssetManager()
{
}
//構築関数
HRESULT CAssetManager::Create()
{
	//スプライトの構築
	if (FAILED(CSpriteManager::GetInstance()->Create()))
	{
		return E_POINTER;
	}
	//エフェクトの読み込み
	if (FAILED(CEffect::GetInstance()->Create()))
	{
		return E_POINTER;
	}
	return S_OK;
}
//ロード関数
HRESULT CAssetManager::LoadData(HWND hWnd)
{
	//サウンドデータ読み込み
	if (CSoundManager::GetInstance()->Load(hWnd) == false)
	{
		return E_POINTER;
	};
	//エフェクトのデータ読み込み
	if (FAILED(CEffect::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}
	//スプライトの読み込み
	if (FAILED(CSpriteManager::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}
	return S_OK;
}

//スタティックメッシュの情報を取得
CStaticMesh* CAssetManager::GetStatic(std::wstring name)
{
	return CMeshManager::GetInstance()->GetStatic(name);
}
//スキンメッシュの情報を取得
CSkinMesh* CAssetManager::GetSkin(std::wstring name)
{
	return CMeshManager::GetInstance()->GetSkin(name);
}
//スプライト2Dの情報を取得
CSprite2D* CAssetManager::GetSprite2D(std::wstring name)
{
	return CSpriteManager::GetInstance()->GetSprite2D(name);
}
//スプライト3Dの情報を取得
CSprite3D* CAssetManager::GetSprite3D(std::wstring name)
{
	return CSpriteManager::GetInstance()->GetSprite3D(name);
}