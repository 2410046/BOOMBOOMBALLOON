#include "CollisionBox.h"
#include <algorithm>

#undef min
#undef max

CollisionBox::CollisionBox(
    D3DXVECTOR3 Length, CollisionListener* listener, LayerTag tag)
    : CollisionBase(listener,tag)
{
    // Boxのサイズ（幅・高さ・奥行き）
    m_Length = Length;

    // ローカル空間での中心オフセット
    m_Offset = D3DXVECTOR3(0.f, 0.f, 0.f);
}

CollisionBox::~CollisionBox()
{
}

// 更新処理
// ・ワールド行列を使ってAABBを生成する
// ・回転・スケールを考慮したBoxを作る
void CollisionBox::WorldUpdate()
{
    // ワールド行列取得
    // （位置・回転・スケールをすべて含む）
    CGameObject* object = dynamic_cast<CGameObject*>(GetListener());
    if (!object) return;

    const D3DXMATRIX& world = object->GetWorldMatrix();

    // 半サイズ計算
    // ・中心から各方向への距離になる
    D3DXVECTOR3 half = m_Length * 0.5f;

    // ローカル空間での8頂点定義
    // ・中心(0,0,0)基準のBox
    D3DXVECTOR3 local[8] =
    {
        {-half.x, -half.y, -half.z},
        { half.x, -half.y, -half.z},
        {-half.x,  half.y, -half.z},
        { half.x,  half.y, -half.z},
        {-half.x, -half.y,  half.z},
        { half.x, -half.y,  half.z},
        {-half.x,  half.y,  half.z},
        { half.x,  half.y,  half.z},
    };

    // ワールド変換後の頂点配列
    D3DXVECTOR3 worldPos[8];

    for (int i = 0; i < 8; i++)
    {
        // ローカル頂点にオフセットを加算
        // → Boxの中心位置を調整
        D3DXVECTOR3 p = local[i] + m_Offset;

        // ローカル → ワールド変換
        // ・回転
        // ・スケール
        // ・平行移動
        // をすべて適用
        D3DXVec3TransformCoord(&worldPos[i], &p, &world);
    }

    // AABB初期化（最初の頂点）
    m_Box.Min = worldPos[0];
    m_Box.Max = worldPos[0];

    // 全頂点からAABBを生成
    // ・各軸ごとに最小値・最大値を更新
    for (int i = 1; i < 8; i++)
    {
        // 最小値更新
        m_Box.Min.x = std::min(m_Box.Min.x, worldPos[i].x);
        m_Box.Min.y = std::min(m_Box.Min.y, worldPos[i].y);
        m_Box.Min.z = std::min(m_Box.Min.z, worldPos[i].z);

        // 最大値更新
        m_Box.Max.x = std::max(m_Box.Max.x, worldPos[i].x);
        m_Box.Max.y = std::max(m_Box.Max.y, worldPos[i].y);
        m_Box.Max.z = std::max(m_Box.Max.z, worldPos[i].z);
    }

    // AABB中心を計算
    // ・衝突処理やデバッグ描画で使用
    m_WorldPos = (m_Box.Min + m_Box.Max) * 0.5f;
}