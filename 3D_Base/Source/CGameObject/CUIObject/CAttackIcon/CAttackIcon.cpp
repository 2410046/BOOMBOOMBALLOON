#include"CAttackIcon.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
namespace
{
    constexpr int Max = 2;
    constexpr float Space = 30.f;
}
CAttackIcon::CAttackIcon()
{

    //スプライトを接続
   // AttachSprite(*AssetManager::GetSprite2D(L"AttackUser"));
}

CAttackIcon::~CAttackIcon()
{
}
//動作関数
void CAttackIcon::Update()
{
    //クールタイム中
    //点滅
    m_Alpha--;
    if (m_Alpha <= 0.f)
    {
        m_Alpha = 1.f;
    }

    CUIObject::Update();
}

//ゲージの中身
void CAttackIcon::Draw()
{
    for (int i = 0; i < Max; i++)
    {
        D3DXVECTOR3 pos = m_vPosition;
        pos.x += i * Space;

        m_pSprite->SetPosition(pos);
        m_pSprite->SetPatternNo(i,0);
       // m_pSprite->SetPatternNo(m_PatternNo.x, m_PatternNo.y);
        m_pSprite->Render();
        //CUIObject::Draw();
    }

}