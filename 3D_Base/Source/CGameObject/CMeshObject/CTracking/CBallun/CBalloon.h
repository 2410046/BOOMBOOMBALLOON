#pragma once
#include "CMeshObject/CCharacter.h"
#include "CMeshObject/CTracking/CTrackingManager/CTrackingManager.h"
/********************************************************************************
* バルーンクラス
* プレイヤーのライフのようなもの
**/
class CBalloon
	:public CCharacter
{
public:
	CBalloon();
	virtual~CBalloon()override;
	//初期化
	void Init(CTracking* pTracking);
	//動作関数
	virtual void Update() override;
	//描画関数
	virtual void Draw(
		const CCamera* pCamera) override;
	//風船の出現
	bool Spawn();
	//風船の設定
	void SetBalloon(
		const D3DXVECTOR3& position,
		bool isHit,
		int life);
private:
	// 座標
	D3DXVECTOR3 m_PlayerPos;
	int m_Life;
	// Trackingへの参照
	CTracking* m_pTracking;
};
