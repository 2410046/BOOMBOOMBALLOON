#pragma once
#include <vector>
#include "Collision/CollisionBase/CollisionBase.h"		//当たり判定クラス
#include"Singleton.h"
//======================================
// 当たり判定管理クラス
//======================================
class CollisionManager
 :public Singleton<CollisionManager>
{
private:
      friend class Singleton<CollisionManager>;
      CollisionManager();
public:
      ~CollisionManager();
    // 初期化
     void Init();
    // 登録
     void Register(std::shared_ptr<CollisionBase> pCollider);
    // 解除
     void Unregister(std::shared_ptr<CollisionBase> pCollider);
     // 更新関数
     void Update();
private:
    // 内部判定
    static bool CheckCollision(
              CollisionBase* a,
              CollisionBase* b);
    // 関数ポインタ型
    using CollisionFunc = bool(*)(
        const CollisionBase*,
        const CollisionBase*);

    // 判定共通化
    static bool CollisionPattern(
        CollisionBase* a,
        CollisionBase* b,
        CollisionBase::CollisionType typeA,
        CollisionBase::CollisionType typeB,
        CollisionFunc func);

    std::vector<std::shared_ptr<CollisionBase>> m_List;
};