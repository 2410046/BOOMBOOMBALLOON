#pragma once
/**************************************************
*	スフィアコリジョンクラス
*   当たり判定に使用する
**/
#include "Collision/CollisionBase/CollisionBase.h" // 当たり判定基底クラス
class CollisionSphere
    : public CollisionBase
{
public:
    //--------------------------------------
    // 球構造体
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
    // radius : 半径
    // object : 所有オブジェクト
    // layer  : 所属レイヤー
    //--------------------------------------
    CollisionSphere(
        float radius, CollisionListener* listener, LayerTag tag);

    ~CollisionSphere();

    //--------------------------------------
    // 更新処理
    // ワールド座標から中心を計算
    //--------------------------------------
    void WorldUpdate() override;

    //--------------------------------------
    // 球情報取得
    //--------------------------------------
    const SphereShape& GetSphere() const { return m_Sphere; }

    CollisionType GetType() const override { return CollisionType::Sphere; }
private:
    float m_Radius;          // 半径（元データ）
    D3DXVECTOR3 m_Offset;    // 中心のローカルオフセット
    SphereShape m_Sphere;    // 計算済み球情報
};