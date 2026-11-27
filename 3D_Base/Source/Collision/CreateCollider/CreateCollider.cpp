#include "stdafx.h"
#include "CreateCollider.h"
#include "Collision/CollisionManager/CollisionManager.h"
//スフィアの当たり判定を生成・登録
std::shared_ptr<CollisionBase> CreateCollider::CreateSphere(
    float Radius,
    CollisionListener* pOwner,
    CollisionBase::LayerTag tag,
    const D3DXVECTOR3& offset) 
{
    // スフィアのコリジョンを生成
    std::shared_ptr<CollisionBase> pCollider
        = std::make_shared<CollisionSphere>(Radius, pOwner, tag, offset);
    // コリジョンマネージャーに登録
    CollisionManager::GetInstance()->Register(pCollider);
    return pCollider;
}
//カプセルの当たり判定を生成・登録
std::shared_ptr<CollisionBase> CreateCollider::CreateCaupsule(
    float Radius, float Height, CollisionListener* pOwner,
    CollisionBase::LayerTag tag)
{
    // カプセルのコリジョンを生成
    std::shared_ptr<CollisionBase> pCollider
        = std::make_shared<CollisionCapsule>(Radius, Height, pOwner, tag);
    // コリジョンマネージャーに登録
    CollisionManager::GetInstance()->Register(pCollider);
    return pCollider;
}
// ボックスのコリジョンを生成・登録
std::shared_ptr<CollisionBase> CreateCollider::CreateBox(
    D3DXVECTOR3 Langth, CollisionListener* pOwner, CollisionBase::LayerTag tag)
{
    // ボックスのコリジョンを生成
    std::shared_ptr<CollisionBase> pCollider
        = std::make_shared<CollisionBox>(Langth, pOwner, tag);
    // コリジョンマネージャーに登録
    CollisionManager::GetInstance()->Register(pCollider);
    return pCollider;
}
