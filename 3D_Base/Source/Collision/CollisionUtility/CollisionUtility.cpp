#include "CollisionUtility.h"
#include <algorithm>
#include <float.h>
#include <cmath>
// スフィア同士の衝突判定
bool CollisionUtility::SphereToSphere(
    const CollisionBase* sA,
    const CollisionBase* sB)
{
    // コリジョンをスフィア型に変換
    const CollisionSphere* CollSphereA 
        = dynamic_cast<const CollisionSphere*>(sA);
    const CollisionSphere* CollSphereB 
        = dynamic_cast<const CollisionSphere*>(sB);

    // 変換に失敗した場合は衝突なし
    if (!CollSphereA || !CollSphereB) { return false; }

    // スフィアの情報を取得
    const auto& SphereA = CollSphereA->GetSphere();
    const auto& SphereB = CollSphereB->GetSphere();

    // スフィアの中心間距離を計算
    D3DXVECTOR3 diff = SphereA.Center - SphereB.Center;
    float distSq = D3DXVec3LengthSq(&diff);

    // 2つの半径を合計
    float r = SphereA.Radius + SphereB.Radius;

    // 中心間距離が半径の合計以下なら衝突
    return distSq <= (r * r);
}
// カプセルとスフィアの衝突判定
bool CollisionUtility::CapsuleToSphere(
    const CollisionBase* cA,
    const CollisionBase* sA)
{
    // コリジョンを各形状に変換
    const CollisionCapsule* CapsuleA 
        = dynamic_cast<const CollisionCapsule*>(cA);
    const CollisionSphere* SphereA 
        = dynamic_cast<const CollisionSphere*>(sA);

    // 変換に失敗した場合は衝突なし
    if (!CapsuleA || !SphereA) { return false; }
    // 各コリジョンの情報を取得
    const auto& Capsule = CapsuleA->GetCapsule();
    const auto& Sphere = SphereA->GetSphere();

    // カプセルの線分とスフィアの中心を結ぶベクトルを取得
    D3DXVECTOR3 ab = Capsule.End - Capsule.Start;
    D3DXVECTOR3 ap = Sphere.Center - Capsule.Start;

    // カプセルの線分の長さの二乗を計算
    float abLenSq = D3DXVec3Dot(&ab, &ab);

    // カプセルの線分が点の場合
    if (abLenSq <= 0.0001f)
    {
        // 中心間距離を計算
        D3DXVECTOR3 diff = Sphere.Center - Capsule.Start;
        float distSq = D3DXVec3LengthSq(&diff);

        // 半径の合計で衝突判定
        float r = Capsule.Radius + Sphere.Radius;
        return distSq <= (r * r);
    }

    // 線分上の最近点を求めるための補間係数を計算
    float t = D3DXVec3Dot(&ap, &ab) / abLenSq;
    // 補間係数を線分の範囲内に制限
    t = std::clamp(t, 0.0f, 1.0f);
    // カプセルの線分上にある最近点を取得
    D3DXVECTOR3 closest = Capsule.Start + ab * t;

    // 最近点とスフィアの中心間距離を計算
    D3DXVECTOR3 diff = Sphere.Center - closest;
    float distSq = D3DXVec3LengthSq(&diff);

    // 半径の合計で衝突判定
    float r = Capsule.Radius + Sphere.Radius;
    return distSq <= (r * r);
}
// カプセルとボックスの衝突判定
bool CollisionUtility::CapsuleToAABB(
    const CollisionBase* cA,
    const CollisionBase* bA)
{
   // コリジョンを各形状に変換
    auto capsuleA =
        dynamic_cast<const CollisionCapsule*>(cA);
    auto boxA =
        dynamic_cast<const CollisionBox*>(bA);

    // 変換に失敗した場合は衝突なし
    if (!capsuleA || !boxA)
    {
        return false;
    }

    // 各コリジョンの情報を取得
    const auto& capsule = capsuleA->GetCapsule();
    const auto& box = boxA->GetBox();

    // カプセルの線分方向を取得
    D3DXVECTOR3 ab = capsule.End - capsule.Start;

    // カプセルの開始点に最も近いボックス上の点を取得
    D3DXVECTOR3 closest =
    {
        std::clamp(capsule.Start.x, box.Min.x, box.Max.x),
        std::clamp(capsule.Start.y,box.Min.y, box.Max.y),
        std::clamp(capsule.Start.z,box.Min.z, box.Max.z)
    };

    // カプセルの開始点から最近点へのベクトルを取得
    D3DXVECTOR3 ap = closest - capsule.Start;

    // カプセルの線分の長さの二乗を計算
    float abLenSq =D3DXVec3Dot(&ab, &ab);

    // カプセルの線分が点の場合
    if (abLenSq <= 0.0001f)
    {
        // 最近点との距離で衝突判定
        D3DXVECTOR3 diff =
            closest - capsule.Start;

        return D3DXVec3LengthSq(&diff)
            <= capsule.Radius * capsule.Radius;
    }
    // 線分上の最近点を求めるための補間係数を計算
    float t =
        D3DXVec3Dot(&ap, &ab) / abLenSq;
    // 補間係数を線分の範囲内に制限
    t = std::clamp(t, 0.0f, 1.0f);

    // カプセルの線分上にある最近点を取得
    D3DXVECTOR3 point =
        capsule.Start + ab * t;

    // 線分上の最近点に対するボックス上の最近点を取得
    D3DXVECTOR3 nearest =
    {
        std::clamp(point.x,
            box.Min.x, box.Max.x),

        std::clamp(point.y,
            box.Min.y, box.Max.y),

        std::clamp(point.z,
            box.Min.z, box.Max.z)
    };

    // 2つの最近点間の距離で衝突判定
    D3DXVECTOR3 diff =
        point - nearest;

    return D3DXVec3LengthSq(&diff)
        <= capsule.Radius * capsule.Radius;
}
// カプセル同士の衝突判定
bool CollisionUtility::CapsuleToCapsule(const CollisionBase* cA, const CollisionBase* cB)
{
    // コリジョンをカプセル型に変換
    const CollisionCapsule* A = dynamic_cast<const CollisionCapsule*>(cA);
    const CollisionCapsule* B = dynamic_cast<const CollisionCapsule*>(cB);

    // 変換に失敗した場合は衝突なし
    if (!A || !B) { return false; }
    // 各カプセルの情報を取得
    const auto& CapsuleA = A->GetCapsule();
    const auto& CapsuleB = B->GetCapsule();

    // 2つの線分間の最短距離を計算
    float distSq = SegmentSegmentDistanceSq(
        CapsuleA.Start, CapsuleA.End,
        CapsuleB.Start, CapsuleB.End);

    // 2つの半径を合計
    float r = CapsuleA.Radius + CapsuleB.Radius;

    // 最短距離が半径の合計以下なら衝突
    return distSq <= (r * r);
}
// 線分同士の最短距離の二乗を計算
float CollisionUtility::SegmentSegmentDistanceSq(
    const D3DXVECTOR3& p1, const D3DXVECTOR3& q1,
    const D3DXVECTOR3& p2, const D3DXVECTOR3& q2)
{
    // 計算誤差を考慮するための微小値
     const float EPS = 1e-6f;

     // 各線分の方向ベクトルを取得
     D3DXVECTOR3 d1 = q1 - p1; // 線分AB
     D3DXVECTOR3 d2 = q2 - p2; // 線分CD
     D3DXVECTOR3 r = p1 - p2;

     // 線分の長さの二乗を計算
     float a = D3DXVec3Dot(&d1, &d1);
     float e = D3DXVec3Dot(&d2, &d2);
     float f = D3DXVec3Dot(&d2, &r);
    
     float s, t;
    
     // 両方の線分が点の場合
     if (a <= EPS && e <= EPS)
         return D3DXVec3LengthSq(&r);
    
     // 1つ目の線分が点の場合
     if (a <= EPS)
     {
         // 2つ目の線分上の最近点を求める
         s = 0.0f;
         t = std::clamp(f / e, 0.0f, 1.0f);
     }
     else
     {
         float c = D3DXVec3Dot(&d1, &r);
    
         // 2つ目の線分が点の場合
         if (e <= EPS)
         {
             // 1つ目の線分上の最近点を求める
             t = 0.0f;
             s = std::clamp(-c / a, 0.0f, 1.0f);
         }
         else
         {
             float b = D3DXVec3Dot(&d1, &d2);
             float denom = a * e - b * b;
             // 線分同士の最近点を求める
             if (denom != 0.0f)
             {
                 s = std::clamp((b * f - c * e) / denom, 0.0f, 1.0f);
             }
             else
             {
                 s = 0.0f;
             }
             float tnom = b * s + f;
             // 最近点が2つ目の線分の始点より外側の場合
             if (tnom < 0.0f)
             {
                 t = 0.0f;
                 s = std::clamp(-c / a, 0.0f, 1.0f);
             }
             // 最近点が2つ目の線分の終点より外側の場合
             else if (tnom > e)
             {
                 t = 1.0f;
                 s = std::clamp((b - c) / a, 0.0f, 1.0f);
             }
             // 線分の範囲内に最近点がある場合
             else
             {
                 t = tnom / e;
             }
         }
     }
     // 各線分上の最近点を取得
     D3DXVECTOR3 c1 = p1 + d1 * s;
     D3DXVECTOR3 c2 = p2 + d2 * t;

     // 最近点同士の距離の二乗を返す
     D3DXVECTOR3 diff = c1 - c2;
     return D3DXVec3LengthSq(&diff);
}

