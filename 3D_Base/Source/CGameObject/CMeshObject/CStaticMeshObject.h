#pragma once
#include "CGameObject.h"
#include "Asset/Mesh/StaticMesh/CStaticMesh.h"
#include "Asset/AssetManager/AssetManager.h"
#include "Asset/Effect/CEffect.h"
#include "Collision/CollisionListener/CollisionListener.h"
#include "Collision/CreateCollider/CreateCollider.h"

/************************************************************
*	スタティックメッシュオブジェクトクラス.
**/
class CStaticMeshObject
	: public CGameObject
{
public:
	CStaticMeshObject();
	virtual ~CStaticMeshObject() override;

	//CGameObjectで純粋仮想関数の宣言がされてるのでこちらで定義を書く.
	virtual void Update() override;
	virtual void Draw( const CCamera*pCamera ) override;

	//メッシュを接続する.
	void AttachMesh( CStaticMesh& pMesh ){
		m_pMesh = &pMesh;
	}
	//メッシュを切り離す.
	void DetachMesh(){
		m_pMesh = nullptr;
	}
	//コライダー取得
	const std::shared_ptr<CollisionBase>& GetCollider() const
	{
		return m_pCollider;
	}
protected:
	CStaticMesh*		m_pMesh;
	bool                m_ActEffect;		// エフェクトが発生
	float               CollisionScale;
	std::shared_ptr<CollisionBase>	m_pCollider;	//当たり判定
};
