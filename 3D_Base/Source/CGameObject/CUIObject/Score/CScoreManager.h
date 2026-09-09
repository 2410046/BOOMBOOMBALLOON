#pragma once
#include <vector>
#include <memory>
#include "CScore.h"  //スコアクラス
#include "Asset/Sprite/CSpriteManager.h"

/********************************************************************************
*	スコアマネージャークラス
**/
class CScoreManager
{
public:
    //コンストラクタ
    CScoreManager();
    //デストラクタ
    ~CScoreManager() = default;

    // スコアの生成
    void NewScore(int ID);
    // 動作関数
    void Update();
    // 描画関数
    void Draw();
    //プレイヤーIDを指定してスコアを追加
    void AddScore(int ID, int i,bool Attack = false);
    //プレイヤーIDを指定してスコアを減少
    void DropScore(int ID, int i,bool Rhythm = false);
    // プレイヤーIDから対応するスコアオブジェクトを取得
    CScore* GetScore(int ID);
    // 全プレイヤーのスコアを取得
    void ResultScore();
private:
    std::vector<std::unique_ptr<CScore>> m_Scores; // スコア
};