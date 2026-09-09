#include "CollisionUtility.h"
#include <algorithm>
#include <float.h>
// 球同士
bool CollisionUtility::SphereToSphere(
    const CollisionBase* sA,
    const CollisionBase* sB)
{
    // 型変換
    const CollisionSphere* CollSphereA = dynamic_cast<const CollisionSphere*>(sA);
    const CollisionSphere* CollSphereB = dynamic_cast<const CollisionSphere*>(sB);

    if (!CollSphereA || !CollSphereB) { return false; }

    const auto& SphereA = CollSphereA->GetSphere();
    const auto& SphereB = CollSphereB->GetSphere();

    // 中心間距離
    D3DXVECTOR3 diff = SphereA.Center - SphereB.Center;
    float distSq = D3DXVec3LengthSq(&diff);

    // 半径合計
    float r = SphereA.Radius + SphereB.Radius;

    // 距離 <= 半径なら衝突
    return distSq <= (r * r);
}
//カプセルと球
bool CollisionUtility::CapsuleToSphere(
    const CollisionBase* cA,
    const CollisionBase* sA)
{
    const CollisionCapsule* CapsuleA = dynamic_cast<const CollisionCapsule*>(cA);
    const CollisionSphere* SphereA = dynamic_cast<const CollisionSphere*>(sA);

    if (!CapsuleA || !SphereA) { return false; }

    const auto& Capsule = CapsuleA->GetCapsule();
    const auto& Sphere = SphereA->GetSphere();

    //--------------------------------------
    // カプセル線分と球中心の最近点を求める
    //--------------------------------------
    D3DXVECTOR3 ab = Capsule.End - Capsule.Start;
    D3DXVECTOR3 ap = Sphere.Center - Capsule.Start;

    float abLenSq = D3DXVec3Dot(&ab, &ab);

    // カプセルが点の場合
    if (abLenSq <= 0.0001f)
    {
        D3DXVECTOR3 diff = Sphere.Center - Capsule.Start;
        float distSq = D3DXVec3LengthSq(&diff);
        float r = Capsule.Radius + Sphere.Radius;
        return distSq <= (r * r);
    }

    // 最近点の補間係数
    float t = D3DXVec3Dot(&ap, &ab) / abLenSq;
    t = std::clamp(t, 0.0f, 1.0f);

    D3DXVECTOR3 closest = Capsule.Start + ab * t;

    D3DXVECTOR3 diff = Sphere.Center - closest;
    float distSq = D3DXVec3LengthSq(&diff);

    float r = Capsule.Radius + Sphere.Radius;

    return distSq <= (r * r);
}

// カプセルとボックス
bool CollisionUtility::CapsuleToAABB(
    const CollisionBase* cA,
    const CollisionBase* bA)
{
    auto capsuleA =
        dynamic_cast<const CollisionCapsule*>(cA);

    auto boxA =
        dynamic_cast<const CollisionBox*>(bA);

    if (!capsuleA || !boxA)
    {
        return false;
    }

    const auto& capsule = capsuleA->GetCapsule();
    const auto& box = boxA->GetBox();

    //--------------------------------------
    // カプセル線分
    //--------------------------------------
    D3DXVECTOR3 ab = capsule.End - capsule.Start;

    //--------------------------------------
    // Boxへの最近点
    //--------------------------------------
    D3DXVECTOR3 closest =
    {
        std::clamp(capsule.Start.x, box.Min.x, box.Max.x),
        std::clamp(capsule.Start.y,box.Min.y, box.Max.y),
        std::clamp(capsule.Start.z,box.Min.z, box.Max.z)
    };

    //--------------------------------------
    // 開始点 → 最近点
    //--------------------------------------
    D3DXVECTOR3 ap = closest - capsule.Start;

    // 線分長さ^2
    float abLenSq =D3DXVec3Dot(&ab, &ab);

    // カプセルが点の場合
    if (abLenSq <= 0.0001f)
    {
        D3DXVECTOR3 diff =
            closest - capsule.Start;

        return D3DXVec3LengthSq(&diff)
            <= capsule.Radius * capsule.Radius;
    }
    // 最近点係数
    float t =
        D3DXVec3Dot(&ap, &ab) / abLenSq;

    t = std::clamp(t, 0.0f, 1.0f);

    // 線分上最近点
    D3DXVECTOR3 point =
        capsule.Start + ab * t;

    // Boxへの最近点
    D3DXVECTOR3 nearest =
    {
        std::clamp(point.x,
            box.Min.x, box.Max.x),

        std::clamp(point.y,
            box.Min.y, box.Max.y),

        std::clamp(point.z,
            box.Min.z, box.Max.z)
    };
    // 距離判定
    D3DXVECTOR3 diff =
        point - nearest;

    return D3DXVec3LengthSq(&diff)
        <= capsule.Radius * capsule.Radius;
}

