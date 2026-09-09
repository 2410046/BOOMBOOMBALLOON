#include "CCamera.h"
//インストラクタ
CCamera::CCamera()
		: m_mView()
		, m_mProj()
		, m_Camera()
		, m_Light()
{
	//カメラ座標.
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 1.0f, -2.0f);
	//カメラの注視点
	m_Camera.vLook = D3DXVECTOR3(0.0f, 1.0f, 10.0f);
	//ライト情報  
	m_Light.vDirection = D3DXVECTOR3(0.5f, -1.0f, 1.0f);
	//ライトの強度
	m_Light.fIntensity = 1.f;
}
//デストラクタ
CCamera::~CCamera()
{
}
//動作関数
void CCamera::Update()
{
	if (GetAsyncKeyState('W') & 0x8000) m_Camera.vPosition.z += 0.1f; // 前進
	if (GetAsyncKeyState('S') & 0x8000) m_Camera.vPosition.z -= 0.1f; // 後退
	if (GetAsyncKeyState('A') & 0x8000) m_Camera.vPosition.x -= 0.1f; // 左
	if (GetAsyncKeyState('D') & 0x8000) m_Camera.vPosition.x += 0.1f; // 右
	if (GetAsyncKeyState('Z') & 0x8000) m_Camera.vPosition.y += 0.1f; // 上
	if (GetAsyncKeyState('X') & 0x8000) m_Camera.vPosition.y -= 0.1f; // 下
}
//カメラ関数.
void CCamera::Camera()
{

	D3DXVECTOR3 cam_pos = m_Camera.vPosition;	//カメラ位置
	D3DXVECTOR3 cam_look = m_Camera.vLook;		//カメラの注視点の位置
	D3DXVECTOR3	vUpVec(0.0f, 1.0f, 0.0f);		//上方（ベクトル）.

	//ビュー（カメラ）変換.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)ビュー計算結果.
		&cam_pos, &cam_look, &vUpVec);
}
//プロジェクション関数.
void CCamera::Projection()
{
	//y方向の視野角。数値を大きくしたら視野が狭くなる.
	float fov_y = static_cast<FLOAT>(D3DXToRadian(45.0));	//ラジアン値.
	//アスペクト（幅÷高さ）.
	float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
	float near_z = 0.1f;
	float far_z = 100.0f;

	//プロジェクション（射影）変換.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,	//(out)プロジェクション計算結果.
		fov_y,		//視野角（FOV：Field of View）.
		aspect,		//アスペクト.
		near_z,		//近いビュー平面のz値.
		far_z);	//遠いビュー平面のz値.
}
//カメラの位置を設定
void CCamera::SetCamera(
	const D3DXVECTOR3& position, const D3DXVECTOR3& look)
{
	m_Camera.vPosition = position; // カメラ位置
	m_Camera.vLook = look;       // 注視点
}
//ライトの位置を設定
void CCamera::SetLight(D3DXVECTOR3 light)
{
	m_Light.vDirection = light;
}


