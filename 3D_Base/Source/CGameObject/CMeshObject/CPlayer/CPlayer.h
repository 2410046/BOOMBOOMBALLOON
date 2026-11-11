#pragma once
#include "CMeshObject/CCharacter.h"
#include "Global.h"
#include "Asset/CXInput/CXInput.h"

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
		Down,			// ダウン状態
		Invincible,	    // 無敵状態
		Dead,	        // 死亡状態
	};

	struct AttackData
	{
		int count = 0;
		int maxcount = 0;
		float coolTime = 180.0f;
		float coolTimer = 0.0f;
		bool isCoolTime = false;
	};

	// COMの行動状態
	enum class enCOMState
	{
		Chase,      // 接近
		KeepDist,   // 距離を保つ
		Attack,     // 攻撃
		Avoid       // 回避
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
	int  GetPoint();
	//ライフを取得
	int  GetLife() { return m_Life; }
	//クールタイム中のフラグを取得
	std::unordered_map<std::string, bool> GetCoolFlag() const;
	// 他のプレイヤーリストを設定・参照するための関数を追加
	void SetTargetPlayers(const std::vector<CPlayer*>& players) { m_pOtherPlayers = players; }
protected:
	//当たり判定
	void OnCollision(
		CollisionBase* pCollider) override;
	//コントローラー操作
	virtual void Controller();
	//攻撃回数の制限
	bool AttackLimit(const std::string& name);
	//クールタイムの更新
	void UpdateCoolTime();
	//移動制限
	void UpdateMoveLimit();
protected:  
	int         m_Life;			//ライフの数
	int			m_Point;		//スコアに追加するポイント
	enMoveState	m_MoveState;	//移動状態
	std::shared_ptr<CReaction>	m_pReaction;	//リアクション
	std::unordered_map<std::string, AttackData> m_AttackData;
	std::unordered_map<std::string, ::EsHandle> m_Effect;

	std::vector<CPlayer*> m_pOtherPlayers; // 参照用他プレイヤーリスト
};