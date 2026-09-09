#include "CollisionCapsule.h"

//--------------------------------------
// コンストラクタ
// radius : カプセル半径
// height : カプセルの高さ（Start→Endの長さ）
// object : 所有オブジェクト
// layer  : 所属レイヤー
//--------------------------------------
CollisionCapsule::CollisionCapsule(
    float radius, float height, CollisionListener* listener, LayerTag tag)
    : CollisionBase(listener, tag)
    , m_Radius(radius)
{
    // ローカル座標での始点・終点
    m_LocalOffsetA = D3DXVECTOR3(0, 0, 0);
    m_LocalOffsetB = D3DXVECTOR3(0, height, 0);

    // 移動補正（初期はなし）
    m_MoveOffsetA = D3DXVECTOR3(0, 0, 0);
    m_MoveOffsetB = D3DXVECTOR3(0, 0, 0);
}

CollisionCapsule::~CollisionCapsule()
{
}

//--------------------------------------
// 更新処理
// ワールド座標に基づいてカプセルの位置を更新
//--------------------------------------
void CollisionCapsule::WorldUpdate()
{
    // 所有オブジェクトを取得
    CGameObject* object = dynamic_cast<CGameObject*>(GetListener());
    if (!object) return;

    // ワールド行列取得
    const D3DXMATRIX& world = object->GetWorldMatrix();

    // ローカル + 移動オフセットを合成
    D3DXVECTOR3 offsetA = m_LocalOffsetA + m_MoveOffsetA;
    D3DXVECTOR3 offsetB = m_LocalOffsetB + m_MoveOffsetB;

    // ワールド座標へ変換
    D3DXVec3TransformCoord(&m_Capsule.Start, &offsetA, &world);
    D3DXVec3TransformCoord(&m_Capsule.End, &offsetB, &world);

    // 半径を反映
    m_Capsule.Radius = m_Radius;

    // 中心位置（デバッグ・共通処理用）
    m_WorldPos = (m_Capsule.Start + m_Capsule.End) * 0.5f;
}