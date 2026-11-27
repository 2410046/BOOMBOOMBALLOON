#pragma once
/**************************************************
*	スフィアコリジョンクラス
*   球形の当たり判定情報を計算・保持する
**/
#include "Collision/CollisionBase/CollisionBase.h" // 当たり判定基底クラス
class CollisionSphere
    : public CollisionBase
{
private:
    //--------------------------------------
    // 球の中心座標と半径を管理する構造体
    // Center : 中心座標
    // Radius : 半径
    //--------------------------------------
    struct SphereShape
    {
        D3DXVECTOR3 Center 
            = D3DXVECTOR3(0.f, 0.f, 0.f);
        float Radius = 0.1f;
    };
public:
    //--------------------------------------
    // コンストラクタ
    // radius   : 半径
    // Listener : 衝突時の通知先
    // tag      : 所属するレイヤー
    // offset   : 中心のローカルオフセット
    //--------------------------------------
    CollisionSphere(
        float radius,
        CollisionListener* Listener,
        LayerTag tag,
        const D3DXVECTOR3& offset = D3DXVECTOR3(0.f, 0.f, 0.f) 
    );
    // デストラクタ
    ~CollisionSphere() {};

    // ワールド座標を基準に球の中心座標を更新
    void WorldUpdate() override;

    // 球の情報を取得
    const SphereShape& GetSphere() const { return m_Sphere; }
   
    // コリジョン形状の種類を取得
    CollisionType GetType() const override { return CollisionType::Sphere; }
private:
    float m_Radius;          // 半径
    D3DXVECTOR3 m_Offset;    // 中心のローカルオフセット
    SphereShape m_Sphere{};    // スフィア情報
};