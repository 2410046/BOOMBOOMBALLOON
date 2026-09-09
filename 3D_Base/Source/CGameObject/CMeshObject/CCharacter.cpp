#include "CCharacter.h"

CCharacter::CCharacter()
	: m_Speed	    ( 0.1f )
	, m_ID          ( 0 )
	, m_Scale       ( 0 )

{
	D3DXQuaternionIdentity(&m_Quat);
}

CCharacter::~CCharacter()
{
}

void CCharacter::Update()
{
	// 時間を進める
	t += 0.05f;
	// 上下にふわふわ動く
	m_vPosition.y = 1.f + (float)(sin(t) * 0.3f);
	CStaticMeshObject::Update();
}

void CCharacter::Draw(const CCamera*pCamera)
{
	CStaticMeshObject::Draw(pCamera);
}