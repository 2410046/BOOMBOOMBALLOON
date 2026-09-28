#include "CScoreManager.h"

//コンストラクタ
CScoreManager::CScoreManager()
    : m_Scores()
{
}
//定数
namespace
{
    //----------------------------------------------------
    // IDごとのスコア表示位置
    //----------------------------------------------------
    const D3DXVECTOR3 SCORE_POS[] =
    {
        {90.f, 40.f, 0.f}, // ID : 0
        {300.f, 40.f, 0.f},  // ID : 1
        {900.f, 40.f, 0.f},  // ID : 2
        {1110.f, 40.f, 0.f},  // ID : 3
    };
}
// IDを指定してスコアを生成
void CScoreManager::NewScore(int ID)
{
     // スコアオブジェクト生成
     auto score = std::make_unique<CScore>();
     //スプライトを接続
     score->AttachSprite(*CSpriteManager::GetSprite2D(L"Number"));
     //IDを設定する
     score->SetID(ID);
     //座標を設定
     score->SetPos(SCORE_POS[ID]);
     //スコアの登録
     m_Scores.emplace_back(std::move(score));

}
//更新関数
void CScoreManager::Update(const std::vector<bool>& hit,
    const std::vector<bool>& down)
{

    for (auto& score : m_Scores)
    {
        score->Update();

        const int playerNo = score->GetID();
        //スコアを増減する
        score->Fluctuation(
            hit[playerNo],
            down[playerNo]
        );
    }
}
//描画関数
void CScoreManager::Draw()
{
    for (auto& score : m_Scores)
    {
        score->Draw();
    }
}
// プレイヤーIDから対応するスコアオブジェクトを取得
CScore* CScoreManager::GetScore(int ID)
{
    if (ID >= 0 && ID < static_cast<int>(m_Scores.size()))
    {
        return m_Scores[ID].get(); // 所有権は保持したままポインタを返す

    }
    return nullptr;
}
// 全プレイヤーのスコアを取得
void CScoreManager::ResultScore()
{
    for (auto& score : m_Scores)
    {
        score->ResultScore();
    }

}

 