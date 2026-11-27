#pragma once
#include "Collision/CollisionBase/CollisionBase.h"		//当たり判定クラス
#include"Singleton.h"
/********************************************************************************
*	コリュージョンマネージャークラス
*   当たり判定の登録・更新・管理を行うクラス
**/
class CollisionManager
 :public Singleton<CollisionManager>
{
private:
      friend class Singleton<CollisionManager>;
      CollisionManager();
public:
      ~CollisionManager();
      // 当たり判定の初期化
     void Init();
     // コリジョン形状を登録
     void Register(std::shared_ptr<CollisionBase> pCollider);
     // コリジョン形状を解除
     void Unregister(std::shared_ptr<CollisionBase> pCollider);
     // 当たり判定を更新
     void Update();
private:
    // 2つのオブジェクトの衝突を判定
    static bool CheckCollision(
              CollisionBase* a,
              CollisionBase* b);

    // 衝突判定関数のポインタ型
    using CollisionFunc = bool(*)(
        const CollisionBase*,
        const CollisionBase*);

    // 衝突タイプに応じた共通判定処理
    static bool CollisionPattern(
        CollisionBase* a,
        CollisionBase* b,
        CollisionBase::CollisionType typeA,
        CollisionBase::CollisionType typeB,
        CollisionFunc func);
private:
    // 登録された当たり判定の一覧
    std::vector<std::shared_ptr<CollisionBase>> m_List;
};