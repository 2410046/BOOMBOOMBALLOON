#include "CollisionCapsule.h"

//--------------------------------------
// コンストラクタ
// radius   : 半径
// height   : 高さ（Start〜Endの長さ）
// Listener : 衝突時の通知先
// tag      : 所属するレイヤー
//--------------------------------------
CollisionCapsule::CollisionCapsule(
    float radius, float height, 
    CollisionListener* Listener, LayerTag tag)
    : CollisionBase(Listener, tag)
    , m_Radius(radius)
{
    // カプセルの始点と終点をローカル座標で設定
    m_LocalOffsetA = D3DXVECTOR3(0, 0, 0);
    m_LocalOffsetB = D3DXVECTOR3(0, height, 0);

    // 移動補正用オフセットを初期化
    m_MoveOffsetA = D3DXVECTOR3(0, 0, 0);
    m_MoveOffsetB = D3DXVECTOR3(0, 0, 0);
}
// ワールド座標を基準にカプセルの始点と終点を更新
void CollisionCapsule::WorldUpdate()
{
    // 所有オブジェクトを取得
    CGameObject* object = dynamic_cast<CGameObject*>(GetListener());
   
    if (!object)
    {
        return;
    }

    // ワールド行列を取得
    const D3DXMATRIX& world = object->GetWorldMatrix();

    // ローカルオフセットと移動オフセットを合成
    D3DXVECTOR3 offsetA = m_LocalOffsetA + m_MoveOffsetA;
    D3DXVECTOR3 offsetB = m_LocalOffsetB + m_MoveOffsetB;

    // 始点と終点をワールド座標に変換
    D3DXVec3TransformCoord(&m_Capsule.Start, &offsetA, &world);
    D3DXVec3TransformCoord(&m_Capsule.End, &offsetB, &world);

    // カプセルの半径を設定
    m_Capsule.Radius = m_Radius;

    // 始点と終点から中心位置を計算
    constexpr float CenterRate = 0.5f;
    m_WorldPos = (m_Capsule.Start + m_Capsule.End) * CenterRate;

}