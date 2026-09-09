#include "CSkinMeshObject.h"

CSkinMeshObject::CSkinMeshObject()
	: m_pMesh			( nullptr )
	, m_pAnimCtrl		( nullptr )
	, m_AnimNo			( 0 )
	, m_AnimTime	    ( 0.8f )
	, m_AnimSpeed       ( 0.0f )
	, m_BonePos			()
{
}

CSkinMeshObject::~CSkinMeshObject()
{
	DetachMesh();
}

void CSkinMeshObject::Update()
{
	if( m_pMesh == nullptr ){
		return;
	}
}

void CSkinMeshObject::Draw(
	const CCamera* pCamera)
{
	if( m_pMesh == nullptr ){
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pMesh->SetPosition( m_vPosition );
	m_pMesh->SetRotation( m_vRotation );
	m_pMesh->SetScale( m_vScale );

	CAMERA Camera = pCamera->GetInstance()->GetCamera();

	D3DXMATRIX View = pCamera->GetInstance()->GetView();
	D3DXMATRIX Proj = pCamera->GetInstance()->GetProj();
	LIGHT	   Light = pCamera->GetInstance()->GetLight();
	//レンダリング.
	m_pMesh->Render( View, Proj, Light, Camera.vPosition,
		m_pAnimCtrl );	//クローンを設定
}

//メッシュを接続する.
void CSkinMeshObject::AttachMesh(CSkinMesh& pMesh)
{
	m_pMesh = &pMesh;

	//アニメーションコントローラを取得
	LPD3DXANIMATIONCONTROLLER pAC = m_pMesh->GetAnimationController();

	//アニメーションコントローラのクローンを作成
	if (FAILED(
		pAC->CloneAnimationController(
			pAC->GetMaxNumAnimationOutputs(),
			pAC->GetMaxNumAnimationSets(),
			pAC->GetMaxNumTracks(),
			pAC->GetMaxNumEvents(),
			&m_pAnimCtrl)))
	{
		_ASSERT_EXPR(false, L"アニメーションコントローラのクローン作成失敗");
	}
}
//メッシュを切り離す.
void CSkinMeshObject::DetachMesh()
{
	m_pMesh = nullptr;

	SAFE_RELEASE(m_pAnimCtrl);
}
