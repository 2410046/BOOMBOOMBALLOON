#pragma once
//#include"CSpriteObject/CSpriteObject.h"
#include "CGameObject/CUIObject/CUIObject.h"
#include "Singleton.h"
/********************************************************************************
*	タイムクラス
**/
class CTime
	:public CUIObject,public Singleton<CTime>//スプライトオブジェクトクラス継承
{
private:
	//シングルトン
	friend class Singleton<CTime>;
	CTime();
public:
	//デストラクタ
	~CTime();
	//動作関数
	virtual void Update() override;
	//描画関数
	virtual void Draw() override;
	//制限時間を超えたら
	bool MaxTime();
	//初期化
	void Reset();
	// 小数秒まで含めた時間を取得（例：1.23秒）
	float GetFlameTime() const { return m_FrameTime; }
private:
	int m_Count;				// 現在のカウント時間（秒）
	float m_FrameTime;			// フレーム単位の経過時間（小数秒）
	float m_LastUpdateTime;		// 前フレームの時間
};