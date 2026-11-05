#include "CUIObject.h"

CUIObject::CUIObject()
	: m_pSprite		( nullptr )
	, m_PatternNo	()
	, m_Alpha		( 1 )
	, m_Patten		( 0 )
	, m_ID(0)
{
}

CUIObject::~CUIObject()
{
	DetachSprite();
}

void CUIObject::Update()
{
	if( m_pSprite == nullptr ){
		return;
	}
}

void CUIObject::Draw()
{
	if( m_pSprite == nullptr ){
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pSprite->SetPosition( m_vPosition );
	m_pSprite->SetRotation( m_vRotation );
	m_pSprite->SetScale( m_vScale );
	m_pSprite->SetAlpha(m_Alpha);
	
	//パターン番号を設定
	m_pSprite->SetPatternNo( m_PatternNo.x, m_PatternNo.y );

	//レンダリング.
	m_pSprite->Render();
}

void CUIObject::Draw(
	const CCamera* pCamera)
{
	Draw();
}
void CUIObject::Number(int Score, float Space, int digitCount)
{
	const POINTS PatternMax = m_pSprite->GetPatternMax();

	char buf[16];
	//digitCount = 6 → "%06d"
	char format[16];
	sprintf_s(format, "%%0%dd", digitCount);
	sprintf_s(buf, format, Score);

	for (int i = 0; i < digitCount; ++i)
	{
		int digit = buf[i] - '0';
		//数字を進める
		m_PatternNo.x = digit % PatternMax.x;
		m_PatternNo.y = m_Patten + (digit / PatternMax.x);

		m_pSprite->SetPatternNo(m_PatternNo.x, m_PatternNo.y);

		D3DXVECTOR3 pos = m_vPosition;
		pos.x += i * Space;

		m_pSprite->SetPosition(pos);
		//レンダリング.
		m_pSprite->Render();
	}
}

