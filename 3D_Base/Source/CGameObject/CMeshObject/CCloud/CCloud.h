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
	//更新関数
	virtual void Update();
	//描画関数
	virtual void Draw(CCamera*camera);
	//当たり判定
	void OnCollision(CollisionBase* pCollider)override;
private:
	bool m_Animation;
};