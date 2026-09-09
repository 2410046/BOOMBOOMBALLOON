#pragma once
#include <memory>
#include "CollisionBase/Collider/Sphere/CollisionSphere.h"
#include "CollisionBase/Collider/Capsule/CollisionCapsule.h"
#include "CollisionBase/Collider/Box/CollisionBox.h"
#include "CollisionListener/CollisionListener.h"
/********************************************************************************
*	当たり判定生成クラス
**/
class CreateCollider
{
public:
    //スフィアの当たり判定を生成
    static std::shared_ptr<CollisionBase> CreateSphere(
        float Radius, CollisionListener* pOwner,
        CollisionBase::LayerTag tag);
    //カプセルの当たり判定を生成
    static std::shared_ptr<CollisionBase> CreateCaupsule(
        float Radius, float Height, CollisionListener* pOwner,
        CollisionBase::LayerTag tag);
    //ボックスの当たり判定生成
    static std::shared_ptr<CollisionBase> CreateBox(
        D3DXVECTOR3 Langth, CollisionListener* pOwner,
        CollisionBase::LayerTag tag);
};
