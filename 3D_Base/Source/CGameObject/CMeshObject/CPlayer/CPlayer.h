#pragma once
#include "CMeshObject/CCharacter.h"
#include "Global.h"
/********************************************************************************
* プレイヤークラス
**/
class CPlayer
	: public CCharacter,public CollisionListener
	//キャラクタークラスを継承.
{
public:
	// プレイヤーの状態
	enum enMoveState
	{
		App = 0,		// 出現
		Live,			// 生存状態
		Boost,			// ブースト状態

		Shot,			// 射撃状態
		CoolTime,		// クールタイム
		Down,			// ダウン状態
		Invincible,	    // 無敵状態
		Dead,	        // 死亡状態
	};

public:
	//コンストラクタ
	CPlayer();
	//デストラクタ
	virtual ~CPlayer() override;
	//動作関数
	virtual void Update() override;
	//描画関数
	virtual void Draw(
		const CCamera* pCamera ) override;
public:
	//状態を取得
	bool GetShot() const{ return m_MoveState == enMoveState::Shot;}
	//ポイントを取得
	int  GetPoint() 
	{
		int point = m_Point;
		m_Point = 0;
		return point;
	}
	//ライフを取得
	int  GetLife() { return m_Life; }
protected:
	//当たり判定
	void OnCollision(
		CollisionBase* pCollider) override;
	//コントローラー操作
	void Controller();
	//クオータニオン対応
	void Quotanion(D3DXVECTOR3 moveDir);
	//移動制限
	void MoveLimit();
protected:
	enMoveState	m_MoveState;	//移動状態
	float       m_StateTime;	//状態の開始時間
	//キーボード
	int         m_Life;			//ライフの数
	int			m_Point;		//スコアに追加するポイント
	std::shared_ptr<CReaction>	m_pReaction;	//当たり判定

};