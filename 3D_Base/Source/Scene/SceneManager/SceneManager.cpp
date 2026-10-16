#include "SceneManager.h"

#include "Scene/Title/CTitle.h"     //タイトルクラス
#include "Scene/CSelect/CSelect.h"  //セレクトクラス
#include "Scene/CGame/CGame.h"      //ゲームクラス
#include "Scene/CResult/CResult.h"  //リザルトクラス
SceneManager::SceneManager() 
    : m_pScene( nullptr ) 
    , m_hWnd  ( )
{
}
SceneManager::~SceneManager() 
{
    //解放
    Release();
}
// 最初のシーンを構築
HRESULT SceneManager::NewScene(HWND hWnd)
{
    m_hWnd = hWnd;
    //最初はタイトルシーン
    NextScene("Title");//Title
    return S_OK;
}


// 現在のシーンを更新
void SceneManager::Update()
{
    if (m_pScene != nullptr)
    {
        m_pScene->Update();
    }
}
// 現在のシーンを描画
void SceneManager::Draw()
{
    if (m_pScene != nullptr)
    { 
        m_pScene->Draw(); 
    }
}

// 現在のシーンを解放
void SceneManager::Release()
{
    if (m_pScene != nullptr)
    {
        m_pScene->Release();     
        m_pScene.reset();        
    }
}

// 現在のシーンを更新
void SceneManager::NextScene(const std::string& scene)
{
    if (m_pScene != nullptr)
    {
        m_pScene->Release(); 
        m_pScene.reset();
    }

    SceneList(scene);

    if (m_pScene)
    {
        m_pScene->Create();
        m_pScene->LoadData();
    }
}
//シーンの種類
void SceneManager::SceneList(const std::string& scene)
{


    //// シーン作成
    //SceneData DataName[]
    //{
    //    {"Title" ,std::make_unique<CTitle>()},
    //    {"Select",std::make_unique<CSelect>()},
    //    {"Game"  ,std::make_unique<CGame>()},
    //    {"Result",std::make_unique<CResult>()},
    //};


    if (scene == "Title")
    {
        m_pScene = std::make_unique<CTitle>();
    }
    else if (scene == "Select")
    {
        m_pScene = std::make_unique<CSelect>();
    }
    else if (scene == "Game")
    {
        m_pScene = std::make_unique<CGame>();
    }
    else if (scene == "Result")
    {
        m_pScene = std::make_unique<CResult>();
    }
}