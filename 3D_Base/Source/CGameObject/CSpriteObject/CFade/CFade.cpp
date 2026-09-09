#include "CFade.h"
#include <algorithm>

//コンストラクタ
CFade::CFade()
    : m_Alpha( 0.f )
{
    //スプライトを接続
    AttachSprite(*CSpriteManager::GetSprite3D("Fade"));
}
//デストラクタ
CFade::~CFade()
{
}
//動作関数
void CFade::Update()
{
    CSpriteObject::Update();
}
//描画関数
void CFade::Draw(const CCamera* pCamera)
{
    //a値を設定
    m_pSprite->SetAlpha(m_Alpha);
    CSpriteObject::Draw(pCamera);
}
//透明度初期化
void CFade::Reset()
{
     m_Alpha = 0.f; 
}
//フェードアウト
bool CFade::FadeOut()
{
    ////フェードの
    constexpr float Fade_Speed = 0.01f; //進行速度

    constexpr float Max_Fade   = 1.f;   //最大
    //フェードアウト進行中(徐々に暗くなる)
//a値を増やす
    m_Alpha = std::clamp(m_Alpha + Fade_Speed, 0.f, Max_Fade);

    bool m_Finish = (m_Alpha >= 1.f);
    //フェードアウトが完了したら
    if (m_Finish == true)
    {
        Reset();//リセット
    }
    //フラグを返す
    return m_Finish;

}
