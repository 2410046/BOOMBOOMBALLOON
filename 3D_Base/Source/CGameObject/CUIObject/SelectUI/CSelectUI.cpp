#include "CSelectUI.h"
// コンストラクタ
CSelectUI::CSelectUI()
    : m_BasePosition( 0.f,0.f,0.f )
{
}

// デストラクタ
CSelectUI::~CSelectUI()
{
}
//更新関数
void CSelectUI::Update()
{
	CUIObject::Update();
}
//描画関数
void CSelectUI::Draw()
{
    // 透明度を設定
	m_pSprite->SetAlpha(m_Alpha);
	CUIObject::Draw();
}
//選択肢の座標
void CSelectUI::SetBasePosition(D3DXVECTOR3 pos)
{
    // 基準座標を保存
    m_BasePosition = pos;

    // 表示位置に基準座標を設定
    m_vPosition = m_BasePosition;
}
//--------------------------------------
// 選択状態に応じて表示パターンを設定
// index        : 選択肢の番号
// selectIndex  : 現在選択されている番号
// pattern      : 表示するパターン番号
//--------------------------------------
void CSelectUI::SelectState(
    int index, int selectIndex, int pattern)
{
    //アニメーションの進行速度
    constexpr float speed = 0.05f;
    // 上下移動の振り幅
    constexpr float amplitude = 10.0f;   
    // 選択時の透明度（完全不透明）
    constexpr float SelectedAlpha = 1.0f;  
    // 非選択時の透明度（半透明）
    constexpr float UnSelectedAlpha = 0.3f; 
    // 現在の選択肢が選択中かどうかを判定
    bool isSelected = (index == selectIndex);

    if (isSelected)
    {
        // 選択中ならば不透明
        SetAlpha(SelectedAlpha);

        // 時間を進める
        m_Count += speed;

        // 時間に応じて上下の移動量を計算
        float offset = sinf(m_Count) * amplitude;

        // 基準座標をもとに表示位置を設定
        D3DXVECTOR3 pos = m_BasePosition;
        pos.y += offset;
        //座標を設定
        SetPosition(pos);
    }
    else
    {
        // 非選択中なら半透明にする
        SetAlpha(UnSelectedAlpha);

        // 元の座標に戻す
        SetPosition(m_BasePosition);

        // 時間をリセット
        m_Count = 0.0f;
    }
    // 指定したパターン番号をモデルに反映する
    SetPatternNo(index, pattern);
}
