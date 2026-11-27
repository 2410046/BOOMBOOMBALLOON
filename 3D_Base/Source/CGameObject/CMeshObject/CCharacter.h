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
	//コンストラクタ
	CCharacter();
	//デストラクタ
	virtual ~CCharacter();
	//更新関数
	virtual void Update() override;
	//描画関数
	virtual void Draw(const CCamera* pCamera) override;
	//オブジェクトを上下させる
	void UpDown(float& pos);
	//オブジェクトを回転
	bool TurnUpdate(
		float Speed = 0.1f,float Max = D3DX_PI * 2.0f,bool Loop=false);
protected:
	//当たり判定情報を取得
	const std::shared_ptr<CollisionBase>& GetCollider() const
	{
		return m_pCollider;
	}
    //クオータニオン対応
    void Quotanion(D3DXVECTOR3 moveDir);
protected:
	std::shared_ptr<CollisionBase> m_pCollider; // 当たり判定情報

	float	m_Speed;	//移動速度
	float   t = 0.f;
	float   m_Scale;
	float   m_angle = -1.59f;
};