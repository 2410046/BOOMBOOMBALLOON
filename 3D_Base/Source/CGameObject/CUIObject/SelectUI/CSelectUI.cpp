#include "CSelectUI.h"

CSelectUI::CSelectUI()
    :time (0.f)
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
//選択肢の座標
void CSelectUI::SetBasePosition(D3DXVECTOR3 pos)
{
    m_BasePosition = pos;
    m_vPosition = m_BasePosition;
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
        // 時間を進める
        time += 0.05f;

        // 上下にふわふわ動かす
        float offset = sinf(time) * 10.0f;

        D3DXVECTOR3 pos = m_BasePosition;
        pos.y += offset;

        SetPosition(pos);
    }
    else
    {
        // 選択されていない要素は半透明にして、選択中の要素と区別する
        SetAlpha(0.3f);

        // 元の座標に戻す
        SetPosition(m_BasePosition);

        // 時間をリセット
        time = 0.0f;
    }
    // 指定したパターン番号をモデルに反映する
    SetPatternNo(index, pattern);
}

bool CSelectUI::UpDown(bool Sell)
{
    if (Sell)
    {
        // 時間を進める
        time += 0.05f;
        // 上下にふわふわ動く
        m_vPosition.y = 1.f + (float)(sin(time) * 0.3f);
        return true;
    }

    return false;
}
