#pragma once
#include "Collision/CollisionBase/CollisionBase.h"
#include "Collision/CollisionBase/Collider/Box/CollisionBox.h"
#include "Collision/CollisionBase/Collider/Capsule/CollisionCapsule.h"
#include "Collision/CollisionBase/Collider/Sphere/CollisionSphere.h"

/********************************************************************************
*	コリジョン判定用ユーティリティクラス
*   コリジョン形状同士の衝突判定を行う
**/
class CollisionUtility
{
public:
    // スフィア同士の衝突判定
    static bool SphereToSphere(
        const CollisionBase* sA,
        const CollisionBase* sB);
    // カプセルとスフィアの衝突判定
    static bool CapsuleToSphere(
        const CollisionBase* cA,
        const CollisionBase* sA);
    // カプセルとボックスの衝突判定
    static bool CapsuleToAABB(
        const CollisionBase* cA,
        const CollisionBase* bA);
    // カプセル同士の衝突判定
    static bool CapsuleToCapsule(
        const CollisionBase* cA,
        const CollisionBase* bA);
protected:
    // 2つの線分間の最短距離の二乗を計算
    static float SegmentSegmentDistanceSq(
        const D3DXVECTOR3& p1, const D3DXVECTOR3& q1,
        const D3DXVECTOR3& p2, const D3DXVECTOR3& q2);
};