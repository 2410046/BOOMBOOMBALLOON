#pragma once
#include <memory>
#include"Singleton.h"
#include <string>
#include <vector>
class CScene;       //シーンクラス
/********************************************************************************
*	シーンマネージャークラス
**/
class SceneManager
    :public Singleton<SceneManager>
{
private:
    friend class Singleton<SceneManager>;
    SceneManager();
public:
    ~SceneManager();
    // 最初のシーンを構築
    HRESULT NewScene(HWND hWnd);
    // 現在のシーンを更新
    void Update();
    // 現在のシーンを描画
    void Draw();
    // 現在のシーンを解放
    void Release();
    // シーン切り替え
    void NextScene(const std::string& scene);
    // シーン遷移設定
    void SetTransition(
        const std::wstring& bgm,
        const std::vector<std::string>& nextScene);
    // 遷移開始
    void StartTransition();
    // シーン遷移更新
    void UpdateTransition(int select,bool &m_Transitioning);
private:
    //シーンの種類
    void SceneList(const std::string& scene);
private:
    std::unique_ptr<CScene>		m_pScene;
    HWND                        m_hWnd;
    std::wstring m_BGM;
    std::vector<std::string> m_NextScene;

    bool m_Transitioning;
    int m_Select;
};
