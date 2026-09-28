#include "CPlayer.h"
#include "Asset/CXInput/CXInput.h"
#include "MathUtility.h"
#include <algorithm>
#include "Reaction/CReactionApply/CReactionFactory.h"
#include "CMeshObject/CTracking/CShot/CShot.h"	    //ショットクラス

namespace
{
	//カプセルのサイズ
	constexpr float radius = 0.5f;
	constexpr float height = 0.7f;

	constexpr float TimeSpeed  = 0.1f;	//経過速度
	constexpr float MaxTime    = 10.f;   //指定時間
	constexpr float Size_Speed = 0.0001f;
	constexpr float Base_Size  = 0.01f;
}
//コンストラクタ
CPlayer::CPlayer()
	: m_MoveState		( enMoveState::App )
	, m_StateTime		( 5.f )
	, m_Life			( 5 )

{	
	//カプセルの当たり判定
	m_pCollider = CreateCollider::CreateCaupsule(
		radius, height, this, CollisionBase::Player);
	m_vQuaternion
		= D3DXQUATERNION(0.0f, 0.7071068f, 0.0f, 0.7071068f);
}
//デストラクタ
CPlayer::~CPlayer()
{
	CollisionManager::GetInstance()->Unregister(m_pCollider);
}
//動作関数
void CPlayer::Update()
{
	switch (m_MoveState)
	{

	case enMoveState::App:
	{
		//プレイヤーのサイズを大きくする
		m_Scale += Size_Speed;
		if (m_Scale>=Base_Size)
		{
			m_Scale = Base_Size;
			m_MoveState = enMoveState::Live;
		}
		//サイズを設定
		m_vScale = D3DXVECTOR3(m_Scale, m_Scale, m_Scale);
	}
		break;
	case enMoveState::Live:
		//コントローラー操作
		Controller();
		CCharacter::UpDown();
		break;
	case enMoveState::Boost:		//ブースト状態
	{
		//プレイヤーの方向にまっすぐ進む
		CReaction::ReactionParam param;
		param.rot = m_vQuaternion;
		m_pReaction = CReactionFactory::Create(CReaction::Boost);
		m_pReaction->Apply(param);
		m_MoveState = enMoveState::Live;
	}
		break;
	case enMoveState::Shot://ショット状態
	{
		CReaction::ReactionParam param;
		param.rot = m_vQuaternion;
		m_pReaction = CReactionFactory::Create(CReaction::Firing);
		m_pReaction->Apply(param);
		m_MoveState = enMoveState::Live;		//一瞬で切り替える
	}
		break;
	case enMoveState::Hit://ヒット状態
		m_MoveState = enMoveState::Live;
		break;
	case enMoveState::Down://ダウン状態
		m_Life = std::clamp(m_Life - 1, 0, 5);
		m_MoveState = enMoveState::Invincible;
		break;
	case enMoveState::Invincible://無敵状態

		m_angle += 0.1f; // 回転速度

		D3DXQuaternionRotationYawPitchRoll(
			&m_vQuaternion,
			m_angle,
			0.0f,
			0.0f);

		if (m_angle >= D3DX_PI * 2.0f)
		{
			//コントローラー操作
			Controller();
			CCharacter::UpDown();
			m_angle = 0.f;
			//無敵時間開始
			m_MoveState = enMoveState::Live;
		}	
		break;
	default:
		break;
	}
	//ノックバック中

		if (m_pReaction)
		{
			m_pReaction->SetPosition(&m_vPosition);
			m_pReaction->SetQuaternion(&m_vQuaternion);
			m_pReaction->Update();
		}
	
}
//描画関数
void CPlayer::Draw(
	const CCamera* pCamera)
{
	const auto& param = s_IDTable[m_ID];
	//色の設定
	m_pMesh->SetDiffuse(param.Color);
	//m_pMesh->SetAmbient(param.Color);
	CCharacter::Draw(pCamera);
}

//コントローラー操作
//プレイヤーの速度
void CPlayer::Controller()
{
#if 1
	//ダウン状態の場合
	if (m_MoveState != enMoveState::Live )
	{
		return;
	}

	//キーボード
	float moveX = 0.0f;
	float moveZ = 0.0f;
	switch (m_ID)
	{
	case 0:
		if (GetAsyncKeyState(VK_UP) & 0x8000) moveZ += 1.0f;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) moveZ -= 1.0f;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) moveX -= 1.0f;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) moveX += 1.0f;
		
		if (GetAsyncKeyState('Z') & 0x8000) m_MoveState = enMoveState::Boost;
		if (GetAsyncKeyState('X') & 0x0001) m_MoveState = enMoveState::Shot;
		break;
	case 1:
		if (GetAsyncKeyState('W') & 0x8000) moveZ += 1.0f;
		if (GetAsyncKeyState('S') & 0x8000) moveZ -= 1.0f;
		if (GetAsyncKeyState('A') & 0x8000) moveX -= 1.0f;
		if (GetAsyncKeyState('D') & 0x8000) moveX += 1.0f;

		if (GetAsyncKeyState('1') & 0x8000) m_MoveState = enMoveState::Boost;
		if (GetAsyncKeyState('2') & 0x0001) m_MoveState = enMoveState::Shot;
		break;
	default:
		break;
	}

	// 移動ベクトル
	D3DXVECTOR3 moveDir(moveX, 0.0f, moveZ);

	float len = D3DXVec3Length(&moveDir);

	if (len > 0.01f)
	{
		// 移動
		m_vPosition += moveDir * m_Speed;
		//クオータニオン
		Quotanion(moveDir);
		//nanamehayasi
	}
