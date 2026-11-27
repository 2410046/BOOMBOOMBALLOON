#pragma once
#include "CGameObject.h"
#include "Asset/Mesh/StaticMesh/CStaticMesh.h"
#include "Asset/Effect/CEffect.h"
#include "Collision/CollisionListener/CollisionListener.h"
#include "Collision/CreateCollider/CreateCollider.h"

/************************************************************
*	スタティックメッシュオブジェクトクラス.
*   スタティックメッシュを使用するゲームオブジェクト
**/
class CStaticMeshObject
	: public CGameObject
{
public:
	//コンストラクタ
	CStaticMeshObject();
	//デストラクタ
	virtual ~CStaticMeshObject() override;
	//更新関数
	virtual void Update() override;
	//描画関数
	virtual void Draw( const CCamera*pCamera ) override;

	//メッシュを接続する.
	void AttachMesh( CStaticMesh& pMesh )
	{
		m_pMesh = &pMesh;
	}
	//メッシュを切り離す.
	void DetachMesh()
	{
		m_pMesh = nullptr;
	}

protected:
	CStaticMesh* m_pMesh;   // 接続しているスタティックメッシュ
};
