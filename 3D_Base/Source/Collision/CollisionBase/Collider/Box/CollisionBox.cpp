#include "CollisionBox.h"
#include <algorithm>

#undef min
#undef max
//--------------------------------------
// コンストラクタ
// Length   : ボックスのサイズ
// Listener : 衝突時の通知先
// tag      : 所属するレイヤー
//--------------------------------------
CollisionBox::CollisionBox(
    D3DXVECTOR3 Length, CollisionListener* listener, LayerTag tag)
    : CollisionBase(listener,tag)
{
    // ボックスのサイズを設定
    m_Length = Length;

    // ローカル座標での中心位置を設定
    m_Offset = D3DXVECTOR3(0.f, 0.f, 0.f);
}

// ワールド座標を基準にボックスの最小座標と最大座標を更新
void CollisionBox::WorldUpdate()
{
    // 所有オブジェクトを取得
    CGameObject* object = dynamic_cast<CGameObject*>(GetListener());

    if (!object)
    {
        return;
    }
    // ワールド行列を取得
    const D3DXMATRIX& world = object->GetWorldMatrix();

    // ボックスの半分のサイズを計算
    constexpr float LengthRate = 0.5f;
    D3DXVECTOR3 half = m_Length * LengthRate;

    // ローカル座標での8頂点を定義
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

    // ワールド座標に変換した頂点を格納
    D3DXVECTOR3 worldPos[8];

    for (int i = 0; i < 8; i++)
    {
        // ローカル座標に中心位置のオフセットを加算
        D3DXVECTOR3 p = local[i] + m_Offset;

        // ローカル → ワールド変換
        // ・回転
        // ・スケール
        // ・平行移動
        // をすべて適用
        D3DXVec3TransformCoord(&worldPos[i], &p, &world);
    }

    // 最初の頂点を基準に最小座標と最大座標を初期化
    m_Box.Min = worldPos[0];
    m_Box.Max = worldPos[0];

    // 8頂点から各軸の最小値と最大値を計算
    for (int i = 1; i < 8; i++)
    {
        // 各軸の最小値を更新
        m_Box.Min.x = std::min(m_Box.Min.x, worldPos[i].x);
        m_Box.Min.y = std::min(m_Box.Min.y, worldPos[i].y);
        m_Box.Min.z = std::min(m_Box.Min.z, worldPos[i].z);

        // 各軸の最大値を更新
        m_Box.Max.x = std::max(m_Box.Max.x, worldPos[i].x);
        m_Box.Max.y = std::max(m_Box.Max.y, worldPos[i].y);
        m_Box.Max.z = std::max(m_Box.Max.z, worldPos[i].z);
    }

    // 最小座標と最大座標から中心位置を計算
    m_WorldPos = (m_Box.Min + m_Box.Max) * LengthRate;
}