#include "CScene.h"

CScene::CScene()
    : m_Start(false)
    , m_Select(0)
    , m_SceneList()
    , m_RequestScene()
    , m_BGM()
{
}
//次に呼ぶシーンの取得
std::string CScene::GetRequestScene() const
{
    return m_RequestScene;
}
// シーン遷移更新
void CScene::UpdateTransition(bool UseSelect)
{
    if (!m_Start)
        return;
    //選択肢を使う場合
    if (UseSelect)
    {
        // フェードアウトが完了するまで待つ
        if (!CFade::GetInstance()->FadeOut())
        {
            return;
        }
    }

    // BGM停止
    CSoundManager::Stop(m_BGM);

    // 遷移先の番号
    int index = 0;

    // 選択番号を使う場合
    if (UseSelect)
    {
        index = m_Select;
    }

    // 選択番号の範囲確認
    if (index < 0 ||
        index >= static_cast<int>(m_SceneList.size()))
    {
        m_Start = false;
        return;
    }

    const std::string& nextScene = m_SceneList[m_Select];

    // 遷移先が空ならゲーム終了
    if (nextScene.empty())
    {
        PostQuitMessage(0);
    }
    else
    {
        // 遷移要求を保存
        m_RequestScene = nextScene;
    }

    m_Start = false;
}