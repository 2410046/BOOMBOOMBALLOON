#include "CollisionManager.h"
#include "CollisionUtility/CollisionUtility.h"

CollisionManager::CollisionManager()
    :m_List()
{
}
CollisionManager::~CollisionManager()
{
}
//当たり判定の初期化
void CollisionManager::Init()
{
    m_List.clear();
}
// コリジョン形状を登録
void CollisionManager::Register(std::shared_ptr<CollisionBase> pCollider)
{
    if (pCollider)
    {
        m_List.push_back(pCollider);
    }
}
// コリジョン形状を解除
void CollisionManager::Unregister(std::shared_ptr<CollisionBase> pCollider)
{
    m_List.erase(
        std::remove(m_List.begin(), m_List.end(), pCollider),
        m_List.end());
}

// 当たり判定を更新
void CollisionManager::Update()
{
    // コリジョンの位置を更新
      for (const auto& pCollider : m_List)
      {
            pCollider->WorldUpdate();
      }

      // 登録されたコリジョン同士を総当たりで判定
      for (size_t i = 0; i < m_List.size(); ++i)
      {
        CollisionBase* a = m_List[i].get();
        if (!a) continue;

        for (size_t j = i + 1; j < m_List.size(); j++)
        {
           CollisionBase* b = m_List[j].get();
            if (!b) continue;

            // 2つのコリジョンの衝突を判定
            if (CheckCollision(a, b))
            {
                // 衝突したオブジェクトに通知
                a->HitCollision(b);
                b->HitCollision(a);
            }
        }
    }


}
// 2つのオブジェクトの衝突を判定
bool CollisionManager::CheckCollision(
    CollisionBase* a,
    CollisionBase* b)
{
    using Type = CollisionBase::CollisionType;
    // 各コリジョンの形状名を取得
    Type tA = a->GetType();
    Type tB = b->GetType();

    //カプセルとボックスの当たり判定
    if (CollisionPattern(a, b, Type::Capsule, Type::Box,
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
    if (CollisionPattern(a, b, Type::Capsule, Type::Sphere,
        CollisionUtility::CapsuleToSphere))
    {
        return true;
    }
    // カプセルとカプセルの当たり判定
    if (CollisionPattern(a, b, Type::Capsule, Type::Capsule,
        CollisionUtility::CapsuleToCapsule))
    {
        return true;
    }
   return false;
}

// 衝突判定の共通処理
bool CollisionManager::CollisionPattern(
    CollisionBase* a,
    CollisionBase* b,
    CollisionBase::CollisionType typeA,
    CollisionBase::CollisionType typeB,
    CollisionFunc func)
{
    using Type = CollisionBase::CollisionType;
    // 各コリジョンの形状名を取得
    Type tA = a->GetType();
    Type tB = b->GetType();

    // 指定した形状の組み合わせと一致するか確認
     if (tA == typeA && tB == typeB)
     {
         return func(a, b);
     }
     // 形状の順番が逆の場合は入れ替えて判定
     if (tA == typeB && tB == typeA)
     {
         return func(b, a);
     }

    return false;
}
