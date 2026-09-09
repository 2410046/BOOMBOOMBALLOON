#include "CMeshManager.h"

CMeshManager::CMeshManager()
{
}
CMeshManager::~CMeshManager()
{
	Release();
}
//解放
void CMeshManager::Release()
{
	m_SkinMapList.clear();
	m_StaticMapList.clear();
	m_SkinData.clear();
	m_StaticData.clear();
}
//すべてのメッシュを生成
HRESULT CMeshManager::Create()
{
	//スタティックメッシュ生成
	if (FAILED(CreateStatic()))
	{
		return E_POINTER;
	}
	//スキンメッシュ生成
	if (FAILED(CreateSkin()))
	{
		return E_POINTER;
	}
	return S_OK;
}
//全てのメッシュを読み込む
HRESULT CMeshManager::LoadData()
{
	//スタティックメッシュの読み込み
	if (FAILED(LoadStatic()))
	{
		return E_POINTER;
	}
	////スキンメッシュの読み込み
	//if (FAILED(LoadSkin()))
	//{
	//	return E_POINTER;
	//}
	return S_OK;
}
//スタティックメッシュの情報を取得
CStaticMesh* CMeshManager::GetStatic(std::string name)
{
	return GetInstance()->GetStatic_Internal(name);
}
//スキンメッシュの情報を取得
CSkinMesh* CMeshManager::GetSkin(std::string name)
{
	return GetInstance()->GetSkin_Internal(name);
}
//スタティックメッシュ生成
HRESULT CMeshManager::CreateStatic()
{
	//スタティックメッシュのデータリスト
	StaticData DataList[] =
	{
		{"Sky01", L"Sky\\Sky1.X"},
		{"Sky02", L"Sky\\Sky2.X"},
		{"Sky03", L"Sky\\Sky3.X"},
		{ "Player01",L"Player\\Player01.X"},
		{ "Player02",L"Player\\Player02.X"},
		{ "Balloon" ,L"Asset\\Balloon.X"},
		{ "Cloud"   ,L"Asset\\Cloud.X"},
		{ "Shot"    ,L"Asset\\Shot.X"},
	};
	//データを登録
	for (const auto& data : DataList)
	{
		//スタティックメッシュデータに登録
		RegisterStatic(data);
	}
	// 各スタティックメッシュのデータをマップに作成
	for (auto& Static : m_StaticData)
	{
		//インスタンス生成
		m_StaticMapList[Static.Name] = std::make_unique<CStaticMesh>();
	}
	return S_OK;
}
//スキンメッシュ生成
HRESULT CMeshManager::CreateSkin()
{
	return S_OK;
}
//スタティックメッシュの読み込み
HRESULT CMeshManager::LoadStatic()
{
	// ファイルが格納されているディレクトリパス
	static const std::wstring TEX_DIR = L"Data\\Mesh\\Static\\";
	// 登録済みのスタティックメッシュデータリストを順番に処理
	for (auto& Static : m_StaticData)
	{
		// ディレクトリパスとファイル名を結合
		std::wstring fullPath = TEX_DIR + Static.File;
		// スタティックメッシュの初期化処理
		if (FAILED(m_StaticMapList[Static.Name]->
			Init(fullPath.c_str())))
		{
			// 初期化に失敗した場合は即座に E_FAIL を返す
			return E_FAIL;
		}
	}
	// 全てのスタティックメッシュが正常に初期化された場合
	return S_OK;
}
//スキンメッシュの読み込み
HRESULT CMeshManager::LoadSkin()
{
	// ファイルが格納されているディレクトリパス
	static const std::wstring TEX_DIR = L"Data\\Mesh\\Skin\\";
	// 登録済みのスキンメッシュデータリストを順番に処理
	for (auto& Skin : m_SkinData)
	{
		// ディレクトリパスとファイル名を結合
		std::wstring fullPath = TEX_DIR + Skin.File;
		// スキンメッシュの初期化処理
		if (FAILED(m_SkinMapList[Skin.Name]->
			Init(fullPath.c_str())))
		{
			// 初期化に失敗した場合は即座に E_FAIL を返す
			return E_FAIL;
		}
	}
	// 全てのスキンメッシュが正常に初期化された場合
	return S_OK;
}
//スタティックメッシュデータに登録
void CMeshManager::RegisterStatic(const StaticData& data)
{
	m_StaticData.push_back(data);
}
//スキンメッシュデータに登録
void CMeshManager::RegisterSkin(const SkinData& data)
{
	m_SkinData.push_back(data);
}
//スタティックメッシュ取得
CStaticMesh* CMeshManager::GetStatic_Internal(std::string name)
{
	auto it = m_StaticMapList.find(name);
	if (it != m_StaticMapList.end())
	{
		return it->second.get();
	}
	return nullptr;
}
//スキンメッシュ取得
CSkinMesh* CMeshManager::GetSkin_Internal(std::string name)
{
	auto it = m_SkinMapList.find(name);
	if (it != m_SkinMapList.end())
	{
		return it->second.get();
	}
	return nullptr;
}
