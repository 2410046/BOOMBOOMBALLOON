#include "SceneManager.h"

#include "Scene/Title/CTitle.h"     //タイトルクラス
#include "Scene/CSelect/CSelect.h"  //セレクトクラス
#include "Scene/CGame/CGame.h"      //ゲームクラス
#include "Scene/CResult/CResult.h"  //リザルトクラス
SceneManager::SceneManager()
    : m_pScene(nullptr)
    , m_hWnd()
    , m_Transitioning(false)
    , m_Select( 0 )
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
// シーン遷移設定
void SceneManager::SetTransition(
    const std::wstring& bgm, const std::vector<std::string>& nextScene)
{
    m_BGM = bgm;
  //  m_NextScene = nextScene;
    m_NextScene =  nextScene;
    m_Transitioning = false;
}
// シーン遷移開始
void SceneManager::StartTransition()
{
    if (m_Transitioning)
        return;

    m_Transitioning = true;
}
// シーン遷移更新
void SceneManager::UpdateTransition(int select,bool &m_Transitioning)
{




    if (!m_Transitioning)
        return;

    // フェードアウトが完了するまで待つ
    if (!CFade::GetInstance()->FadeOut())
        return;

    // BGM停止
    CSoundManager::Stop(m_BGM.c_str());

    // 選択番号の範囲確認
    if (select < 0 ||
        select >= static_cast<int>(m_NextScene.size()))
    {
        m_Transitioning = false;
        return;
    }

    const std::string& nextScene = m_NextScene[select];

    // 遷移先が空ならゲーム終了
    if (nextScene.empty())
    {
        PostQuitMessage(0);
    }
    else
    {
        // シーン切り替え
        NextScene(nextScene);
    }

    m_Transitioning = false;
}
//シーンの種類
void SceneManager::SceneList(const std::string& scene)
{
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


//if (!m_Transitioning)
//    return;

//// フェードアウト完了まで待つ
//if (!CFade::GetInstance()->FadeOut())
//    return;

//// BGM停止
//CSoundManager::Stop(m_BGM.c_str());

//// 選択番号の範囲確認
//if (select < 0 ||
//    select >= static_cast<int>(m_NextScene.size()))
//{
//    m_Transitioning = false;
//    return;
//}

//// 遷移先を取得
//const std::string& nextScene = m_NextScene[select];

//if (nextScene.empty())
//{
//    // ゲーム終了
//    PostQuitMessage(0);
//}
//else
//{
//    // シーン切り替え
//    NextScene(nextScene);
//}

//m_Transitioning = false;