#pragma once
#include "Collision/CollisionBase/CollisionBase.h"
#include "Collision/CollisionBase/Collider/Box/CollisionBox.h"
#include "Collision/CollisionBase/Collider/Capsule/CollisionCapsule.h"
#include "Collision/CollisionBase/Collider/Sphere/CollisionSphere.h"

//--------------------------------------
// コリジョン判定用ユーティリティクラス
// 各コリジョン形状同士の当たり判定を行う
//--------------------------------------
class CollisionUtility
{
public:
    // 球同士
    static bool SphereToSphere(
        const CollisionBase* sA,
        const CollisionBase* sB);
    //カプセルと球
    static bool CapsuleToSphere(
        const CollisionBase* cA,
        const CollisionBase* sA);
    // カプセルとボックス
    static bool CapsuleToAABB(
        const CollisionBase* cA,
        const CollisionBase* bA);
    // カプセルとカプセル
    static bool CapsuleToCapsule(
        const CollisionBase* cA,
        const CollisionBase* bA);
protected:
    // 線分と線分の最短距離（二乗）
    static float SegmentSegmentDistanceSq(
        const D3DXVECTOR3& p1, const D3DXVECTOR3& q1,
        const D3DXVECTOR3& p2, const D3DXVECTOR3& q2);
};