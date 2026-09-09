#include "CTime.h"
#include <stdio.h>
#include <iostream>

CTime::CTime()
    : m_MaxTime(0)

{
    //スプライトを接続
    AttachSprite(*CSpriteManager::GetSprite3D("Time"));
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
    // スプライトの元状態を保存
    // （ゲージ描画でサイズ変更するため）
    CSprite3D::SPRITE_STATE m_OriginalState = m_pSprite->GetSpriteState();

    // 枠を描画（状態を変更しない）
    GaugeFrame(pCamera);

    //----------------------------------------------------
    // ゲージの割合計算
    //----------------------------------------------------
    // 現在時間の割合
    float ratio = static_cast<float>(m_Count) / m_MaxTime;

    // ゲージ表示位置
    constexpr float BaseX  = -4.1f;  //Xの初期座標
    constexpr float BaseY  = 6.9f;   //Yの初期座標
    constexpr float BaseZ  = 10.9f;   //Zの初期座標

    constexpr float Divide = 2.f;   //Yの初期座標

    //サイズ変更
    CSprite3D::SPRITE_STATE ChangeState = m_pSprite->GetSpriteState();

    float BaseWidth = 30.0f;   // 最小幅
    float MaxWidth = 681.0f;   // 最大幅

    // 時間割合に応じてゲージ幅を計算
    float RatioWidth = BaseWidth + (MaxWidth - BaseWidth) * ratio;

    // テクスチャ表示幅変更
    ChangeState.Stride.w = RatioWidth;
    // 表示スケール
    float Scale = 0.012f;
    // 実際の表示幅高さ
    ChangeState.Dips.w = RatioWidth * Scale;
    //スプライト情報を設定
    m_pSprite->SetSpriteState(ChangeState);

    //描画
    //パターン番号を設定
    m_pSprite->SetPatternNo(0, 1);
    m_vPosition = D3DXVECTOR3(BaseX + (ChangeState.Dips.w / Divide ), BaseY, BaseZ);
    CSpriteObject::Draw(pCamera);

    // スプライトの状態を元に戻す（次のフレーム・他の描画に影響しないように）
    m_pSprite->SetSpriteState(m_OriginalState);
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
