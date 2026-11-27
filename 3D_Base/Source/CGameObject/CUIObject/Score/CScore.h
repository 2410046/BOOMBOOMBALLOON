#pragma once
#include "CGameObject/CUIObject/CUIObject.h"
/********************************************************************************
*	スコアクラス
*   スコアの計算や表示を行う
**/
class CScore
	:public CUIObject//UIオブジェクトクラス継承
{
public:
	//コンストラクタ
	CScore();
	//デストラクタ
	~CScore()override;
	//更新関数
	virtual void Update() override;
	//描画関数
	virtual void Draw()	  override;
	// スコアの増減処理（point：加算・減算する値）
	void Fluctuation(int point);
	//ゲーム終了時にスコアをランキングにスコアを設定
	void ResultScore();
protected:
	// スコア増加時のアニメーション
	void AddAnime();
private:
	int         m_Score;		  //スコア
	int         m_DisplayScore;   //表示用スコア（カウントアップ）
	int         m_PrevScore;      //前フレームのスコア（スコア変化の検知用）

	float       m_Scale;        // 現在のスケール（表示サイズ）
	float       m_TargetScale;  // 目標描画スケール（アニメーションの到達サイズ）

};





