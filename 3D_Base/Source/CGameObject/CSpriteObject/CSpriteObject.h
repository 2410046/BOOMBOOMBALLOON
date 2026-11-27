#pragma once
#include "CGameObject.h"
#include <stdio.h>

#include "Asset/Sprite/CSpriteManager.h"
#include "Asset/Sprite/Sprite3D/CSprite3D.h"
/************************************************************
*	スプライトオブジェクトクラス.
* 　スプライト3Dを使用するUIクラス
* 
**/
class CSpriteObject
	: public CGameObject
{
public:
	//コンストラクタ
	CSpriteObject();
	//デストラクタ
	virtual ~CSpriteObject() override;
	//更新関数
	virtual void Update() override;
	//描画関数
	virtual void Draw( const CCamera*pCamera);

	//スプライトを接続する.
	void AttachSprite( CSprite3D& pSprite )
	{
		m_pSprite = &pSprite;
	}
	//スプライトを切り離す.
	void DetachSprite()
	{
		m_pSprite = nullptr;
	}
protected:
	CSprite3D*		 m_pSprite;     //スプライト2D
	float			 m_Alpha;       //透明度
	POINTS			 m_PatternNo;	//パターン番号(マス目)
};
