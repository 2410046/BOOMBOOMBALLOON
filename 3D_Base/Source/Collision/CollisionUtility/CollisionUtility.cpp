#include "CollisionUtility.h"
#include <algorithm>
#include <float.h>
#include <cmath>
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
    const CollisionCapsule* capsuleA =
        dynamic_cast<const CollisionCapsule*>(cA);

    const CollisionSphere* sphereA =
        dynamic_cast<const CollisionSphere*>(sA);

    if (!capsuleA || !sphereA)
        return false;

    // 現在のカプセル
    const auto& current = capsuleA->GetCapsule();

    // 前フレームのカプセル
    const auto& previous = capsuleA->GetBeforeCapsule();

    // 球
    const auto& sphere = sphereA->GetSphere();

    // 合計半径
    float radius = current.Radius + sphere.Radius;

    // カプセルの移動距離
    D3DXVECTOR3 moveA = current.Start - previous.Start;
    D3DXVECTOR3 moveB = current.End - previous.End;

    float distanceA = D3DXVec3Length(&moveA);
    float distanceB = D3DXVec3Length(&moveB);

    float distance = distanceA;

    if (distanceB > distanceA)
    {
        distance = distanceB;
    }
    static int debugCount = 0;

    debugCount++;

    if (debugCount >= 100)
    {
        debugCount = 0;

        OutputDebugStringA("Collision Debug\n");
    }
    // 判定の分割間隔
    float interval = radius * 0.25f;

    if (interval < 0.01f)
    {
        interval = 0.01f;
    }

    // 分割数
    int steps = static_cast<int>(std::ceil(distance / interval));

    if (steps < 1)
    {
        steps = 1;
    }

    // 前フレームから現在位置まで判定
    for (int i = 0; i <= steps; ++i)
    {
        float t = static_cast<float>(i) / steps;

        // カプセルの位置を補間
        D3DXVECTOR3 start =
            previous.Start + (current.Start - previous.Start) * t;

        D3DXVECTOR3 end =
            previous.End + (current.End - previous.End) * t;

        // カプセル線分と球中心の最近点
        D3DXVECTOR3 ab = end - start;
        D3DXVECTOR3 ap = sphere.Center - start;

        float abLenSq = D3DXVec3Dot(&ab, &ab);

        D3DXVECTOR3 closest;

        if (abLenSq <= 0.0001f)
        {
            closest = start;
        }
        else
        {
            float t2 = D3DXVec3Dot(&ap, &ab) / abLenSq;

            t2 = std::clamp(t2, 0.0f, 1.0f);

            closest = start + ab * t2;
        }

        // 球中心との距離
        D3DXVECTOR3 diff = sphere.Center - closest;

        float distSq = D3DXVec3LengthSq(&diff);

        // 衝突判定
        if (distSq <= radius * radius)
        {
            return true;
        }
    }

    return false;
    //const CollisionCapsule* capsuleA =
    //    dynamic_cast<const CollisionCapsule*>(cA);

    //const CollisionSphere* sphereA =
    //    dynamic_cast<const CollisionSphere*>(sA);

    //if (!capsuleA || !sphereA)
    //{
    //    return false;
    //}
    //const auto& before = capsuleA->GetBeforeCapsule();
    //const auto& current = capsuleA->GetCapsule();
    //const auto& sphere = sphereA->GetSphere();
    //// カプセルの移動距離
    //D3DXVECTOR3 move = current.Start - before.Start;

    //float distance = D3DXVec3Length(&move);

    //// 判定間隔
    //float step = (current.Radius + sphere.Radius) * 0.25f;

    //if (step <= 0.0f)
    //{
    //    return false;
    //}

    //// 移動距離に応じて判定回数を決定
    //int count = static_cast<int>(std::ceil(distance / step));

    //if (count < 1)
    //{
    //    count = 1;
    //}

    //// 移動途中を順番に判定
    //for (int i = 0; i <= count; i++)
    //{
    //    float t = static_cast<float>(i) / count;

    //    CollisionCapsule::Capsule test;

    //    // 始点を補間
    //    test.Start =
    //        before.Start + (current.Start - before.Start) * t;

    //    // 終点を補間
    //    test.End =
    //        before.End + (current.End - before.End) * t;

    //    test.Radius = current.Radius;

    //    // カプセルと球の最近点を求める
    //    D3DXVECTOR3 ab = test.End - test.Start;
    //    D3DXVECTOR3 ac = sphere.Center - test.Start;

    //    float lengthSq = D3DXVec3LengthSq(&ab);

    //    float u = 0.0f;

    //    if (lengthSq > 0.0001f)
    //    {
    //        u = D3DXVec3Dot(&ac, &ab) / lengthSq;
    //        u = std::clamp(u, 0.0f, 1.0f);
    //    }

    //    D3DXVECTOR3 closest = test.Start + ab * u;

    //    D3DXVECTOR3 diff = sphere.Center - closest;

    //    float radius = test.Radius + sphere.Radius;

    //    if (D3DXVec3LengthSq(&diff) <= radius * radius)
    //    {
    //        return true;
    //    }
    //}

    //return false;
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

