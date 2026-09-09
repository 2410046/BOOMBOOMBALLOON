#include "AssetManager.h"
AssetManager::AssetManager()
	:m_hWnd()
{
}
AssetManager::~AssetManager()
{
}
//構築関数
HRESULT AssetManager::Create(HWND hWnd)
{
	if (CSoundManager::GetInstance()->Load(hWnd) == false)
	{
		return E_POINTER;
	};
	if (FAILED(CSpriteManager::GetInstance()->Create()))
	{
		return E_POINTER;
	}
	if (FAILED(CMeshManager::GetInstance()->Create()))
	{
		return E_POINTER;
	}
	if (FAILED(CEffect::GetInstance()->Create()))
	{
		return E_POINTER;
	}
	return S_OK;
}
//ロード関数
HRESULT AssetManager::LoadData()
{
	//エフェクトのデータ読み込み
	if (FAILED(CEffect::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}
	if (FAILED(CSpriteManager::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}
	if (FAILED(CMeshManager::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}
	return S_OK;
}

//スタティックメッシュの情報を取得
CStaticMesh* AssetManager::GetStatic(std::string name)
{
	return CMeshManager::GetInstance()->GetStatic(name);
}
//スキンメッシュの情報を取得
CSkinMesh* AssetManager::GetSkin(std::string name)
{
	return CMeshManager::GetInstance()->GetSkin(name);
}
//スプライト2Dの情報を取得
CSprite2D* AssetManager::GetSprite2D(std::string name)
{
	return CSpriteManager::GetInstance()->GetSprite2D(name);
}
//スプライト3Dの情報を取得
CSprite3D* AssetManager::GetSprite3D(std::string name)
{
	return CSpriteManager::GetInstance()->GetSprite3D(name);
}