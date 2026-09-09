#pragma once
#include "CGameObject/CSpriteObject/CSpriteObject.h"
#include <memory>
#include "Singleton.h"
/********************************************************************************
*	フェードクラス
**/
class CFade
    :public CSpriteObject,public Singleton<CFade>  //スプライトオブジェクト継承
{
private:
    //シングルトン
    friend class Singleton<CFade>;
    CFade();
public:
    //デストラクタ
    ~CFade();
    //動作関数
    void Update() override;
    //描画関数
    void Draw(const CCamera* pCamera) override;
    //透明度初期化
    void Reset();
    //フェードアウト
    bool FadeOut();
private:
    float m_Alpha;      //透明度
};




