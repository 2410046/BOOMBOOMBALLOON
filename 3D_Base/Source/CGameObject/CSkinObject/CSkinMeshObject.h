#pragma once
#include "CGameObject/CGameObject.h"
#include "Asset/Mesh/SkinMesh/CSkinMesh.h"
#include "Asset/Mesh/CMeshManager.h"
/************************************************************
*	スキンメッシュオブジェクトクラス.
*   スキンメッシュを使用するゲームオブジェクト
**/
class CSkinMeshObject
	: public CGameObject
{
public:
	//コンストラクタ
	CSkinMeshObject();
	//デストラクタ
	virtual ~CSkinMeshObject() override;
	//更新関数
	virtual void Update() override;
	//描画関数
	virtual void Draw(const CCamera* pCamera) override;
	//メッシュを接続する.
	void AttachMesh(CSkinMesh& pMesh);
	//メッシュを切り離す.
	void DetachMesh();
protected:
	CSkinMesh*					m_pMesh;			//スキンメッシュ
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	    //アニメーションコントローラ
	int							m_AnimNo;			//アニメーション番号
	double						m_AnimTime;			//アニメーション経過時間
	double						m_AnimSpeed;		//アニメーション速度
	D3DXVECTOR3					m_BonePos;			//ボーン座標
};
