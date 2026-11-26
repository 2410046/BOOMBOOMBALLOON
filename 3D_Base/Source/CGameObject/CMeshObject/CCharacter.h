#pragma once
#include "CGameObject/CMeshObject/CStaticMeshObject.h"
#include "Reaction/CReaction.h"
#include "Collision/CreateCollider/CreateCollider.h"
#include "Collision/CollisionManager/CollisionManager.h"
#include "IDData.h"
#include "MathUtility.h"
/**************************************************
*   キャラクタークラス
**/
class CCharacter
	: public CStaticMeshObject
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void Update() override;
	virtual void Draw(const CCamera* pCamera) override;
	//オブジェクトを上下させる
	void UpDown(float& pos);
	//オブジェクトを回転
	bool TurnUpdate(
		float Speed = 0.1f,float Max = D3DX_PI * 2.0f,bool Loop=false);
protected:
    //クオータニオン対応
    void Quotanion(D3DXVECTOR3 moveDir);
protected:
	float	m_Speed;	//移動速度
	float   t = 0.f;
	float   m_Scale;
	float   m_angle = -1.59f;
};