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
        {1100.f, 40.f, 0.f}, // ID : 0
        { 200.f, 40.f, 0.f}  // ID : 1
    };

    //----------------------------------------------------
    // IDごとのコンボ表示位置
    //----------------------------------------------------
    const D3DXVECTOR3 COMBO_POS[] =
    {
        {900.f, 40.f, 0.f}, // ID : 0
        { 10.f, 40.f, 0.f}  // ID : 1
    };
}
// IDを指定してスコアを生成
void CScoreManager::NewScore(int ID)
{
     // スコアオブジェクト生成
     auto score = std::make_unique<CScore>();
     //スプライトを接続
     score->AttachSprite(*CSpriteManager::GetSprite2D("Number"));
     //IDを設定する
     score->SetID(ID);
     //座標を設定
     score->SetPos(SCORE_POS[ID], COMBO_POS[ID]);
     //スコアの登録
     m_Scores.emplace_back(std::move(score));

}
//更新関数
void CScoreManager::Update()
{
    for (auto& score : m_Scores)
    {
        score->Update();
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

//プレイヤーIDを指定してスコアを追加
void CScoreManager::AddScore(int ID, int i, bool Attack)
{
    if (ID >= 0 && ID < static_cast<int>(m_Scores.size())) 
    {
        m_Scores[ID]->AddScore(i, Attack);  // 特定のプレイヤーのスコアを追加する
    }
}
//プレイヤーIDを指定してスコアを減少
void CScoreManager::DropScore(int ID, int i, bool Rhythm)
{
    if (ID >= 0 && ID < static_cast<int>(m_Scores.size())) 
    {
        m_Scores[ID]->DropScore(i, Rhythm);  // 特定のプレイヤーのスコアを減少する
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

 