bool CollisionUtility::CapsuleToCapsule(const CollisionBase* cA, const CollisionBase* cB)
{
    const CollisionCapsule* A = dynamic_cast<const CollisionCapsule*>(cA);
    const CollisionCapsule* B = dynamic_cast<const CollisionCapsule*>(cB);

    if (!A || !B) { return false; }

    const auto& CapsuleA = A->GetCapsule();
    const auto& CapsuleB = B->GetCapsule();

    // 線分同士の最短距離
    float distSq = SegmentSegmentDistanceSq(
        CapsuleA.Start, CapsuleA.End,
        CapsuleB.Start, CapsuleB.End);

    float r = CapsuleA.Radius + CapsuleB.Radius;

    return distSq <= (r * r);
}
//--------------------------------------
// 線分と線分の最短距離（二乗）
//--------------------------------------
float CollisionUtility::SegmentSegmentDistanceSq(
    const D3DXVECTOR3& p1, const D3DXVECTOR3& q1,
    const D3DXVECTOR3& p2, const D3DXVECTOR3& q2)
{
        const float EPS = 1e-6f;
    
        D3DXVECTOR3 d1 = q1 - p1; // 線分AB
        D3DXVECTOR3 d2 = q2 - p2; // 線分CD
        D3DXVECTOR3 r = p1 - p2;
    
        float a = D3DXVec3Dot(&d1, &d1);
        float e = D3DXVec3Dot(&d2, &d2);
        float f = D3DXVec3Dot(&d2, &r);
    
        float s, t;
    
        // 両方点
        if (a <= EPS && e <= EPS)
            return D3DXVec3LengthSq(&r);
    
        // ABが点
        if (a <= EPS)
        {
            s = 0.0f;
            t = std::clamp(f / e, 0.0f, 1.0f);
        }
        else
        {
            float c = D3DXVec3Dot(&d1, &r);
    
            // CDが点
            if (e <= EPS)
            {
                t = 0.0f;
                s = std::clamp(-c / a, 0.0f, 1.0f);
            }
            else
            {
                float b = D3DXVec3Dot(&d1, &d2);
                float denom = a * e - b * b;
    
                if (denom != 0.0f)
                    s = std::clamp((b * f - c * e) / denom, 0.0f, 1.0f);
                else
                    s = 0.0f;
    
                float tnom = b * s + f;
    
                if (tnom < 0.0f)
                {
                    t = 0.0f;
                    s = std::clamp(-c / a, 0.0f, 1.0f);
                }
                else if (tnom > e)
                {
                    t = 1.0f;
                    s = std::clamp((b - c) / a, 0.0f, 1.0f);
                }
                else
                {
                    t = tnom / e;
                }
            }
        }
    
        D3DXVECTOR3 c1 = p1 + d1 * s;
        D3DXVECTOR3 c2 = p2 + d2 * t;
    
        D3DXVECTOR3 diff = c1 - c2;
        return D3DXVec3LengthSq(&diff);
}

