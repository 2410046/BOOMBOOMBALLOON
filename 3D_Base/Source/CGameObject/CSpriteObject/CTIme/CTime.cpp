#include "CTime.h"
#include <stdio.h>
#include <iostream>

CTime::CTime()
    : m_MaxTime(0)
    , m_FrameTime(timeGetTime() / 1000.0f)

{

    //constexpr float Frame_Offset_Y = 0.01f;   // 枠の微調整オフセット
    //constexpr float Frame_Pos_X = 0.0f;       // 枠の基準X座標
    //constexpr float Frame_Pos_Y = 7.0f;       // 枠の基準Y座標
    //constexpr float Frame_Pos_Z = 11.0f;      // 枠のZ座標（奥行き）
    //constexpr float Offset_Scale = 2.15f;     // オフセット補正係数
    //スプライトを接続
    AttachSprite(*CSpriteManager::GetSprite3D(L"TimeArrow"));
  //  m_vPosition = D3DXVECTOR3(650.f, 35.f, 0.f);
    m_vPosition = D3DXVECTOR3(0.f, 7.f, 18.f);
    //リセット
    Reset();
}

CTime::~CTime()
{
}
//動作関数
void CTime::Update()
{
    // 現在時間取得（秒）
    float currentTime = timeGetTime() / 1000.0f;

    // 前フレームからの経過時間を計算
    float deltaTime = currentTime - m_LastUpdateTime;
    m_LastUpdateTime = currentTime;

    // 経過時間を加算
    m_FrameTime += static_cast<float>(deltaTime);

    // 最大時間以内ならカウント更新
    if (m_Count <= m_MaxTime)
    {
        if (m_FrameTime > m_Count)
        {
            // 現在時間取得（ミリ秒 → 秒）
            m_Count = static_cast<int>(m_FrameTime);
        }
    }

    CSpriteObject::Update();

}

//ゲージの中身
void CTime::Draw(const CCamera* pCamera)
{
    //描画
    //パターン番号を設定
    m_pSprite->SetPatternNo(0, 0);
    //m_vPosition = D3DXVECTOR3(600.f , 140.f, 0.f);
    CSpriteObject::Draw(pCamera);
}
//制限時間を超えたら
bool CTime::MaxTime(int Max)
{
    //制限時間を設定
    m_MaxTime = Max;
    //制限時間を超えたら
    if (m_Count >= m_MaxTime)
    {
        return true;
    }
    return false;
}

//ゲージの枠
void CTime::GaugeFrame(const CCamera* pCamera)
{
        // ゲージ枠の描画位置設定
    constexpr float Frame_Offset_Y = 0.01f;   // 枠の微調整オフセット
    constexpr float Frame_Pos_X = 0.0f;       // 枠の基準X座標
    constexpr float Frame_Pos_Y = 7.0f;       // 枠の基準Y座標
    constexpr float Frame_Pos_Z = 11.0f;      // 枠のZ座標（奥行き）
    constexpr float Offset_Scale = 2.15f;     // オフセット補正係数

    // 枠画像のパターン設定（0行目：ゲージ枠）
    m_pSprite->SetPatternNo(0, 0);

    // 枠の表示位置設定
    // Y位置は微調整オフセットを加えて中央に合わせる
    m_vPosition = D3DXVECTOR3(
        Frame_Pos_X,
        Frame_Pos_Y + Frame_Offset_Y / Offset_Scale,
        Frame_Pos_Z
    );

    // スプライト描画
    CSpriteObject::Draw(pCamera);
}
//初期化
void CTime::Reset()
{
    // 秒カウント初期化
    m_Count = 0;
    // 経過時間初期化
    m_FrameTime = 0.0f;
    // 現在時間を基準時間として設定
    // （最初のフレームのデルタタイム補正）
    m_LastUpdateTime = timeGetTime() / 1000.0f;
}
