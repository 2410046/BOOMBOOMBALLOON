#pragma once
#include "Collision/CollisionListener/CollisionListener.h"
#include "CGameObject.h"

//--------------------------------------
// コリジョン（当たり判定）基底クラス
// すべての当たり判定オブジェクトの親クラス
//--------------------------------------
class CollisionBase
{
public:
    // レイヤー種類（衝突グループ）
    enum LayerTag
    {
        Player = 0,    // プレイヤー
        Shot,          //ショット
        Cloud,         // 雲
    };

    // コリジョン形状の種類
    enum CollisionType
    {
        Sphere = 0,    // 球
        Box,       // ボックス（AABB / OBB）
        Capsule,   // カプセル
    };

public:
    // コンストラクタ
    // type   : コリジョン形状
    // object : 所有しているオブジェクト（通知用）
    // layer  : 所属レイヤー
    CollisionBase(
        CollisionListener* object,
        LayerTag tag);

    virtual ~CollisionBase() {}

    //--------------------------------------
    // 更新処理（派生クラスで実装）
    //--------------------------------------
    virtual void WorldUpdate() = 0;

    //--------------------------------------
    // 衝突時処理
    // base : 衝突した相手
    //--------------------------------------
    void HitCollision(CollisionBase* base);

    // 所有オブジェクト取得
    CollisionListener* GetListener() const { return m_pLayer; }
    void* SetListener() const { return m_pLayer; }
    // タグ設定 / 取得
    void SetTag(LayerTag Tag) { m_Tag = Tag; }
    LayerTag  GetTag() const { return m_Tag; }
    // ヒット状態設定
    void SetHit(bool hit) { m_Hit = hit; }
    // コリジョン形状取得
    virtual CollisionType GetType() const = 0;
protected:
    LayerTag        m_Tag;         // 所属タグ
    bool            m_Hit;         // 衝突しているか
    CollisionListener* m_pLayer;   // 所有オブジェクト（通知先）
    D3DXVECTOR3     m_WorldPos;    // ワールド座標
};
