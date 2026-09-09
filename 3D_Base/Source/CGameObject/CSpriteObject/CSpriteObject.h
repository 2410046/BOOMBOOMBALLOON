#pragma once
#include "CGameObject.h"
#include <stdio.h>

#include "Asset/Sprite/CSpriteManager.h"
#include "Asset/Sprite/Sprite3D/CSprite3D.h"
/************************************************************
*	スプライトオブジェクトクラス.
**/
class CSpriteObject
	: public CGameObject
{
public:
	CSpriteObject();
	virtual ~CSpriteObject() override;

	//CGameObjectで純粋仮想関数の宣言がされてるのでこちらで定義を書く.
	virtual void Update() override;
	//CSpriteObjectで宣言した関数で、以降はこれをoverrideさせる
	virtual void Draw( const CCamera*pCamera);

	//スプライトを接続する.
	void AttachSprite( CSprite3D& pSprite )
	{
		m_pSprite = &pSprite;
	}
	//スプライトを切り離す.
	void DetachSprite(){
		m_pSprite = nullptr;
	}
	
	void Number(D3DXVECTOR3 pos, const CCamera* pCamera, int Score, float Space)
	{
		//スロットマシンのようなアニメーションにしたい
		const POINTS PatternMax = m_pSprite->GetPatternMax();

		char buf[5];


		sprintf_s(buf, "%04d", Score);

		for (int i = 0; i < 4; ++i)
		{
			int digit = buf[i] - '0';
			//数字を進める
			m_PatternNo.x = digit % PatternMax.x;
			m_PatternNo.y = m_Patten + (digit / PatternMax.x);

			m_pSprite->SetPatternNo(m_PatternNo.x, m_PatternNo.y);

			float PosX = pos.x + (i * Space);
			D3DXVECTOR3 digitPos = D3DXVECTOR3(PosX, pos.y, pos.z);
			m_pSprite->SetBillboard(true);
			m_vPosition = digitPos;  // ローカル変数で位置を設定
			CSpriteObject::Draw(pCamera);
			m_pSprite->SetBillboard(false);
		}
	}
protected:
	//void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override final;

protected:
	CSprite3D*		 m_pSprite;
	 float			 m_Alpha = 1.0f;
	 POINTS			 m_PatternNo;	//パターン番号(マス目)
	 int			 m_Patten = 0;
};
