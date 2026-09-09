#pragma once
#include "CMeshObject/CCharacter.h"
#include "CMeshObject/CTracking/CTrackingManager/CTrackingManager.h"
//ブースとを使ってショットの動作を
/********************************************************************************
* ショットクラス
*
**/
class CShot
	:public CCharacter,public CollisionListener
{
public:
	CShot();
	virtual~CShot()override;
	//初期化
	virtual void Init(CTracking* pTracking);
	//動作関数
	virtual void Update() override;
	//描画関数
	virtual void Draw(
		const CCamera* pCamera) override;
	void SetShot(
		const D3DXVECTOR3& position,
		const D3DXQUATERNION& Quaternion,
		int ID);

	bool GetFlag()const { return m_ShotFlag; }
	virtual void OnCollision(CollisionBase* base)override ;
private:
	std::shared_ptr<CReaction>	m_pReaction;	//当たり判定
	bool m_ShotFlag;
};
