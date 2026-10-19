#pragma once
#include <memory>
#include"Singleton.h"
#include <string>
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
private:
    //シーンの管理データつかわんかも
    struct SceneData
    {
        std::string Name;              //シーンの名前
        std::unique_ptr<CScene>	pScene;  //シーン
    };
    //シーンの種類
    void SceneList(const std::string& scene);
private:
    std::unique_ptr<CScene>		m_pScene;
    HWND                        m_hWnd;
};
