#include "CScore.h"
#include "CGameObject/CUIObject/Ranking/CRanking.h"
namespace
{
    // 数字の描画間隔
    constexpr float Space = 38.0f;

    // スコア増加時の拡大アニメーション用定数
    constexpr float Pop_Power     = 50.0f;  // 拡大演出の強さを決める基準値
    constexpr float Base_Size     = 1.0f;   // 通常時の大きさ
    constexpr float Max_Scale     = 1.2f;   // 基本の拡大率
    constexpr float Scale_Range   = 0.5f;   // 増加量に応じた拡大率の範囲
    constexpr float Speed         = 0.2f;   // 拡大率の補間速度
    constexpr float Scale_Epsilon = 0.01f;  // 拡大率の補間終了判定値

    // スコア制御用定数
    constexpr float Add_Interval        = 80.0f; // 自動加算するまでの間隔

    constexpr int   Max                 = 9999;  // スコアの最大値

}
// コンストラクタ
CScore::CScore()
    : m_Score        ( 0 )
    , m_DisplayScore ( m_Score )   
    , m_Scale        ( 1.f )
    , m_TargetScale  ( 1.f ) 
    , m_PrevScore    ( 0 )     
{
    //サイズを設定
    m_vScale = D3DXVECTOR3(1.f, 1.f, 1.3f);
    // ゲーム開始時にランキング情報を初期化
    CRanking::GetInstance()->Reset();
}
//デストラクタ
CScore::~CScore()
{
}
//動作関数
void CScore::Update()
{
    // 一定間隔ごとにスコアを自動加算
    m_Count++;

    if (std::fmod(m_Count, Add_Interval) == 0.0f)
    {
        // スコアを1加算し、スコアを0～最大値の範囲に制限
        m_Score = std::clamp(m_Score + 1, 0, Max);
        //カウントをリセット
        m_Count = 0.f;
    }
     //数値のカウントアニメーション
     CountUp(m_Score, m_DisplayScore);
    // スコア増加時に数字を拡大
     AddAnime();
}
//描画関数
void CScore::Draw()
{
    // プレイヤーIDに対応した数字の表示パターンを設定
    m_Patten = m_ID;
    // 表示用スコアを描画
    Number(m_DisplayScore, Space);
}
//スコアの増減
void CScore::Fluctuation(int point)
{
    // 加算・減算するポイントをスコアに反映
    m_Score += point;
    // スコアを0～最大値の範囲に制限
    m_Score = std::clamp(m_Score, 0, Max);
}
//ゲーム終了時にスコアをランキングにスコアを設定
void CScore::ResultScore()
{
    // プレイヤーIDとスコアをランキングに登録
    CRanking::GetInstance()->Register(m_ID, m_Score);
}
// スコア増加時のアニメーション
void CScore::AddAnime()
{
    // 前回よりスコアが増えている場合のみ処理
    if (m_Score > m_PrevScore)
    {
        // スコアの増加量を取得
        int diff = m_Score - m_PrevScore;

        // 増加量をもとに演出の強さを決定（0.0～1.0に制限）
        float power = std::clamp(diff / Pop_Power, 0.0f, 1.0f);
        // 増加量に応じてスケールの目標値を設定
        m_TargetScale = Max_Scale + power * Scale_Range;
    }

    // 現在のスコアを保存（次回の増加判定に使用）
    m_PrevScore = m_Score;

    // 現在の拡大率と目標値の差を計算
    float ScaleDiff = m_TargetScale - m_Scale; 

    // 現在の数字のサイズを徐々に目標値へ近づける（補間）
    m_Scale += ScaleDiff * Speed;

    // 目標値にほぼ到達したら通常サイズに戻す
    if (std::abs(ScaleDiff) < Scale_Epsilon)
    {
        // 元のサイズに戻す
        m_Scale       = Base_Size;  
        // 目標値も初期値に戻す
        m_TargetScale = Base_Size;
    }
    //サイズを設定
    m_vScale = D3DXVECTOR3(m_vScale.x, m_Scale,m_vScale.z);

}
