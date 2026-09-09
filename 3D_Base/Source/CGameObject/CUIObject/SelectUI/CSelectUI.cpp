#include "CSelectUI.h"

CSelectUI::CSelectUI()
{
}

CSelectUI::~CSelectUI()
{
}
//動作関数
void CSelectUI::Update()
{
	CUIObject::Update();
}
//描画関数
void CSelectUI::Draw()
{
	m_pSprite->SetAlpha(m_Alpha);
	CUIObject::Draw();
}
//選択されたときの状態
void CSelectUI::SellState(
    int index, int selectIndex, int (*patternFunc)(int))
{
    // 選択状態
    bool isSelected = (index == selectIndex);

    // 透明度
    SetAlpha(isSelected ? 1.0f : 0.3f);

    // パターン
    int pattern = patternFunc ? patternFunc(index) : index;
    SetPatternNo(0, pattern);
}
