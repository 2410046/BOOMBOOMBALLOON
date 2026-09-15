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
	D3DXQuaternionIdentity(&m_Quat);
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
