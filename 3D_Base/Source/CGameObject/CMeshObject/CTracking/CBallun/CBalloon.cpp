#include "CBalloon.h"
CBalloon::CBalloon()
    : m_PlayerPos(0.0f, 0.0f, 0.0f)
    , m_Life(0)
	, m_MoveState(enMoveState::Idle)
	, m_pTracking(nullptr)
{
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
CCharacter::Update();
}
//描画関数
void CBalloon::Draw(const CCamera* pCamera)
{
	const auto& param = s_IDTable[m_ID];
	//色の設定
	//m_pMesh->SetDiffuse(param.Color);
	m_pMesh->SetAmbient(param.Color);
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
