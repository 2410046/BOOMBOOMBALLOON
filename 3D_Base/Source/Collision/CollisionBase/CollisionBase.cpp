#include "CollisionBase.h"

//--------------------------------------
// コンストラクタ
// type   : コリジョン形状
// layer  : 所属レイヤー
//--------------------------------------
CollisionBase::CollisionBase(
    CollisionListener* layer, LayerTag tag)
    : m_Tag     ( tag )                 // 所属レイヤー
    , m_pLayer  ( layer )               // 所有オブジェクト
    , m_Hit     ( false )               // 非衝突状態で初期化
    , m_WorldPos( -0.5f, -0.5f, -0.5f ) // 初期座標（仮の値）
{
}
//--------------------------------------
// 衝突時処理
// base : 衝突した相手のコリジョン
//--------------------------------------
void CollisionBase::HitCollision(CollisionBase* base)
{
    // 所有オブジェクトが存在する場合のみ通知
    if (m_pLayer)
    {
        // オーナーに衝突イベントを通知
        m_pLayer->OnCollision(base);
    }
}