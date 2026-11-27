#include "CScoreManager.h"
//定数
namespace
{
    //----------------------------------------------------
    // IDごとのスコアの表示座標
    //----------------------------------------------------
    const D3DXVECTOR3 SCORE_POS[] =
    {
        {90.f, 40.f, 0.f}, // ID : 0
        {300.f, 40.f, 0.f},  // ID : 1
        {900.f, 40.f, 0.f},  // ID : 2
        {1110.f, 40.f, 0.f},  // ID : 3
    };

    const int SCORE_[] =
    {
         20,70,33,1110
    };
    // スコアの最大数
    constexpr int Max = 4;
}
//コンストラクタ
CScoreManager::CScoreManager()
    : m_Scores()
{
}

// IDを指定してスコアを生成
void CScoreManager::NewScore()
{
    for (int i = 0; i < Max; i++)
    {
        // スコアオブジェクト生成
        auto score = std::make_unique<CScore>();
        //スプライトを接続
        score->AttachSprite(*CAssetManager::GetSprite2D(L"Number"));
        //IDを設定する
        score->SetID(i);
        //座標を設定
        score->SetPosition(SCORE_POS[i]);
        //スコアの登録
        m_Scores.emplace_back(std::move(score));
    }
}
//更新関数 (point : プレイヤーの獲得ポイント)
void CScoreManager::Update(
    const std::vector<int>& point)
{
    for (auto& score : m_Scores)
    {
        // スコアを更新
        score->Update();

        // プレイヤーIDを取得
        const int playerID = score->GetID();

        // プレイヤーの獲得ポイントをスコアに反映
        score->Fluctuation(point[playerID]);
    }
}
//描画関数
void CScoreManager::Draw()
{
    for (auto& score : m_Scores)
    {
        //描画
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
// ゲーム終了時のスコア登録
void CScoreManager::ResultScore()
{
    for (auto& score : m_Scores)
    {
        //ゲーム終了時にスコアをランキングにスコアを設定
        score->ResultScore();
    }

}

 