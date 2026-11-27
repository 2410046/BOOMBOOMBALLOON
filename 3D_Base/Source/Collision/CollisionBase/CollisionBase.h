#pragma once
#include "Collision/CollisionListener/CollisionListener.h"
#include "CGameObject.h"
/********************************************************************************
*	コリジョン（当たり判定）基底クラス
**/
class CollisionBase
{
public:
    // レイヤーの種類
    enum LayerTag
    {
        Player = 0,    // プレイヤー
        Shot,          // ショット
        Cloud,         // 雲
    };

    // コリジョン形状の種類
    enum CollisionType
    {
        Sphere = 0,    // 球
        Box,           // ボックス（AABB / OBB）
        Capsule,       // カプセル
    };
public:
    //--------------------------------------
    // コンストラクタ
    // Listener : 衝突時の通知先
    // tag      : 所属するレイヤー
    //--------------------------------------
    CollisionBase(
        CollisionListener* object,
        LayerTag tag);

    // デストラクタ
    virtual ~CollisionBase() {}

    // ワールド座標に基づいてコリジョンの位置や状態を更新
    virtual void WorldUpdate() = 0;

    //--------------------------------------
    // 衝突した相手のオブジェクトに通知
    // base : 衝突した相手のコリジョン
    //--------------------------------------
    void HitCollision(CollisionBase* base);

    // 所有オブジェクトの取得
    CollisionListener* GetListener() const { return m_pListener; }

    // タグ設定、取得
    LayerTag  GetTag() const { return m_Tag; }

    // 衝突状態の設定
    void SetHit(bool hit) { m_Hit = hit; }

    // コリジョン形状の取得
    virtual CollisionType GetType() const = 0;

protected:
    LayerTag        m_Tag;           // 所属レイヤー
    bool            m_Hit;           // 衝突状態
    CollisionListener* m_pListener;  // 所有オブジェクト（通知先）
    D3DXVECTOR3     m_WorldPos;      // ワールド座標
};
