#pragma once
#include "CScene.h"
#include"Scene/SelectText/CSelectText.h"  //選択肢の関数

/********************************************************************************
*	タイトルクラス.
**/
class CTitle
    : public CScene
{
public:
    //コンストラクタ
    CTitle();
    //デストラクタ
    ~CTitle() override;

    //構成関数
    void    Create()   override;    
    //ロード関数
    HRESULT LoadData() override;
    //破棄関数
    void    Release()  override;
    //動作関数
    void    Update()   override;
    //描画関数
    void    Draw()     override;

private:
    //スプライトオブジェクト
    std::unique_ptr<CSpriteObject>          m_pBack;    //背景クラス

    std::vector<std::unique_ptr<CSelectUI>> m_pSelect;  //選択肢テキストクラス
};