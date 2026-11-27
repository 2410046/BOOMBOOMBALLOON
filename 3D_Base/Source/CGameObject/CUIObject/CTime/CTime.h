#pragma once
#include "CGameObject/CUIObject/CUIObject.h"
#include "Singleton.h"
/********************************************************************************
*	タイムクラス
*	ゲーム内の経過時間と制限時間を管理する
**/
class CTime
	:public CUIObject,public Singleton<CTime>
{
private:
	// シングルトンによるインスタンス管理
	friend class Singleton<CTime>;
	// コンストラクタ
	CTime();
public:
	//デストラクタ
	~CTime();
	//更新関数
	virtual void Update() override;
	//描画関数
	virtual void Draw() override;
	// 制限時間に達したか
	bool MaxTime();
	//時間を初期化
	void Reset();
	// 小数秒を含む経過時間を取得
	float GetFlameTime() const { return m_FrameTime; }
	// 制限時間を取得
	float GetMaxTime() const { return m_Max; }
private:
	float m_FrameTime;       // フレーム単位の経過時間（秒）
	float m_LastUpdateTime;  // 前回更新時の時間
	float m_Max;             // 制限時間
};