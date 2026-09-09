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
private:
	enum enMoveState
	{
		App=0,		//出現
		Idle,
		Delete,
	};
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
	//風船の設定
	void SetBalloon(
		const D3DXVECTOR3& position,
		bool isHit,
		int life);
	//削除状態を取得
	bool GetDelete()const { return m_MoveState == enMoveState::Delete; }
private:
	enMoveState m_MoveState = {};
	// 座標
	D3DXVECTOR3 m_PlayerPos;
	int m_Life;
	// Trackingへの参照
	CTracking* m_pTracking;
};
