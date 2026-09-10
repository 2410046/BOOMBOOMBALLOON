#include "CShot.h"
#include "Reaction/CReactionApply/CReactionFactory.h"


namespace
{
	//当たり判定
	constexpr float radius = 0.4f;
}
CShot::CShot()
	: m_ShotFlag( false )
{
	m_vScale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);

	//スフィアの当たり判定これを追加するとエラーが起こる
	//ショットが消えるときにそのエラーが起きる
	m_pCollider = CreateCollider::CreateSphere(
		radius,this, CollisionBase::Shot);
}


CShot::~CShot()
{
	CollisionManager::GetInstance()->Unregister(m_pCollider);
}
void CShot::Init(CTracking* pTracking)
{
	if (pTracking == nullptr)
	{
		return;
	}

	// プレイヤーの現在位置を取得
	SetPosition(
		pTracking->GetPosition());

	// プレイヤーの現在方向を取得
	m_vQuaternion =
		pTracking->GetQuaternion();

	AttachMesh(*AssetManager::GetStatic("Shot"));

	// プレイヤーID
	m_ID = pTracking->GetID();

	//方向や座標を取得
	CReaction::ReactionParam param;
	param.rot = m_vQuaternion;
	param.time = 200.f;
	param.power = 1.f;
	m_pReaction = CReactionFactory::Create(CReaction::Boost);
	m_pReaction->Apply(param);

	// 生存
	m_ShotFlag = true;
}
//動作関数
void CShot::Update()
{
	if (!m_ShotFlag)
	{
		return;
	}

	// リアクションが存在しない場合
	if (m_pReaction == nullptr)
	{
		m_ShotFlag = false;
		return;
	}

	// 座標・回転をリアクションに渡す
	m_pReaction->SetPosition(&m_vPosition);
	m_pReaction->SetQuaternion(&m_vQuaternion);

	// リアクション更新
	m_pReaction->Update();

	// リアクション終了
	if (m_pReaction->TimeOut())
	{
		m_ShotFlag = false;
	}
}
//描画関数
void CShot::Draw(const CCamera* pCamera)
{
	if (!m_ShotFlag)
	{
		return;
	}
	const auto& param = s_IDTable[m_ID];
	//色の設定
	m_pMesh->SetAmbient(param.Color);
	CCharacter::Draw(pCamera);
}

void CShot::SetShot(
	const D3DXVECTOR3& position, const D3DXQUATERNION& Quaternion, int ID)
{
	m_vPosition = position;
	m_vQuaternion = Quaternion;
	m_ID = ID;

	m_ShotFlag = true;
}
//当たり判定
void CShot::OnCollision(CollisionBase* base)
{
	//ショットを打ってない状態
	if (!m_ShotFlag)
	{
		return;
	}

	switch (base->GetTag())
	{
	case CollisionBase::Shot://ショットに当たった場合
	{
		auto* shot = dynamic_cast<CShot*>(base->GetListener());
		if (!shot || shot == this)
		{
			return;
		}
		m_ShotFlag = false;
	}
		break;
	case CollisionBase::Player://プレイヤーに当たった場合
	case CollisionBase::Cloud://雲に当たった場合
		m_ShotFlag = false;
		break;
	default:
		break;
	}
}
