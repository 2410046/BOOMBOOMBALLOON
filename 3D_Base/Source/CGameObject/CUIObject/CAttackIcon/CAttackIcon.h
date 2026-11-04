#pragma once
#include "CGameObject/CUIObject/CUIObject.h"
/********************************************************************************
*	タイムクラス
**/
class CAttackIcon
	:public CUIObject
{
public:
	CAttackIcon();
	//デストラクタ
	~CAttackIcon();
	//動作関数
	virtual void Update() override;
	//描画関数
	virtual void Draw() override;
private:
};