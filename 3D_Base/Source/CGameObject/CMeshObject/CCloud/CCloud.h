#pragma once

#include "CGameObject/CMeshObject/CCharacter.h"

/*********************************************************
*	雲クラス、障害物
**/
class CCloud
	: public CCharacter, public CollisionListener
{
public:
	//コンストラクタ
	CCloud();
	//デストラクタ
	virtual ~CCloud()override;
	//画像を設定
	void LoadData();

	virtual void Update();

	void OnCollision(CollisionBase* pCollider)override {};

};