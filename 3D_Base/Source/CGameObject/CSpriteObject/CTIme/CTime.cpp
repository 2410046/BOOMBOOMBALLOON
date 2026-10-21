#include "CTime.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
namespace
{
    constexpr float m_MaxTime = 10;	// スコアテキストの数
    // 回転速度
    static constexpr float m_RotSpeed = 0.02f;
    // レコード間隔
    static constexpr float m_Space = 650.f;
    // 補間速度
    static constexpr float m_LerpSpeed = 0.2f;
    // Y座標固定値
    static constexpr float m_PosY = 350.f;
}
CTime::CTime()
    : m_FrameTime(timeGetTime() / 1000.0f)

{
    //スプライトを接続
    AttachSprite(*CSpriteManager::GetSprite2D(L"TimeArrow"));
    m_vPosition = D3DXVECTOR3(660.f, 78.f, 0.f);
    m_vScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
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

    CUIObject::Update();

}

//ゲージの中身
void CTime::Draw()
{
    // 小数点以下も含めた経過時間から進行度を計算
    float ratio = m_FrameTime / m_MaxTime;
    ratio = std::clamp(ratio, 0.0f, 1.0f);

    // 時計の針の回転
    float angle = ratio * 360.0f;

    m_vRotation = D3DXVECTOR3(
        0.0f,
        D3DXToRadian(180.0f),
        D3DXToRadian(angle)
    );

    CUIObject::Draw();
}
//制限時間を超えたら
bool CTime::MaxTime()
{
    //制限時間を超えたら
    if (m_Count >= m_MaxTime)
    {
        return true;
    }
    return false;
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
