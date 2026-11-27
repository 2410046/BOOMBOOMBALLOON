#include "CollisionBase.h"
//--------------------------------------
// コンストラクタ
// Listener : 衝突時の通知先
// tag      : 所属するレイヤー
// //--------------------------------------
CollisionBase::CollisionBase(
    CollisionListener* Listener, LayerTag tag)
    : m_Tag      ( tag )                 
    , m_pListener( Listener )            
    , m_Hit      ( false )               
    , m_WorldPos ( -0.5f, -0.5f, -0.5f ) 
{
}
//--------------------------------------
// 衝突した相手のオブジェクトに通知
// base : 衝突した相手のコリジョン
//--------------------------------------
void CollisionBase::HitCollision(CollisionBase* base)
{
    // 所有オブジェクトが存在する場合のみ通知
    if (m_pListener)
    {
        //衝突イベントを通知
        m_pListener->OnCollision(base);
    }
}