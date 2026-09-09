#pragma once
#include "Asset/Mesh/StaticMesh/CStaticMesh.h"
/**************************************************
*	メッシュクラス
* 　メッシュを読み込み当たり判定に使用する
**/
class CMesh
{
public:
	CMesh();
	~CMesh();
	//モデルに合わせたバウンディングスフィアを作成
	HRESULT CreateSphereForMesh(const CStaticMesh& pMesh);
private:

};
