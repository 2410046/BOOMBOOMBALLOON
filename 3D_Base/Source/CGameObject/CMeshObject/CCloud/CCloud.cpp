#include "CCloud.h"
#include "MathUtility.h"
#include <algorithm>
#include "Collision/CollisionManager/CollisionManager.h"

namespace
{
	//当たり判定
	constexpr float radius = 1.f;
	//ボックスのサイズ
	D3DXVECTOR3 Box = D3DXVECTOR3(40.f, 20.f, 20.f);
	constexpr float Stage_ScaleX = 5.0f;   // X方向範囲倍率
	constexpr float Stage_ScaleZ = 4.0f;	  // Z方向範囲倍率
	constexpr float Stage_Offset = 0.5f;	  // Z端微調整
	// ローカルオフセットを設定
	const D3DXVECTOR3 colliderOffset = D3DXVECTOR3(15.5f, 0.0f, 0.f);
}
//コンストラクタ
CCloud::CCloud()
	:m_Animation(false)
{
	//座標
	m_vPosition = D3DXVECTOR3(0.f, 1.f, 0.f);
	//サイズ
	m_vScale = D3DXVECTOR3(0.06f, 0.06f, 0.07f);

	// スフィアの当たり判定を生成（オフセットを指定）
	m_pCollider = CreateCollider::CreateSphere(
		radius, this, CollisionBase::Cloud, colliderOffset);
}
//デストラクタ
CCloud::~CCloud()
{
	CollisionManager::GetInstance()->Unregister(m_pCollider);
}
//更新関数
void CCloud::Update()
{
	// 時間を進める
	t += m_Speed;

	if (m_Animation)
	{
		m_Speed = 0.1f;
		// 雲のサイズをサイン波で変化させる
		m_Scale = 1.f + (float)(sin(t) * 0.3f);
		
		if (delta_clamp(m_Count += 1.f, 50.f))
		{
			m_Animation = false;
			t = 0.f;
			m_Count = 0;
		};
	}
	else
	{
		m_Speed = 0.05f;
		// 雲のサイズをサイン波で変化させる
		m_Scale = 1.f + (float)(sin(t) * 0.02f);
	}
	m_vScale = D3DXVECTOR3(m_Scale * 0.06f, m_Scale * 0.06f, m_Scale * 0.07f);


     CCharacter::Update();
}
//描画関数
void CCloud::Draw(CCamera* camera)
{
	m_pMesh->SetAmbient(D3DXVECTOR4(0.f,1.f,1.f,0.f));
	CCharacter::Draw(camera);
}

void CCloud::OnCollision(CollisionBase* pCollider)
{
	// プレイヤーと衝突した場合の処理
	if (pCollider->GetTag() == CollisionBase::Player)
	{
		//アニメーションフラグを立てる
		m_Animation = true;
		CSoundManager::GetInstance()->PlaySE(L"SE\\BaseHit");
	}

}

