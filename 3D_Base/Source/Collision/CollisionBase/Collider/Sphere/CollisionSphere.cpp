#include "CollisionSphere.h"

//--------------------------------------
// コンストラクタ
// radius : 球の半径
// object : 所有オブジェクト
// layer  : 所属レイヤー
// offset : 中心のローカルオフセット
//--------------------------------------
CollisionSphere::CollisionSphere(
    float radius, CollisionListener* Listener,
    LayerTag tag, const D3DXVECTOR3& offset)
    : CollisionBase( Listener, tag )
    , m_Radius     ( radius )
    , m_Offset     ( offset ) 
{
}
// ワールド座標を基準に球の中心座標と半径を更新
void CollisionSphere::WorldUpdate()
{
    // 所有オブジェクト取得
    CGameObject* Object = dynamic_cast<CGameObject*>(GetListener());
    
    if (!Object) 
    { 
        return;
    }

    // ワールド行列を取得
    const D3DXMATRIX& world = Object->GetWorldMatrix();
    // オフセットを加味してワールド座標変換
    D3DXVec3TransformCoord(&m_Sphere.Center, &m_Offset, &world);
    // 半径を設定
    m_Sphere.Radius = m_Radius;
    // コリジョンのワールド座標を更新
    m_WorldPos = m_Sphere.Center;
}