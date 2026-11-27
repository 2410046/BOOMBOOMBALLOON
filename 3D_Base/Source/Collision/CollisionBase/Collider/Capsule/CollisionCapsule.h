#pragma once
#include "Collision/CollisionBase/CollisionBase.h" // 当たり判定基底クラス

/**************************************************
*	カプセルコリジョンクラス
*   カプセル形状の当たり判定情報を計算・保持する
**/
class CollisionCapsule
	: public CollisionBase
{
private:
	//--------------------------------------
	// カプセルの始点・終点・半径を管理する構造体
	// Start : 始点
	// End   : 終点
	// Radius: 半径
	//--------------------------------------
	struct Capsule
	{
		D3DXVECTOR3 Start 
			= D3DXVECTOR3(0.f,0.f,0.f);
		D3DXVECTOR3 End 
			= D3DXVECTOR3(0.f, 0.f, 0.f);
		float Radius = 0.1f;
	};
public:
	//--------------------------------------
	// コンストラクタ
	// radius   : 半径
	// height   : 高さ（Start〜Endの長さ）
	// Listener : 衝突時の通知先
	// tag      : 所属するレイヤー
	//--------------------------------------
	CollisionCapsule(
		float radius, float height, 
		CollisionListener* Listener, LayerTag tag);
	// デストラクタ
	~CollisionCapsule() {};
	// ワールド座標を基準にカプセルの始点と終点を更新
	void WorldUpdate() override;
	// カプセル情報を取得
	const Capsule& GetCapsule() const { return m_Capsule; }
	// カプセルの半径を設定
	void SetRadius(float r) { m_Radius = r; }
	// コリジョン形状の種類を取得
	CollisionType GetType() const override { return CollisionType::Capsule; }
private:
	float m_Radius;   // カプセルの半径

	// 移動位置を補正するオフセット
	D3DXVECTOR3 m_MoveOffsetA;
	D3DXVECTOR3 m_MoveOffsetB;

	// ローカル座標での位置を補正するオフセット
	D3DXVECTOR3 m_LocalOffsetA;
	D3DXVECTOR3 m_LocalOffsetB;

	Capsule m_Capsule{}; // カプセル情報
};