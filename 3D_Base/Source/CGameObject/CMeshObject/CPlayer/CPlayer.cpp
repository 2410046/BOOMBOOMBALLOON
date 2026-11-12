#include "CPlayer.h"

#include "MathUtility.h"
#include "Reaction/CReactionApply/CReactionFactory.h"
#include "CMeshObject/CTracking/CShot/CShot.h"	    //ショットクラス
#include "CGameObject/CMeshObject/CCloud/CCloud.h"  //雲クラス
#include "Asset/Effect/CEffectPlay.h"
namespace
{
	//カプセルのサイズ
	constexpr float radius = 0.7f;
	constexpr float height = 0.7f;

	constexpr float TimeSpeed  = 0.1f;	//経過速度
	constexpr float MaxTime    = 10.f;   //指定時間
	constexpr float Size_Speed = 0.0001f;
	constexpr float Base_Size = 0.01f;

	constexpr int Max_Boost  = 1;
	constexpr int Max_Shot  = 5;
	// 円の中心座標
	constexpr float CenterX = 0.f;
	constexpr float CenterZ = 13.5f;

	// 円の半径
	constexpr float RadiusX = 12.8f;
	constexpr float RadiusZ = 11.f;
}
//コンストラクタ
CPlayer::CPlayer()
	: m_MoveState		( enMoveState::App )
	, m_Life			( 3 )
	, m_Point			( 0 )
	, m_AttackData		( )
	, m_Effect			()
{	
	//カプセルの当たり判定
	m_pCollider = CreateCollider::CreateCaupsule(
		radius, height, this, CollisionBase::Player);
	m_vQuaternion
		= D3DXQUATERNION(0.0f, 0.7071068f, 0.0f, 0.7071068f);
	m_angle = 0.f;
	//攻撃制限数を設定
	m_AttackData["Shot"] = { Max_Shot,Max_Shot, 180.0f,0.f};
	m_AttackData["Boost"] = { Max_Boost,Max_Boost, 150.0f,0.f };
	m_AttackData["Invincible"] = { Max_Boost,Max_Boost, 150.0f, 0.f };
}
//デストラクタ
CPlayer::~CPlayer()
{
	CollisionManager::GetInstance()->Unregister(m_pCollider);
}
//動作関数
void CPlayer::Update()
{

	//クールタイム
	UpdateCoolTime();
	//移動制限
	UpdateMoveLimit();

	switch (m_MoveState)
	{

	case enMoveState::App:
	{
		//プレイヤーのサイズを増やす
		if (delta_clamp(m_Scale += Size_Speed, Base_Size))
		{
			m_Life = 3;
			m_MoveState = enMoveState::Live;
		}
		//サイズを設定
		m_vScale = D3DXVECTOR3(m_Scale, m_Scale, m_Scale);
	}
	break;
	case enMoveState::Boost:		//ブースト状態
	{
		CReaction::ReactionParam param;
		param.rot = m_vQuaternion;
		param.power = 2.f;

		m_pReaction = CReactionFactory::Create(CReaction::Boost);
		m_pReaction->Apply(param);

		const auto& effect = s_IDTable[m_ID];

		m_Effect["Boost"] = CreateEffect(
			effect.BoostEffect,
			m_vPosition,
			m_vQuaternion,
			0.5f,
			1.f);

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
	case enMoveState::Down://ダウン状態
	{
		m_Point = -20;

		const auto& effect = s_IDTable[m_ID];
		//エフェクト出現
		m_Effect["Down"] = CreateEffect(
			effect.DeleteEffect, m_vPosition);

		if (delta_clamp(m_Life -= 1, 5))
		{
			CSoundManager::GetInstance()->PlaySE(L"SE\\Dead");
			m_MoveState = enMoveState::Dead;
		}
		else
		{
			m_MoveState = enMoveState::Turn;
		}
	}
		break;
	case enMoveState::Turn://回転状態
		if (CCharacter::TurnUpdate())
		{
			m_angle = 0.f;
			LimitCoolTime("Invincible");
			m_MoveState = enMoveState::Invincible;
		}
		break;
	case enMoveState::Invincible://無敵状態
		m_vScale = D3DXVECTOR3(0.03f, 0.03f, 0.03f);
		// クールタイムが終了したら無敵解除
		if (!m_AttackData["Invincible"].isCoolTime)
		{
			m_vScale = D3DXVECTOR3(
				Base_Size,
				Base_Size,
				Base_Size);
			m_MoveState = enMoveState::Live;
		}
		break;
	case enMoveState::Dead://死亡状態
		//クール時間開始
		//プレイヤーのサイズを小さくする
		if (delta_clamp(m_Scale -= Size_Speed, Base_Size))
		{
			m_Point = -100;
			//スコアを半分減らす
			m_MoveState = enMoveState::App;
		}
		m_vScale = D3DXVECTOR3(m_Scale, m_Scale, m_Scale);
		break;
	default:
		break;
	}

	//コントローラー操作
	Controller();
	//ノックバック中
		if (m_pReaction)
		{
			m_pReaction->SetPosition(&m_vPosition);
			m_pReaction->SetQuaternion(&m_vQuaternion);
			m_pReaction->Update();
		}

		if (m_pReaction &&
			m_pReaction->Play(CReaction::Boost))
		{
			EffectUpdateY(
				m_Effect["Boost"], m_vPosition, m_vQuaternion);
		}

		CCharacter::Update();
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
//ポイントを取得
int CPlayer::GetPoint()
{
	int point = m_Point;
	m_Point = 0;
	return point;
}
//コントローラー操作
//プレイヤーの速度
void CPlayer::Controller()
{
#if 1
	//無敵状態と生存状態以外の場合
	if (m_MoveState != enMoveState::Live 
		&& m_MoveState != enMoveState::Invincible)
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

		if (GetAsyncKeyState('Z') & 0x8000)
		{
			// アニメーション中でなければ再生
			if (m_pReaction &&
				m_pReaction->Play(CReaction::Boost))
			{
				return;
			}
			if (LimitCoolTime("Boost"))
			{
				CSoundManager::GetInstance()->PlaySE(L"SE\\Boost");
				m_MoveState = enMoveState::Boost;
			}
		}
		if ((GetAsyncKeyState('X') & 0x8000))
		{
			// アニメーション中でなければ再生
			if (m_pReaction &&
				m_pReaction->Play(CReaction::Firing))
			{
				return;
			}

			if (LimitCoolTime("Shot"))
			{
				CSoundManager::GetInstance()->PlaySE(L"SE\\Shot");
				m_MoveState = enMoveState::Shot;
			}
		}
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
		CCharacter::Quotanion(moveDir);
		//nanamehayasi
	}
	m_vPosition.y = 1.f;
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

//攻撃回数の制限
bool CPlayer::LimitCoolTime(const std::string& name)
{
	auto& data = m_AttackData.at(name);

	// 使用不可
	if (data.isCoolTime && data.count <= 0)
	{
		return false;
	}

	// 回数を減らす
	// 回数が0になったらクールタイム開始
	if (delta_clamp(
		data.count -= 1, data.maxcount))
	{
		data.isCoolTime = true;
	}

	return true;
}
//移動制限
void CPlayer::UpdateMoveLimit()
{
	// 中心からの距離
	const float dx = m_vPosition.x - CenterX;
	const float dz = m_vPosition.z - CenterZ;

	// 楕円の範囲を超えているか確認
	const float distance = (dx * dx) / (RadiusX * RadiusX)
		+ (dz * dz) / (RadiusZ * RadiusZ);
	//トンネリング現象が解決しないため移動制限を設定
	if (distance > 1.0f)
	{
		// 中心からの方向を正規化する
		const float length = sqrtf(distance);
		m_vPosition.x = CenterX + dx / length;
		m_vPosition.z = CenterZ + dz / length;
	}
}
//クールタイム
void CPlayer::UpdateCoolTime()
{
	for (auto& data : m_AttackData)
	{
		// 回数が0ならクールタイム中
		if (!data.second.isCoolTime)
		{
			continue;
		}

		// クールタイム終了
		if (delta_clamp(
			data.second.coolTimer += 1.f, data.second.coolTime))
		{
			data.second.coolTimer = 0.0f;
			data.second.count = data.second.maxcount;
			data.second.isCoolTime = false;
		}
	}
}
//クールタイム中のフラグを取得
std::unordered_map<std::string, bool> CPlayer::GetCoolFlag() const
{
	std::unordered_map<std::string, bool> data;

	for (const auto& attack : m_AttackData)
	{
		data[attack.first] = attack.second.isCoolTime;
	}

	return data;
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
		//生存状態以外は無視
		if (other->m_MoveState != enMoveState::Live
			|| m_MoveState != enMoveState::Live)
		{
			return;
		}
		//相手のリアクション
		auto& BoostOther = other->m_pReaction;
		//ブースト状態
		if (m_pReaction&&m_pReaction->Play(CReaction::Boost))
		{
			CSoundManager::GetInstance()->PlaySE(L"SE\\PlayerHit");
			m_Point = 20;
    		m_pReaction->Stop();//リアクションを終わらせる
			//プレイヤーは風船とスコアを1つ取得する
			m_Life = std::clamp(m_Life + 1, 0, 5);
			//相手のプレイヤーをダウンx状態に
			other->m_MoveState = enMoveState::Down;
		}
		else//お互いブーストじゃない場合		
		{
			CSoundManager::GetInstance()->PlaySE(L"SE\\BaseHit");
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
	case CollisionBase::Cloud://雲に接触した場合
	{
		// ブースト状態なら止める
		if (m_pReaction && m_pReaction->Play(CReaction::Boost))
		{
			m_pReaction->Stop();
		}
		auto* cloud = dynamic_cast<CCloud*>(pCollider->GetListener());
		if (!cloud) break;

		//// 3. 押し戻した最新位置からノックバックを適用
		CReaction::ReactionParam param;
		param.from = cloud->GetPosition();
		param.to = GetPosition();
		m_pReaction = CReactionFactory::Create(CReaction::KnockBack);
		m_pReaction->Apply(param);
	}
	break;

	case CollisionBase::Shot://ショットに当たった瞬間
	{
		//ダウン状態は無視
		//生存状態以外は無視
		if (m_MoveState != enMoveState::Live)
		{
			return;
		}

		auto* shot =
			dynamic_cast<CShot*>(pCollider->GetListener());
		// 自分が発射したShotなら無視
		if (shot == nullptr|| shot->GetID() == m_ID)
		{
			return;
		}
		//ブースト状態
		if (m_pReaction && m_pReaction->Play(CReaction::Boost))
		{
			shot->SetFlag(false);//ショットが消える
		}
		else 
		{
			CSoundManager::GetInstance()->PlaySE(L"SE\\Ballon");
			// 相手のShotならダウン
			//スコアを減らす
			m_MoveState = enMoveState::Down;
		}
	}
	break;
	default:
		break;
	}
	
}