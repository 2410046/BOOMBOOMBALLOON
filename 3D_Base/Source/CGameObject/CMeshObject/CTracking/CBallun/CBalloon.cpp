#include "CBalloon.h"
CBalloon::CBalloon()
    : m_PlayerPos(0.0f, 0.0f, 0.0f)
    , m_Life(0)
	, m_MoveState(enMoveState::Idle)
	, m_pTracking(nullptr)
{
	//m_vScale = D3DXVECTOR3(0.001f, 0.001f, 0.001f);
	m_vScale = D3DXVECTOR3(0.001f, 0.001f, 0.001f);
	m_vPosition = D3DXVECTOR3(0.1f, 1.f, 7.5f);
}

CBalloon::~CBalloon()
{
}
//初期化
void CBalloon::Init(CTracking* pTracking)
{
	if (pTracking == nullptr)
	{
		return;
	}

	//m_pTracking = pTracking;
	AttachMesh(*AssetManager::GetStatic("Balloon"));

	// プレイヤーの現在位置を取得
	SetPosition(
		pTracking->GetPosition());

	//// プレイヤーの現在方向を取得
	m_vQuaternion =
		pTracking->GetQuaternion();
	//// プレイヤーID
	m_ID = pTracking->GetID();

	//// 登場アニメーション開始
	m_MoveState = enMoveState::App;

}
//動作関数
void CBalloon::Update()
{

	//--------------------------------------------------------
	// 状態
	//--------------------------------------------------------

	switch (m_MoveState)
	{
	case enMoveState::App:
	{
		// 登場時に少しずつ大きくする
		m_Scale += 0.00009f;
		
		if (m_Scale >= 0.004f)
		{
			m_Scale = 0.004f;
			m_MoveState = enMoveState::Idle;
		}

		//// サイズを設定
		m_vScale = D3DXVECTOR3(
			m_Scale,
			m_Scale,
			m_Scale);
	}
	break;

	case enMoveState::Idle:
	{
		//CCharacter::Update();
	}
	break;

	default:
		break;
	}
	////---------------------------------
	//// プレイヤーの後
	////---------------------------------
	//// 前方向（X+）を基準方向として設定
	//D3DXVECTOR3 forward(1.0f, 0.0f, 0.f);

	//// クォータニオンを回転行列へ変換
	//D3DXMATRIX matRot;
	//D3DXMatrixRotationQuaternion(&matRot, &m_vQuaternion);

	//// 基準となる前方向を回転させ、実際の進行方向を求める
	//D3DXVECTOR3 dir;
	//D3DXVec3TransformNormal(
	//	&dir,
	//	&forward,
	//	&matRot);

	//// 進行方向を正規化して、方向のみを取得
	//D3DXVec3Normalize(&dir, &dir);

	////ライフの数分風船を配置する（プレイヤーを囲む）
	//for (int i = 1;i <= m_Life;i++)
	//{

	//}

	//switch (m_MoveState)
	//{
	//case enMoveState::App:
	//{
	//	m_Scale += 0.0001f;
	//	if (m_Scale >= 0.5f)
	//	{
	//		m_Scale = 0.5f;
	//		m_MoveState = enMoveState::Idle;
	//	}
	//	//サイズを設定
	//	m_vScale = D3DXVECTOR3(m_Scale, m_Scale, m_Scale);
	//}
	//break;
	//case enMoveState::Idle:
	//	//コントローラー操作
	//	//m_vPosition.y += 1.5f;
	//	CCharacter::Update();
	//	break;
	//}

CCharacter::Update();
}
//描画関数
void CBalloon::Draw(const CCamera* pCamera)
{
	CCharacter::Draw(pCamera);
}

void CBalloon::SetBalloon(
    const D3DXVECTOR3& position,bool isHit, int life)
{
    // LifeはCGameから受け取る
    m_Life = life;
    // 座標はTrackingから取得
    m_vPosition = position;
}
