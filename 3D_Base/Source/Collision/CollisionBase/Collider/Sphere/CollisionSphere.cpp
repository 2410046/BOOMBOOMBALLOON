#include "CollisionSphere.h"

//--------------------------------------
// コンストラクタ
// radius : 球の半径
// object : 所有オブジェクト
// layer  : 所属レイヤー
//--------------------------------------
CollisionSphere::CollisionSphere(
    float radius, CollisionListener* listener, LayerTag tag)
    : CollisionBase(listener, tag)
{
    m_Radius = radius;

    // ローカル座標での中心オフセット
    m_Offset = D3DXVECTOR3(0, 0, 0);
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

    // ワールド行列取得
    const D3DXMATRIX& world = Object->GetWorldMatrix();

    //--------------------------------------
    // ローカル → ワールド変換
    //--------------------------------------
    D3DXVec3TransformCoord(&m_Sphere.Center, &m_Offset, &world);

    //--------------------------------------
    // 半径を設定
    //--------------------------------------
    m_Sphere.Radius = m_Radius;

    //--------------------------------------
    // 基底クラスの位置も更新（中心座標）
    //--------------------------------------
    m_WorldPos = m_Sphere.Center;
}