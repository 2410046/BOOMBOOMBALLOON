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
    int index, int selectIndex, int pattern)
{
    // 現在の要素が選択中かどうかを判定する
    bool isSelected = (index == selectIndex);

    // 選択中の要素かどうかで透明度を変更する
    if (isSelected)
    {
        // 選択中の要素は不透明にして、目立たせる
        SetAlpha(1.0f);
    }
    else
    {
        // 選択されていない要素は半透明にして、選択中の要素と区別する
        SetAlpha(0.3f);
    }
    // 指定したパターン番号をモデルに反映する
    SetPatternNo(index, pattern);
}
