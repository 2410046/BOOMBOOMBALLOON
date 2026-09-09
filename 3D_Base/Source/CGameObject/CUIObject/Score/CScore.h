#pragma once
#include "CGameObject/CUIObject/CUIObject.h"
/********************************************************************************
*	スコアクラス
**/
class CScore
	:public CUIObject//UIオブジェクトクラス継承
{
public:
	//コンストラクタ
	CScore();
	//デストラクタ
	~CScore()override;
	//動作関数
	virtual void Update() override;
	//描画関数
	virtual void Draw()	  override;
    //スコアを減少
	void DropScore(
		int i, bool Rhythm = false);
    //スコアを追加
	void AddScore(
		int i,bool Attack = false);

	//ゲーム終了時のスコア
	void ResultScore();
	//スコアとコンボの座標を取得
	void SetPos(
		D3DXVECTOR3 pos, D3DXVECTOR3 Compos);
public:
	void SetID(int id) { m_ID = id; }
	int GetID() const { return m_ID; }
protected:
	//スコアが増えた時のアニメーション
	void AddAnime();
private:
	int         m_Score;		  //スコア
	int         m_DisplayScore;   //表示用スコア（アニメ用）

	int		    m_UpdateCounter;  //加算アニメーション
	int         m_ID;			  //スコアID

	float       m_Scale;        // 現在のスケール（表示サイズ）
	float       m_TargetScale;  // 目標スケール（アニメーションで目指すサイズ）
	int         m_PrevScore;    // 前回のスコア（変化検知や更新判定用）
private:        
	D3DXVECTOR3 m_Pos;			  //スコアの描画位置
	D3DXVECTOR3 m_ComPos;		  //コンボの描画位置
};





