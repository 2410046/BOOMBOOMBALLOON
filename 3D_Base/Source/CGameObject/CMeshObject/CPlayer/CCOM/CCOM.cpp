#include "CCOM.h"

CCom::CCom()
	: m_ComState(enCOMState::Chase)
	, m_ThinkTimer(0)
{
}

CPlayer* CCom::GetNearestTarget()
{
	CPlayer* pNearest = nullptr;
	float minDistanceSq = FLT_MAX;

	for (auto* pOther : m_pOtherPlayers)
	{
		// 自分自身や無効なポインタはスキップ
		if (!pOther || pOther == this) continue;

		// 死亡状態または出現状態の相手は対象外
		// (CPlayerにGetMoveState等のゲッターがあるとより正確です)

		D3DXVECTOR3 diff = pOther->GetPosition() - m_vPosition;
		float distSq = D3DXVec3LengthSq(&diff);

		if (distSq < minDistanceSq)
		{
			minDistanceSq = distSq;
			pNearest = pOther;
		}
	}

	return pNearest;
}

void CCom::Controller()
{
	// 生存状態または無敵状態以外は操作不能
	if (m_MoveState != enMoveState::Live)
	{
		return;
	}

	// 最寄りのターゲットを取得
	CPlayer* pTarget = GetNearestTarget();
	if (!pTarget) return;

	// ターゲットまでのベクトルと距離
	D3DXVECTOR3 toTarget = pTarget->GetPosition() - m_vPosition;
	toTarget.y = 0.0f; // Y軸は無視
	float distance = D3DXVec3Length(&toTarget);

	// 状態判定
	m_ThinkTimer++;
	if (m_ThinkTimer > 30) // 30フレーム毎に思考状態を更新
	{
		m_ThinkTimer = 0;

		if (distance > 8.0f)
		{
			m_ComState = enCOMState::Chase;
		}
		else if (distance < 3.0f)
		{
			////ライフが少なかったら離れる
			//if (m_Life <= 2)
			//{
			//	m_ComState = enCOMState::Avoid;
			//}
			//else
			//{
				// 近すぎる場合は確率で攻撃か距離をとる
				m_ComState = (rand() % 2 == 0) ? enCOMState::Attack : enCOMState::Avoid;
		

		}
		else
		{
			//m_ComState = enCOMState::KeepDist;
		}

	}

	// 思考状態に応じた移動方向の算出
	D3DXVECTOR3 moveDir(0.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&toTarget, &toTarget);

	switch (m_ComState)
	{
	case enCOMState::Chase: // ターゲットへ接近
		moveDir = toTarget;
		break;

	case enCOMState::KeepDist: // ターゲットを中心に周回するように移動
		//moveDir = D3DXVECTOR3(-toTarget.z, 0.0f, toTarget.x);
		break;

	case enCOMState::Avoid: // ターゲットから離れる
		moveDir = -toTarget;
		break;

	case enCOMState::Attack: // 攻撃チャンス
		moveDir = toTarget;

		// 近距離かつ正面方向であればブースト攻撃
		if (distance < 4.0f && LimitCoolTime("Boost"))
		{
			CSoundManager::GetInstance()->PlaySE(L"SE\\Boost");
			m_MoveState = enMoveState::Boost;
			return;
		}
		// 中距離であればショット攻撃
		else if (distance < 17.0f && LimitCoolTime("Shot"))
		{
			// ブースト発動中でなければショット
			if (!m_pReaction || !m_pReaction->Play(CReaction::Firing))
			{
				CSoundManager::GetInstance()->PlaySE(L"SE\\Shot");
				m_MoveState = enMoveState::Shot;
				return;
			}
		}
		break;
	}

	// 移動処理の実行
	float len = D3DXVec3Length(&moveDir);
	if (len > 0.01f)
	{
		m_vPosition += moveDir * m_Speed;
		CCharacter::Quotanion(moveDir);
	}
}