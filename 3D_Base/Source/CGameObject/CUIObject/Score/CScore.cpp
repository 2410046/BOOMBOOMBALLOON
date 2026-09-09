#include "CScore.h"
#include "CGameObject/CUIObject/Ranking/CRanking.h"
#include <algorithm>
namespace
{

    constexpr float Space    = 34.f;   // 数字の間隔

    constexpr float Pop_Power = 50.0f; // スコア増加の演出の強さ
    constexpr float Base_Size = 0.8f;  // 通常時スケール
    constexpr float Max_Scale = 1.0f;  // 最大スケール
    constexpr float Scale_Range = 0.5f;  // 拡大幅

    constexpr float Speed = 0.2f;  // スケール補間速度
    constexpr float Scale_Epsilon = 0.01f; // 収束判定

    constexpr int   Update_Interval = 5;     // 表示更新間隔
    //スコアの上限
    constexpr int Max = 9999;

}
CScore::CScore()
    : m_Score        ( 0 )
    , m_DisplayScore ( m_Score )   
    , m_ID           ( 0 )
    , m_UpdateCounter( 0 )
    , m_Scale        ( 0.8f )
    , m_TargetScale  ( 0.8f ) 
    , m_PrevScore    ( 0 )     
{
    //サイズを設定
    m_vScale = D3DXVECTOR3(0.8f, 0.8f, 1.3f);
    //パターンナンバー
    m_Patten = m_ID;
    //ランキングをリセット
    CRanking::GetInstance()->Reset();
    //コンボ座標
    m_ComPos = D3DXVECTOR3(0.f,0.f,0.f);
}

CScore::~CScore()
{
}
//動作関数
void CScore::Update()
{

    // ===== 表示スコアの加算アニメーション =====
    m_UpdateCounter++; // フレームカウント

    if (m_UpdateCounter >= Update_Interval)
    {
        m_UpdateCounter = 0; // カウンタリセット

        int diff = m_Score - m_DisplayScore; // 実スコアとの差分

        // 1ずつ増減させてゆっくり追従させる
        int step = std::clamp(diff, -1, 1);

        m_DisplayScore += step; // 表示スコア更新
    }
    //スコアが増えた時のアニメーション
    AddAnime();

}
//描画関数
void CScore::Draw()
{
    //プレイヤーによってスコアの色を変える
    m_Patten = m_ID;
    // 数字を描画（m_vPosition は変更しない）
    Number(m_Pos,m_DisplayScore, Space);
}

//スコアを減少
void CScore::DropScore(int i,bool Rhythm)
{
        // スコアを減らす
        m_Score = std::clamp(m_Score - i, 0, m_Score);
}

//スコアを追加
void CScore::AddScore(int i, bool Attack)
{
    //スコアにボーナスを加算
    m_Score = std::clamp(m_Score + i,0, Max);
}
//ゲーム終了時のスコア
void CScore::ResultScore()
{
}
//スコアとコンボの座標を取得
void CScore::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 Compos)
{
    m_Pos = pos; 
    m_ComPos = Compos;
}
//スコアが増えた時のアニメーション
void CScore::AddAnime()
{

    // ===== スコア増加検知（ポップ演出）=====
    if (m_Score > m_PrevScore)
    {
        // 前回よりスコアが増えている場合のみ処理
        int diff = m_Score - m_PrevScore; // 増加量を取得

        // 増加量をもとに演出の強さを決定（0.0～1.0に制限）
        float power = std::clamp(diff / Pop_Power, 0.0f, 1.0f);

        // スケールの目標値を設定（増えるほど大きくなる）
        m_TargetScale = Max_Scale + power * Scale_Range; // 最大で約1.5倍
    }

    // 現在のスコアを保存（次フレーム比較用）
    m_PrevScore = m_Score;

    // ===== スケールを元に戻す（イージング）=====
    float ScaleDiff = m_TargetScale - m_Scale; // 現在と目標の差

    // 徐々に目標値へ近づける（補間）
    m_Scale += ScaleDiff * Speed;

    // ほぼ目標に到達したら固定
    if (std::abs(ScaleDiff) < Scale_Epsilon)
    {
        m_Scale       = Base_Size;  // 元のサイズに戻す
        m_TargetScale = Base_Size;  // 目標もリセット
    }
    //サイズを設定
    m_vScale = D3DXVECTOR3(m_Scale, m_Scale,m_vScale.z);

}
