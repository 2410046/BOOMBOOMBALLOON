#include "CSpriteObject.h"

CSpriteObject::CSpriteObject()
	: m_pSprite		( nullptr )
	, m_PatternNo	()
	, m_Alpha       ( 1.f )
	, m_Patten		( 0 )
{
}

CSpriteObject::~CSpriteObject()
{
	DetachSprite();
}

void CSpriteObject::Update()
{
	if( m_pSprite == nullptr ){
		return;
	}
}

void CSpriteObject::Draw(const CCamera* pCamera)
{
	if( m_pSprite == nullptr ){
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pSprite->SetPosition( m_vPosition );
	m_pSprite->SetRotation( m_vRotation );
	m_pSprite->SetScale( m_vScale );
	//m_pSprite->SetPatternNo( m_PatternNo.x, m_PatternNo.y);

	//レンダリング.
	D3DXMATRIX View = pCamera->GetInstance()->GetView();
	D3DXMATRIX Proj = pCamera->GetInstance()->GetProj();

	m_pSprite->Render( View, Proj );
}