#else
	//ダイレクト操作
	CXInput* pPad = CXInput::GetInstance(m_ID); // 1Pコントローラー

	if (pPad && pPad->Update())
	{
		//ダウン状態じゃない場合
		if (m_MoveState == Down)
		{
			return;
		}
		float LX = static_cast<float>(pPad->GetLThumbX()) / 32767.0f;
		float LY = static_cast<float>(pPad->GetLThumbY()) / 32767.0f;

		// デッドゾーン処理
		const float DEAD_ZONE
			= static_cast<float>(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) / 32767.0f;
		if (fabs(LX) < DEAD_ZONE) LX = 0.0f;
		if (fabs(LY) < DEAD_ZONE) LY = 0.0f;

		// 入力方向にそのまま動く（Z軸反転なし）
		D3DXVECTOR3 moveDir(LX, 0.0f, LY);

		float len = D3DXVec3Length(&moveDir);


		if (len > 0.01f) {
			// 移動
			m_vPosition += moveDir * m_Speed;

			Quotanion(moveDir);

			m_MoveState = enMoveState::Walk;	//移動状態
		}
		else
		{
			m_MoveState = enMoveState::Idle;    //待機状態
		}

	}
#endif

}
//クオータニオン対応
void CPlayer::Quotanion(D3DXVECTOR3 moveDir)
{
	D3DXVec3Normalize(&moveDir, &moveDir);

	// ===== 回転（クォータニオン）=====
	float yaw = atan2f(moveDir.x, moveDir.z) - D3DX_PI / 2;

	D3DXQUATERNION targetRot;
	D3DXQuaternionRotationYawPitchRoll(
		&targetRot,
		yaw,
		0.0f,
		0.0f
	);

	// スムーズ回転
	D3DXQuaternionSlerp(
		&m_vQuaternion,
		&m_vQuaternion,
		&targetRot,
		0.2f
	);
}

//当たり判定
void CPlayer::OnCollision(CollisionBase* pCollider)
{
	switch (pCollider->GetTag())
	{
		//プレイヤーと接触した場合
	case CollisionBase::Player:
	{
		auto* other = dynamic_cast<CPlayer*>(pCollider->GetListener());
		if (!other || other == this)
			return;
		//ダウン状態は無視
		if (m_MoveState == enMoveState::Down
			|| m_MoveState == enMoveState::Invincible)
		{
			return;
		}
		//相手のリアクション
		auto& BoostOther = other->m_pReaction;

		//風船が多いほどスコアの量が上がる
		//ブースト状態
		if (m_pReaction&&m_pReaction->Play(CReaction::Boost))
		{
			m_MoveState = enMoveState::Hit;//当てた

			m_pReaction->Stop();//リアクションを終わらせる
			//プレイヤーは風船とスコアを1つ取得する
			m_Life = std::clamp(m_Life + 1, 0, 5);
			//相手のプレイヤーをダウンx状態に
			other->m_MoveState = enMoveState::Down;
		}
		else//お互いブーストじゃない場合		
		{
			//ノックバック
			CReaction::ReactionParam param;
			param.from = other->GetPosition();
			param.to = GetPosition();
			m_pReaction = CReactionFactory::Create(CReaction::KnockBack);
			m_pReaction->Apply(param);

		}
	}
	//相手もブースト状態ならノックバックにしたい
		break;
	//case CollisionBase::Cloud://雲に接触した場合
	//{
	//	//ノックバック
	//	CReaction::ReactionParam param;
	//	param.to = GetPosition();
	//	//param.from = GetPosition();
	//	m_pReaction = CReactionFactory::Create(CReaction::KnockBack);
	//	m_pReaction->Apply(param);
	//}
	//	break;

	case CollisionBase::Shot://ショットに当たった瞬間
	{
		auto* shot =
			dynamic_cast<CShot*>(pCollider->GetListener());

		if (shot == nullptr)
		{
			return;
		}
		// 自分が発射したShotなら無視
		if (shot->GetID() == m_ID)
		{
			return;
		}
		// 相手のShotならダウン
		m_MoveState = enMoveState::Down;
		//ほかのプレイヤーに自分のショットが当たったらスコア
	}
	break;
	default:
		break;
	}
	
}
