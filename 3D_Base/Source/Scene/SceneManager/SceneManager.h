#pragma once
#include <memory>
#include"Singleton.h"
class CScene;       //シーンクラス
/********************************************************************************
*	シーンマネージャークラス
**/
class SceneManager
    :public Singleton<SceneManager>
{
public:
    // シーンリスト列挙型.
    enum enList
    {
        Title,		// タイトル.
        Select,     // セレクト
        Game,		// メイン
        Result,		// リザルト.
    };
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
    void NextScene(enList scene);
private:
    //シーンの種類
    void SceneList(enList scene);
private:
    std::unique_ptr<CScene>		m_pScene;
    HWND                        m_hWnd;
};
