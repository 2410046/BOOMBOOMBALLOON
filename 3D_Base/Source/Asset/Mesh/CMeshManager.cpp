#include "CMeshManager.h"

static const std::wstring STATIC_MESH_DIR = L"Data\\Mesh\\Static\\";
static const std::wstring SKIN_MESH_DIR = L"Data\\Mesh\\Skin\\";
static const std::wstring MESH_X = L".X";

// コンストラクタ
CMeshManager::CMeshManager()
{
}

// デストラクタ
CMeshManager::~CMeshManager()
{
	Release();
}

// 解放
void CMeshManager::Release()
{
	m_SkinMapList.clear();
	m_StaticMapList.clear();
}


// スタティックメッシュ取得
CStaticMesh* CMeshManager::GetStatic(const std::wstring& name)
{
	return GetInstance()->GetStatic_Internal(name);
}


// スキンメッシュ取得
CSkinMesh* CMeshManager::GetSkin(const std::wstring& name)
{
	return GetInstance()->GetSkin_Internal(name);
}


// スタティックメッシュ取得・生成
CStaticMesh* CMeshManager::GetStatic_Internal(
	const std::wstring& name)
{
	// ----------------------------------------
	// すでに読み込まれているか確認
	// ----------------------------------------

	auto it = m_StaticMapList.find(name);

	if (it != m_StaticMapList.end())
	{
		return it->second.get();
	}


	// ----------------------------------------
	// まだ存在しないので生成
	// ----------------------------------------

	auto mesh = std::make_unique<CStaticMesh>();


	// ----------------------------------------
	// ファイルパスを作成
	//
	// 例：
	//
	// name
	// "Player\\Player01"
	//
	// ↓
	// Data\\Mesh\\Static\\Player\\Player01.X
	// ----------------------------------------

	std::wstring fullPath =
		STATIC_MESH_DIR + name + MESH_X;


	// ----------------------------------------
	// メッシュ読み込み
	// ----------------------------------------

	if (FAILED(mesh->Init(fullPath.c_str())))
	{
		return nullptr;
	}


	// ----------------------------------------
	// マップに保存
	// ----------------------------------------

	CStaticMesh* result = mesh.get();

	m_StaticMapList[name] = std::move(mesh);


	return result;
}


// スキンメッシュ取得・生成
CSkinMesh* CMeshManager::GetSkin_Internal(
	const std::wstring& name)
{
	// すでに読み込まれているか確認
	auto it = m_SkinMapList.find(name);

	if (it != m_SkinMapList.end())
	{
		return it->second.get();
	}


	// まだ存在しないので生成
	auto mesh = std::make_unique<CSkinMesh>();


	// ファイルパス作成
	std::wstring fullPath =
		SKIN_MESH_DIR + name + MESH_X;


	// メッシュ読み込み
	if (FAILED(mesh->Init(fullPath.c_str())))
	{
		return nullptr;
	}


	// マップに保存
	CSkinMesh* result = mesh.get();

	m_SkinMapList[name] = std::move(mesh);


	return result;
}