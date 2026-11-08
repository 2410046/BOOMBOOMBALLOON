#include "CollisionSphere.h"

//--------------------------------------
// コンストラクタ
// radius : 球の半径
// object : 所有オブジェクト
// layer  : 所属レイヤー
//--------------------------------------
CollisionSphere::CollisionSphere(
    float radius, CollisionListener* listener, LayerTag tag, const D3DXVECTOR3& offset)
    : CollisionBase(listener, tag)
    , m_Radius(radius)
    , m_Offset(offset) // オフセットを保存
{
}

CollisionSphere::~CollisionSphere()
{
}

//--------------------------------------
// 更新処理
// ワールド座標に基づいて球の位置を更新
//--------------------------------------
void CollisionSphere::WorldUpdate()
{
    // 所有オブジェクト取得
    CGameObject* Object = dynamic_cast<CGameObject*>(GetListener());
    if (!Object) return;

    const D3DXMATRIX& world = Object->GetWorldMatrix();

    // 1. オフセットを加味してワールド座標変換
    D3DXVec3TransformCoord(&m_Sphere.Center, &m_Offset, &world);

    // 2. ワールド行列のX軸スケールを取得して半径に掛ける
    //D3DXVECTOR3 axisX(world._11, world._12, world._13);
    //float scaleX = D3DXVec3Length(&axisX);
    m_Sphere.Radius = m_Radius;/* * scaleX;*/

    m_WorldPos = m_Sphere.Center;

}