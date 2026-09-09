#pragma once
#include "CGameObject/CUIObject/CUIObject.h"
/********************************************************************************
*	選択肢のUIクラス
**/
class CSelectUI
	:public CUIObject
{
public:
	CSelectUI();
	virtual ~CSelectUI() override;
	//動作関数
	virtual void Update()override;
	//描画関数
	virtual void Draw()override;
	//選択されたときの状態
	void SellState(
		int index,int selectIndex,int (*patternFunc)(int));

private:

};

