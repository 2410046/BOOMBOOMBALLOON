#include "CSpriteManager.h"
static const std::wstring TEX_PNG = L".png";
CSpriteManager::CSpriteManager()
    : m_3DMapList()
    , m_2DMapList()
    , m_3DData()
    , m_2DData()
{
}
CSpriteManager::~CSpriteManager()
{
    //解放
    Release();
}

//解放
void CSpriteManager::Release()
{
    m_3DMapList.clear();
    m_2DMapList.clear();
}
//全てのスプライトを生成
HRESULT CSpriteManager::Create()
{
    // 2Dスプライト生成
    if (FAILED(CreateSprite2D()))
    {
        return E_POINTER; 
    }
    // 3Dスプライト生成
    if (FAILED(CreateSprite3D()))
    {
        return E_POINTER;
    }

    return S_OK; // 成功
}
//全てのスプライトを読み込む
HRESULT CSpriteManager::LoadData()
{
    // スプライト2Dの読み込み
    if (FAILED(LoadSprite2D()))
    {
        return E_POINTER;
    }
    // スプライト3Dの読み込み
    if (FAILED(LoadSprite3D()))
    {
        return E_POINTER;
    }

    return S_OK; // 成功
}
//スプライト2Dの情報を取得
CSprite2D* CSpriteManager::GetSprite2D(std::wstring name)
{
    return GetInstance()->Sprite2D_Internal(name);
}
//スプライト3Dの情報を取得
CSprite3D* CSpriteManager::GetSprite3D(std::wstring name)
{
    return GetInstance()->Sprite3D_Internal(name);
}
// スプライト2D生成
HRESULT CSpriteManager::CreateSprite2D()
{

    //スプライト2Dの構造体
    CSprite2D::SPRITE_STATE SSSel    = { 190.f, 70.f , 147.f, 160.f, 147.f, 53.f };
    CSprite2D::SPRITE_STATE SSText   = { 240.f, 60.f, 320.f, 185.f, 160.f, 60.f };
  
    CSprite2D::SPRITE_STATE SSLogo   = { 825.f, 276.f, 825.f, 276.f, 825.f, 276.f };
    CSprite2D::SPRITE_STATE SSNumber = { 42.f, 42.f, 590.f, 364.f, 59.f, 90.f };
    CSprite2D::SPRITE_STATE SSActive = { 142.f, 80.f, 423.f, 427.f, 423.f, 85.f };
    CSprite2D::SPRITE_STATE SSRank   = { 403.f, 554.f, 1612.f, 554.f, 403.f, 554.f };

    CSprite2D::SPRITE_STATE SSTime    = { 121.f, 145.f , 451.f, 575.f, 451.f, 575.f };
    CSprite2D::SPRITE_STATE SSArrow   = { 20.f, 50.f,141.f, 252.f, 70.f, 252.f };

    // スプライトのデータリスト
    Sprite2DData DataList[] =
    {
        { L"Text",     SSSel    },
        { L"Logo",     SSLogo   },
        { L"Number",     SSNumber },
        { L"ActiveUser", SSActive },
        { L"Rank",       SSRank },

        { L"Time",            SSTime },
        { L"TimeArrow",       SSArrow },
        
    };
    // データを登録
    for (const auto& data : DataList)
    {
        //スプライト2Dデータに登録
        RegisterSprite2D(data);
    }
    // 各スプライトデータをマップに作成
    for (auto& sprite2D : m_2DData)
    {
        //インスタンス生成
        m_2DMapList[sprite2D.File] = std::make_unique<CSprite2D>();
    }
    return S_OK;

}

// スプライト3D生成
HRESULT CSpriteManager::CreateSprite3D()
{
    //スプライト構造体
    CSprite3D::SPRITE_STATE SSBack
        = { 33.f, 20.f, 33.f, 20.f, 33.f, 20.f };
    CSprite3D::SPRITE_STATE SSSelectBack
        = { 18.f, 35.f, 33.f, 20.f, 33.f, 20.f };
    CSprite3D::SPRITE_STATE SSFade
        = { 1289.f, 780.f, 1280.f, 480.f, 33.f, 20.f };
    CSprite3D::SPRITE_STATE SSArrow
        = { 2.f, 5.f,141.f, 252.f, 70.f, 252.f };
    // スプライト3Dのデータリスト
    Sprite3DData DataList[] =
    {
        { L"TestSky", SSSelectBack}, //リザルト
        { L"Black" , SSFade}, //フェード
        { L"TimeArrow",       SSArrow },
    };

    // データを登録
    for (const auto& data : DataList)
    {
        //スプライト3Dデータに登録
        RegisterSprite3D(data);
    }

    // 各スプライトデータをマップに作成
    for (auto & sprite3D : m_3DData)
    {
        //インスタンス生成
        m_3DMapList[sprite3D.File] = std::make_unique<CSprite3D>();
    }
    return S_OK;
}

//スプライト2Dの読み込み
HRESULT CSpriteManager::LoadSprite2D()
{
    // ファイルが格納されているディレクトリパス
    static const std::wstring TEX_DIR = L"Data\\Texture\\";
    // 登録済みの2Dスプライトデータリストを順番に処理
    for (auto& sprite2D : m_2DData)
    {
        // ディレクトリパスとファイル名を結合
        std::wstring fullPath =
            TEX_DIR + sprite2D.File + TEX_PNG;

        // スプライトの初期化処理
        if (FAILED(m_2DMapList[sprite2D.File]->
            Init(fullPath.c_str(), sprite2D.State)))
        {
            // 初期化に失敗した場合は即座に E_FAIL を返す
            return E_FAIL;
        }
    }
    // 全ての2Dスプライトが正常に初期化された場合
    return S_OK;
}
// スプライト3D読み込み
HRESULT CSpriteManager::LoadSprite3D()
{
    // ファイルが格納されているディレクトリパス
    static const std::wstring TEX_DIR = L"Data\\Texture\\";
    // 登録済みの3Dスプライトデータリストを順番に処理
    for (auto& sprite3D : m_3DData)
    {
        // ディレクトリパスとファイル名を結合
        std::wstring fullPath = TEX_DIR + sprite3D.File + TEX_PNG;

        // スプライトの初期化処理
        if (FAILED(m_3DMapList[sprite3D.File]->
            Init(fullPath.c_str(), sprite3D.State)))
        {
            // 初期化に失敗した場合は即座に E_FAIL を返す
            return E_FAIL;
        }
    }
    // 全ての2Dスプライトが正常に初期化された場合
    return S_OK;
}

//スプライト2Dデータに登録
void CSpriteManager::RegisterSprite2D(const Sprite2DData& data)
{
    m_2DData.push_back(data);
}
//スプライト3Dデータに登録
void CSpriteManager::RegisterSprite3D(const Sprite3DData& data)
{
    m_3DData.push_back(data);
}
CSprite2D* CSpriteManager::Sprite2D_Internal(std::wstring name)
{
    auto it = m_2DMapList.find(name);
    if (it != m_2DMapList.end())
    {
        return it->second.get();
    }
    return nullptr;
}

// スプライト3Dをマップから取得
CSprite3D* CSpriteManager::Sprite3D_Internal(std::wstring name)
{
    auto it = m_3DMapList.find(name);
    if (it != m_3DMapList.end())
    {
        return it->second.get();
    }
    return nullptr;
}

