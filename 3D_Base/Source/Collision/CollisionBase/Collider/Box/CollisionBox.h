#pragma once
#include "Collision/CollisionBase/CollisionBase.h"  // 当たり判定基底クラス

/**************************************************
*	ボックスコリジョンクラス
*   ボックス形状の当たり判定情報を計算・保持する
**/
class CollisionBox
	: public CollisionBase
{
private:
	//--------------------------------------
	// ボックスの最小座標と最大座標を管理する構造体
	// Min : 最小座標
	// Max : 最大座標
	//--------------------------------------
	struct Box
	{
		D3DXVECTOR3 Min;
		D3DXVECTOR3 Max;
	};

public:
	//--------------------------------------
	// コンストラクタ
	// Length   : ボックスのサイズ
	// Listener : 衝突時の通知先
	// tag      : 所属するレイヤー
	//--------------------------------------
	CollisionBox(
		D3DXVECTOR3 Length, 
		CollisionListener* Listener, LayerTag tag);
	// デストラクタ
	~CollisionBox() {};

	// ワールド座標を基準にボックスの最小座標と最大座標を更新
	void WorldUpdate() override;
	// ボックスのサイズを設定
	void SetLength(const D3DXVECTOR3& length) { m_Length = length; }
	// ボックスの情報を取得
	const Box& GetBox() const { return m_Box; }
	// コリジョン形状の種類を取得
	CollisionType GetType() const override { return CollisionType::Box; }
private:
	D3DXVECTOR3 m_Length;       // ボックスのサイズ
	D3DXVECTOR3 m_Offset;       // 中心位置のオフセット
	Box         m_Box{};          // ボックス情報

};