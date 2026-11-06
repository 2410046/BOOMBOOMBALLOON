#include"CAttackIcon.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
namespace
{

    constexpr float Space = 30.f;
}
CAttackIcon::CAttackIcon()
{
    for (int i = 0;i < Max;i++)
    {
        m_Alpha[i] = 1.f;
    }
}

CAttackIcon::~CAttackIcon()
{
}
//動作関数
void CAttackIcon::Update()
{


    //クールタイム中
    //点滅
    for (int i = 0; i < Max; i++)
    {


        if (m_CoolTime["Boost"])
        {
            if (i == 0)
            {
                // Boostアイコン点滅
                m_Alpha[i] = 0.f;
            }

        }
        if (m_CoolTime["Shot"])
        {
            if (i == 1)
            {
                // Shotアイコン点滅
                m_Alpha[i] = 0.f;
            }
        }
        else
        {
            m_Alpha[i] = 1.f;
        }
        //
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
        m_pSprite->SetAlpha(m_Alpha[i]);
        m_pSprite->Render();
    }

}