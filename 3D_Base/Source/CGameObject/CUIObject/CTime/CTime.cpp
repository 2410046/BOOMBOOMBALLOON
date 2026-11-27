#include "CTime.h"
#include <algorithm>
// コンストラクタ
CTime::CTime()
    : m_Max      ( 10.f )
{
    // 表示するスプライトを接続
    AttachSprite(*CAssetManager::GetSprite2D(L"TimeArrow"));

    // 表示位置と大きさを設定
    m_vPosition = D3DXVECTOR3(673.f, 50.f, 0.f);
    m_vScale    = D3DXVECTOR3(0.15f, 0.12f, 0.15f);

    // 時間を初期化
    Reset();
}
// デストラクタ
CTime::~CTime()
{
}

// 動作関数
void CTime::Update()
{
    // 現在時刻を取得（秒）
    float currentTime = timeGetTime() / 1000.0f;

    // 前回の更新からの経過時間を計算
    float deltaTime = currentTime - m_LastUpdateTime;

    // 前回の更新時刻を更新
    m_LastUpdateTime = currentTime;

    // 経過時間を加算
    m_FrameTime += static_cast<float>(deltaTime);

    // UIの更新処理
    CUIObject::Update();
}
// 描画関数
void CTime::Draw()
{
    // 経過時間から制限時間に対する進行度を計算
    float ratio = m_FrameTime / m_Max;

    // 進行度を0～1の範囲に制限
    ratio = std::clamp(ratio, 0.0f, 1.0f);

    // 進行度に応じて針の回転角度を計算
    constexpr float Degrees = 360.0f;
    float angle = ratio * Degrees;

    // 針の回転角度を設定
    m_vRotation = D3DXVECTOR3(
        0.0f,
        D3DXToRadian(180.0f),
        D3DXToRadian(angle)
    );

    // UIを描画
    CUIObject::Draw();
}

//制限時間を超えたら
bool CTime::MaxTime()
{
    //制限時間を超えたら
    if (m_FrameTime >= m_Max)
    {
        return true;
    }
    return false;
}
// 時間の初期化
void CTime::Reset()
{
    // 経過時間初期化
    m_FrameTime = 0.0f;
    // 現在時刻を基準時刻として設定
    // 初回更新時に余分な時間が加算されるのを防ぐ
    m_LastUpdateTime = timeGetTime() / 1000.0f;
}
