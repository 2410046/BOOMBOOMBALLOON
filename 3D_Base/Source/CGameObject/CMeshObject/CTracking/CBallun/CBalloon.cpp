#include "CBalloon.h"
CBalloon::CBalloon()
    : m_PlayerPos(0.0f, 0.0f, 0.0f)
    , m_Life(0)
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
	AttachMesh(*CAssetManager::GetStatic(L"Asset\\Balloon"));

	// プレイヤーの現在位置を取得
	SetPosition(
		pTracking->GetPosition());

	//// プレイヤーの現在方向を取得
	m_vQuaternion =
		pTracking->GetQuaternion();
	//// プレイヤーID
	m_ID = pTracking->GetID();

	//風船の出現
	Spawn();

}
//動作関数
void CBalloon::Update()
{
	if (m_Life <= 0)
	{
		Spawn();
	}
    CCharacter::UpDown(m_vPosition.y);
}
//描画関数
void CBalloon::Draw(const CCamera* pCamera)
{
	const auto& param = s_IDTable[m_ID];
	m_pMesh->SetAmbient(param.Color);
	CCharacter::Draw(pCamera);
}
//風船の出現
bool CBalloon::Spawn()
{
	// 登場時に少しずつ大きくする
	if (delta_clamp(m_Scale += 0.00009f, 0.004f))
	{
		return true;
	}
	//// サイズを設定
	m_vScale = D3DXVECTOR3(m_Scale, m_Scale, m_Scale);
	return false;
}

void CBalloon::SetBalloon(
    const D3DXVECTOR3& position,bool isHit, int life)
{
    // LifeはCGameから受け取る
    m_Life = life;
    // 座標はTrackingから取得
    m_vPosition = position;
}
