#pragma once
#include "Collision/CollisionBase/CollisionBase.h" // 当たり判定基底クラス

/**************************************************
*	カプセルコリジョンクラス
*	当たり判定に使用する
**/
class CollisionCapsule
	: public CollisionBase
{
public:
	//--------------------------------------
	// カプセル構造体
	// Start : 始点
	// End   : 終点
	// Radius: 半径
	//--------------------------------------
	struct Capsule
	{
		D3DXVECTOR3 Start = D3DXVECTOR3(0.f,0.f,0.f);
		D3DXVECTOR3 End = D3DXVECTOR3(0.f, 0.f, 0.f);
		float Radius = 0.1f;
	};
public:
	//--------------------------------------
	// コンストラクタ
	// radius : 半径
	// height : 高さ（Start〜Endの長さ）
	// object : 所有オブジェクト
	// layer  : 所属レイヤー
	//--------------------------------------
	CollisionCapsule(
		float radius, float height, CollisionListener* listener, LayerTag tag);

	~CollisionCapsule();

	//--------------------------------------
	// 更新処理
	// ワールド座標に応じてStart/Endを更新
	//--------------------------------------
	void WorldUpdate() override;

	//--------------------------------------
	// ローカルオフセット設定
	// モデル基準の位置ずれ
	//--------------------------------------
	void SetLocalOffsetA(const D3DXVECTOR3& offset) { m_LocalOffsetA = offset; }
	void SetLocalOffsetB(const D3DXVECTOR3& offset) { m_LocalOffsetB = offset; }

	//--------------------------------------
	// 移動オフセット設定
	// 動きに応じた補正（予測など）
	//--------------------------------------
	void SetMoveOffsetA(const D3DXVECTOR3& offset) { m_MoveOffsetA = offset; }
	void SetMoveOffsetB(const D3DXVECTOR3& offset) { m_MoveOffsetB = offset; }

	//--------------------------------------
	// カプセル情報取得
	//--------------------------------------
	const Capsule& GetCapsule() const { return m_Capsule; }

	//--------------------------------------
	// 半径設定
	//--------------------------------------
	void SetRadius(float r) { m_Radius = r; }

	CollisionType GetType() const override { return CollisionType::Capsule; }
private:
	float m_Radius; // カプセル半径

	// 移動補正オフセット（予測位置などに使用）
	D3DXVECTOR3 m_MoveOffsetA;
	D3DXVECTOR3 m_MoveOffsetB;

	// ローカル座標でのオフセット
	D3DXVECTOR3 m_LocalOffsetA;
	D3DXVECTOR3 m_LocalOffsetB;

	Capsule m_Capsule; // 計算済みカプセル情報
};