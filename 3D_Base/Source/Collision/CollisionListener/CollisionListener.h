#pragma once
class CollisionBase;
#include <memory>
/********************************************************************************
*	当たり判定を使用するクラスに継承する
**/
class CollisionListener
{
public:
	virtual ~CollisionListener() = default;
	virtual void OnCollision(CollisionBase* base) = 0;
};