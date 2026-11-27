#include "CSpriteObject.h"
//コンストラクタ
CSpriteObject::CSpriteObject()
	: m_pSprite		( nullptr )
	, m_PatternNo	()
	, m_Alpha       ( 1.f )
{
}
//デストラクタ
CSpriteObject::~CSpriteObject()
{
	//スプライトを切り離す
	DetachSprite();
}
//更新関数
void CSpriteObject::Update()
{
	// スプライトが接続されていない場合は更新しない
	if( m_pSprite == nullptr ){
		return;
	}
}
//描画関数
void CSpriteObject::Draw(const CCamera* pCamera)
{
	// スプライトが接続されていない場合は描画しない
	if( m_pSprite == nullptr ){
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pSprite->SetPosition( m_vPosition );
	m_pSprite->SetRotation( m_vRotation );
	m_pSprite->SetScale( m_vScale );
	//m_pSprite->SetPatternNo( m_PatternNo.x, m_PatternNo.y);

	//カメラ情報取得
	D3DXMATRIX View = pCamera->GetInstance()->GetView();
	D3DXMATRIX Proj = pCamera->GetInstance()->GetProj();
	// スプライトを描画
	m_pSprite->Render( View, Proj );
}


