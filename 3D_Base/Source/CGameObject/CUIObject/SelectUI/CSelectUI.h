#pragma once
#include "CGameObject/CUIObject/CUIObject.h"
/********************************************************************************
*	選択肢のUIクラス
*   選択肢の表示や選択状態の切り替えを行う
**/
class CSelectUI
	:public CUIObject
{
public:
	//コンストラクタ
	CSelectUI();
	//デストラクタ
	virtual ~CSelectUI() override;
	//更新関数
	virtual void Update()override;
	//描画関数
	virtual void Draw()override;
	// 選択肢の基準座標を設定
	void SetBasePosition(D3DXVECTOR3 pos);

    //--------------------------------------
	// 選択状態に応じて表示パターンを設定
	// index        : 選択肢の番号
	// selectIndex  : 現在選択されている番号
	// pattern      : 表示するパターン番号
	//--------------------------------------
	void SelectState(
		int index,int selectIndex,
		int pattern);
private:

	D3DXVECTOR3 m_BasePosition;	// 選択肢の基準座標
};

