#pragma once
#include "CGameObject/CGameObject.h"
#include "Asset/Mesh/SkinMesh/CSkinMesh.h"
#include "Asset/Mesh/CMeshManager.h"
/************************************************************
*	スキンメッシュオブジェクトクラス.
**/
class CSkinMeshObject
	: public CGameObject
{
public:
	CSkinMeshObject();
	virtual ~CSkinMeshObject() override;

	//CGameObjectで純粋仮想関数の宣言がされてるのでこちらで定義を書く.
	virtual void Update() override;
	virtual void Draw(const CCamera* pCamera) override;

	//メッシュを接続する.
	void AttachMesh(CSkinMesh& pMesh);
	//メッシュを切り離す.
	void DetachMesh();

	//
protected:
	CSkinMesh*					m_pMesh;
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	//アニメーションコントローラ
	int							m_AnimNo;			//アニメーション番号
	double						m_AnimTime;			//アニメーション経過時間
	double						m_AnimSpeed;		//アニメーション速度
	D3DXVECTOR3					m_BonePos;			//ボーン座標
};
