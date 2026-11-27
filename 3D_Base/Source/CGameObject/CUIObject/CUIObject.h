#pragma once
#include "CGameObject.h"
#include "Asset/Sprite/Sprite2D/CSprite2D.h"
/************************************************************
*	UIオブジェクトクラス.
*   スプライト2Dを使用するUIクラス
**/
class CUIObject
	: public CGameObject
{
public:
    // コンストラクタ
    CUIObject();

    // デストラクタ
    virtual ~CUIObject() override;

    // 更新処理
    virtual void Update() override;

    // 描画処理
    virtual void Draw();

    // スプライトを接続
    void AttachSprite(CSprite2D& pSprite)
    {
        m_pSprite = &pSprite;
    }

    // スプライトを切り離す
    void DetachSprite()
    {
        m_pSprite = nullptr;
    }

    // パターン番号を設定
    void SetPatternNo(SHORT x, SHORT y)
    {
        m_PatternNo.x = x;
        m_PatternNo.y = y;
    }

    // 透明度を設定
    void SetAlpha(float alpha)
    {
        m_Alpha = alpha;
    }
protected:
	//CGameObjectから継承した関数
    //カメラを使用した描画処理を禁止
	//final : これ以降はoverrideさせない
	void Draw(const CCamera* pCamera) override final;

    //--------------------------------------
    // 数字を描画
    // value      : 表示する数値
    // Space      : 数字同士の間隔
    // digitCount : 表示する桁数
    //--------------------------------------
	void Number(
        int value, float Space, int digitCount = 4);
    //--------------------------------------
    //数字のカウントアニメーション
    // TargetScore      : 目標数値
    // DisplayScore     : 表示数値
    //--------------------------------------
    void CountUp(int Targetvalue, int& Displayvalue);
protected:
	CSprite2D*	m_pSprite;      //スプライト2D
	POINTS		m_PatternNo;	//パターン番号(マス目)
	float       m_Alpha;        //透明度
	int			m_Patten;		//画像の位置
    int		    m_NumberCount;  //加算アニメーション
};
