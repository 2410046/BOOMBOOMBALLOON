#include "CStaticMeshObject.h"
//コンストラクタ
CStaticMeshObject::CStaticMeshObject()
	: m_pMesh			( nullptr )
{
}
//デストラクタ
CStaticMeshObject::~CStaticMeshObject()
{
	DetachMesh();	
}
//更新関数
void CStaticMeshObject::Update()
{
	// メッシュが接続されていない場合は更新しない
	if( m_pMesh == nullptr )
	{
		return;
	}
}
//描画関数
void CStaticMeshObject::Draw(
	const CCamera*pCamera)
{
	// メッシュが接続されていない場合は描画しない
	if( m_pMesh == nullptr )
	{
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pMesh->SetPosition( m_vPosition );
	m_pMesh->SetRotation( m_vRotation );
	m_pMesh->SetScale( m_vScale );
	m_pMesh->SetQuaternion(m_vQuaternion);

	// カメラ情報を取得
	CAMERA Camera = pCamera->GetCamera();
	D3DXMATRIX View = pCamera->GetView();
	D3DXMATRIX Proj = pCamera->GetProj();
	LIGHT	   Light = pCamera->GetLight();
	//レンダリング.
	m_pMesh->Render( View, Proj, Light, Camera.vPosition );
}