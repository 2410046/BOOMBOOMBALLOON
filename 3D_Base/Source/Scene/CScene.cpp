#include "CScene.h"

CScene::CScene()
    : m_Start(false)
    , m_Select(0)
    , m_BGM()       
    , m_NextScene()
{
}
// シーン遷移設定
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
        index >= static_cast<int>(m_NextScene.size()))
    {
        m_Start = false;
        return;
    }

    const std::string& nextScene = m_NextScene[m_Select];

    // 遷移先が空ならゲーム終了
    if (nextScene.empty())
    {
        PostQuitMessage(0);
    }
    else
    {
        // シーン切り替え
        SceneManager::GetInstance()->NextScene(nextScene);
    }

    m_Start = false;
}