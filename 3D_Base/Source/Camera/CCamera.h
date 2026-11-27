#pragma once
#include "Singleton.h"
/********************************************************************************
*	カメラクラス
*   ゲーム内のカメラの位置・向き・視点を管理するクラス
**/
class CCamera
	:public Singleton<CCamera>
{
private:
	friend class Singleton<CCamera>;
	CCamera();
public:
	//デストラクタ
	~CCamera();
	//更新関数
	void Update();
	//カメラ関数.
	void Camera();
	//プロジェクション関数.
	void Projection();
	//カメラの位置
	CAMERA     GetCamera()const { return m_Camera; }
	//ライトの位置
	LIGHT	   GetLight ()const { return m_Light; }
	//ビュー行列
	D3DXMATRIX GetView  ()const { return m_mView; }	
	//射影行列
	D3DXMATRIX GetProj  ()const { return m_mProj; }		
	//カメラの位置を設定
	void SetCamera(
		const D3DXVECTOR3& position, const D3DXVECTOR3& look);
	//ライトの位置を設定
	void SetLight(D3DXVECTOR3 light);
private:
	//カメラ情報.
	CAMERA			m_Camera;
	//ライト情報
	LIGHT			m_Light;
	//行列.
	D3DXMATRIX		m_mView;	//ビュー(カメラ)行列.
	D3DXMATRIX		m_mProj;	//射影（プロジェクション）行列.
};


