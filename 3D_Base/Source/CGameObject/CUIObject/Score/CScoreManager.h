#pragma once
#include "CScore.h" 

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
    void NewScore();
    //更新関数 (point : プレイヤーの獲得ポイント)
    void Update(const std::vector<int>& point);
    // 描画関数
    void Draw();
    // プレイヤーIDから対応するスコアオブジェクトを取得
    CScore* GetScore(int ID);
    // ゲーム終了時のスコア登録
    void ResultScore();
private:
    std::vector<std::unique_ptr<CScore>> m_Scores; // スコア
};