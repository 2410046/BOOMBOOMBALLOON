#include "CollisionManager.h"
#include "CollisionUtility/CollisionUtility.h"
#include <algorithm>

CollisionManager::CollisionManager()
    :m_List()
{
}
CollisionManager::~CollisionManager()
{
}

// 初期化
void CollisionManager::Init()
{
    m_List.clear();
}

// 登録
void CollisionManager::Register(std::shared_ptr<CollisionBase> pCollider)
{
    if (pCollider)
    {
        m_List.push_back(pCollider);
    }
}
// 解除
void CollisionManager::Unregister(std::shared_ptr<CollisionBase> pCollider)
{
    m_List.erase(
        std::remove(m_List.begin(), m_List.end(), pCollider),
        m_List.end());
}

// 更新関数
void CollisionManager::Update()
{
    //----------------------------------
    // コリジョン更新（位置同期）
    //----------------------------------
      for (const auto& pCollider : m_List)
      {
            pCollider->WorldUpdate();
      }

    //----------------------------------
    // 総当たり判定
    //----------------------------------
    // 衝突判定
      for (size_t i = 0; i < m_List.size(); ++i)
      {
        CollisionBase* a = m_List[i].get();
        if (!a) continue;

        for (size_t j = i + 1; j < m_List.size(); j++)
        {
           CollisionBase* b = m_List[j].get();
            if (!b) continue;
            //----------------------------------
            // 衝突判定
            //----------------------------------
            if (CheckCollision(a, b))
            {
                //----------------------------------
                // 衝突通知
                //----------------------------------
                a->HitCollision(b);
                b->HitCollision(a);
            }
        }
    }


}
//内部判定
bool CollisionManager::CheckCollision(
    CollisionBase* a,
    CollisionBase* b)
{
    using Type = CollisionBase::CollisionType;
    
    Type tA = a->GetType();
    Type tB = b->GetType();
    //カプセルとボックスの当たり判定
    if (CollisionPattern(a, b,Type::Capsule,Type::Box,
        CollisionUtility::CapsuleToAABB))
    {
        return true;
    }
    // スフィアとスフィアの当たり判定
    if (CollisionPattern(a, b, Type::Sphere, Type::Sphere,
        CollisionUtility::SphereToSphere))
    {
        return true;
    }
    // カプセルとスフィアの当たり判定
    if (CollisionPattern(a, b,Type::Capsule,Type::Sphere,
        CollisionUtility::CapsuleToSphere))
    {
        return true;
    }
    // カプセルとカプセルの当たり判定
    if (CollisionPattern(a, b,Type::Capsule,Type::Capsule,
        CollisionUtility::CapsuleToCapsule))
    {
        return true;
    }
   return false;
}

// 判定共通化
bool CollisionManager::CollisionPattern(
    CollisionBase* a,
    CollisionBase* b,
    CollisionBase::CollisionType typeA,
    CollisionBase::CollisionType typeB,
    CollisionFunc func)
{
    using Type = CollisionBase::CollisionType;

    Type tA = a->GetType();
    Type tB = b->GetType();

    //----------------------------------
    // 型一致
    //----------------------------------
     if (tA == typeA && tB == typeB)
     {
         return func(a, b);
     }

     if (tA == typeB && tB == typeA)
     {
         return func(b, a);
     }
    return false;
}
