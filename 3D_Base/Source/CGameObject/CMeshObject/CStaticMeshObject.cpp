#include "CStaticMeshObject.h"

CStaticMeshObject::CStaticMeshObject()
	: m_pMesh			( nullptr )
	, m_ActEffect       ( false )
	, CollisionScale	( 0.f )
{
}

CStaticMeshObject::~CStaticMeshObject()
{
	DetachMesh();	
}

void CStaticMeshObject::Update()
{
	if( m_pMesh == nullptr )
	{
		return;
	}
}

void CStaticMeshObject::Draw(
	const CCamera*pCamera)
{
	if( m_pMesh == nullptr ){
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pMesh->SetPosition( m_vPosition );
	m_pMesh->SetRotation( m_vRotation );
	m_pMesh->SetScale( m_vScale );
	m_pMesh->SetQuaternion(m_vQuaternion);

	CAMERA Camera = pCamera->GetCamera();
	D3DXMATRIX View = pCamera->GetView();
	D3DXMATRIX Proj = pCamera->GetProj();
	LIGHT	   Light = pCamera->GetLight();
	//レンダリング.
	m_pMesh->Render( View, Proj, Light, Camera.vPosition );
}