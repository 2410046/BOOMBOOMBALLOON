#pragma once
class CollisionBase;
/********************************************************************************
*	当たり判定を使用するクラスに継承する
**/
class CollisionListener
{
public:
	virtual ~CollisionListener() = default;
	//当たり判定
	virtual void OnCollision(CollisionBase* base) = 0;
};