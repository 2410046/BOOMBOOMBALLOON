#pragma once

#include "CGameObject.h"
#include "Asset/Sprite/Sprite2D/CSprite2D.h"
#include "Asset/Sprite/CSpriteManager.h"
/************************************************************
*	UIオブジェクトクラス.
**/
class CUIObject
	: public CGameObject
{
public:
	CUIObject();
	virtual ~CUIObject() override;

	//CGameObjectで純粋仮想関数の宣言がされてるのでこちらで定義を書く.
	virtual void Update() override;
	//CUIObjectで宣言した関数で、以降はこれをoverrideさせる
	virtual void Draw();

	//スプライトを接続する.
	void AttachSprite( CSprite2D& pSprite ){
		m_pSprite = &pSprite;
	}
	//スプライトを切り離す.
	void DetachSprite(){
		m_pSprite = nullptr;
	}
	//パターン番号を設定
	void SetPatternNo(SHORT x, SHORT y){
		m_PatternNo.x = x;
		m_PatternNo.y = y;
	}
	//a値を設定
	void SetAlpha(float alpha) 
	{
		m_Alpha = alpha;
	}
protected:
	//CGameObjectから継承した関数
	//final : これ以降はoverrideさせない
	void Draw(const CCamera* pCamera) override final;
	//数字
	void Number(
		D3DXVECTOR3 pos, int Score, float Space, int digitCount = 4);
protected:
	CSprite2D*	m_pSprite;
	POINTS		m_PatternNo;	//パターン番号(マス目)
	float       m_Alpha;
	int			m_Patten;		//画像の位置
};
