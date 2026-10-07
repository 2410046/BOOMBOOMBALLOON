#pragma once
#include "CGameObject/CMeshObject/CStaticMeshObject.h"
#include "Reaction/CReaction.h"
#include "Collision/CreateCollider/CreateCollider.h"
#include "Collision/CollisionManager/CollisionManager.h"
#include "IDData.h"

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

	//IDの取得
	int  GetID()const { return m_ID; }
	//IDの設定
	void SetID(int id) { m_ID = id; }
	//オブジェクトを上下させる
	void UpDown();
	//オブジェクトを回転
	bool Turn(float Speed = 0.1f,float Max = D3DX_PI * 2.0f,bool Loop=false);
protected:
	int		m_ID;			//ID
	float	m_Speed;	//移動速度
	D3DXQUATERNION m_Quat;
	float t = 0.f;
	float m_Scale;
	float m_angle = -1.59f;
};