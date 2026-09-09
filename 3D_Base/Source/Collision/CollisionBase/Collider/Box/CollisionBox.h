#pragma once
#include "Collision/CollisionBase/CollisionBase.h"  // 当たり判定基底クラス

/**************************************************
*	ボックスコリジョンクラス（AABB）
*   当たり判定に使用する
**/
class CollisionBox
	: public CollisionBase
{
public:
	//--------------------------------------
	// AABB構造体
	// Min : 最小座標
	// Max : 最大座標
	//--------------------------------------
	struct Box
	{
		D3DXVECTOR3 Min;
		D3DXVECTOR3 Max;
	};

public:
	// コンストラクタ
	// Length : ボックスのサイズ（半径ではなく大きさ）
	// object : 所有オブジェクト
	// layer  : 所属レイヤー
	CollisionBox(
		D3DXVECTOR3 Length, CollisionListener* listener, LayerTag tag);

	~CollisionBox();

	//--------------------------------------
	// 更新処理
	// ワールド座標からMin/Maxを計算
	//--------------------------------------
	void WorldUpdate() override;

	//--------------------------------------
	// サイズ設定
	//--------------------------------------
	void SetLength(const D3DXVECTOR3& length) { m_Length = length; }

	//--------------------------------------
	// Box情報取得
	//--------------------------------------
	const Box& GetBox() const { return m_Box; }

	CollisionType GetType() const override { return CollisionType::Box; }
private:
	Box m_Box;                  // 計算済みAABB
	D3DXVECTOR3 m_Length;       // ボックスサイズ
	D3DXVECTOR3 m_Offset;       // 中心からのオフセット
};