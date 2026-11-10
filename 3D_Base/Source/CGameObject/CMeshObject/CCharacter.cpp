#include "CCharacter.h"
namespace
{
	constexpr float Speed = 0.05f;
}
CCharacter::CCharacter()
	: m_Speed	    ( 0.1f )
	, m_ID          ( 0 )
	, m_Scale       ( 0 )

{
}

CCharacter::~CCharacter()
{
}

void CCharacter::Update()
{

	CStaticMeshObject::Update();
}

void CCharacter::Draw(const CCamera*pCamera)
{
	CStaticMeshObject::Draw(pCamera);
}
//オブジェクトを上下させる
void CCharacter::UpDown()
{
	// 時間を進める
	t += Speed;
	// 上下にふわふわ動く
	m_vPosition.y = 1.f + (float)(sin(t) * 0.3f);
}
//回転
bool CCharacter::Turn(float Speed,float Max,bool Loop)
{
	if (m_angle >= Max)
	{
		m_angle = Max;
		if (Loop)
		{
			m_angle = 0;
		}
		return true;
	}

	m_angle += Speed; // 回転速度

	D3DXQuaternionRotationYawPitchRoll(
		&m_vQuaternion,
		m_angle,
		0.0f,
		0.0f);
	return false;
}

//クオータニオン対応
void CCharacter::Quotanion(D3DXVECTOR3 moveDir)
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