#include "CCloud.h"
#include "MathUtility.h"
#include <algorithm>
#include "Collision/CollisionManager/CollisionManager.h"

namespace
{
	//ボックスのサイズ
	D3DXVECTOR3 Box = D3DXVECTOR3(80.f, 20.f, 20.f);
	static constexpr float Stage_ScaleX = 5.0f;   // X方向範囲倍率
	static constexpr float Stage_ScaleZ = 4.0f;	  // Z方向範囲倍率
	static constexpr float Stage_Offset = 0.5f;	  // Z端微調整
}
//コンストラクタ
CCloud::CCloud()
{
	//座標
	m_vPosition = D3DXVECTOR3(0.9f, 1.f, 11.5f);
	//サイズ
	m_vScale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);
	//ボックスの当たり判定
	m_pCollider = CreateCollider::CreateBox(
		Box, this, CollisionBase::Cloud
	);
}
//デストラクタ
CCloud::~CCloud()
{
	CollisionManager::GetInstance()->Unregister(m_pCollider);
}
//画像を設定
void CCloud::LoadData()
{
	//メッシュを接続
	AttachMesh(*AssetManager::GetStatic("Cloud"));
	//m_pMesh->SetAmbient(D3DXVECTOR4(0, 0, 1, 1));
}
//ステージの移動制限
void CCloud::Update()
{
     CCharacter::Update();
}

