#include "CollisionCapsule.h"

//--------------------------------------
// コンストラクタ
// radius : カプセル半径
// height : カプセルの高さ（Start→Endの長さ）
// object : 所有オブジェクト
// layer  : 所属レイヤー
//--------------------------------------
CollisionCapsule::CollisionCapsule(
    float radius, float height, CollisionListener* listener, LayerTag tag)
    : CollisionBase(listener, tag)
    , m_Radius(radius)
    , m_IsInitialized(false)
{
    // ローカル座標での始点・終点
    m_LocalOffsetA = D3DXVECTOR3(0, 0, 0);
    m_LocalOffsetB = D3DXVECTOR3(0, height, 0);

    // 移動補正（初期はなし）
    m_MoveOffsetA = D3DXVECTOR3(0, 0, 0);
    m_MoveOffsetB = D3DXVECTOR3(0, 0, 0);
}

CollisionCapsule::~CollisionCapsule()
{
}

//--------------------------------------
// 更新処理
// ワールド座標に基づいてカプセルの位置を更新
//--------------------------------------
void CollisionCapsule::WorldUpdate()
{

        // 所有オブジェクトを取得
    CGameObject* object =
        dynamic_cast<CGameObject*>(GetListener());

    if (!object)
        return;

    // ワールド行列取得
    const D3DXMATRIX& world = object->GetWorldMatrix();

    // 前フレームのカプセルを保存
    if (m_IsInitialized)
    {
        m_BeforeCapsule = m_Capsule;
    }

    // ローカル + 移動オフセットを合成
    D3DXVECTOR3 offsetA = m_LocalOffsetA + m_MoveOffsetA;
    D3DXVECTOR3 offsetB = m_LocalOffsetB + m_MoveOffsetB;

    // ワールド座標へ変換
    D3DXVec3TransformCoord(
        &m_Capsule.Start, &offsetA, &world);

    D3DXVec3TransformCoord(
        &m_Capsule.End, &offsetB, &world);

    // 半径を反映
    m_Capsule.Radius = m_Radius;

    // 初回は現在位置を前フレーム位置にも設定
    if (!m_IsInitialized)
    {
        m_BeforeCapsule = m_Capsule;
        m_IsInitialized = true;
    }

    // 中心位置
    m_WorldPos = (m_Capsule.Start + m_Capsule.End) * 0.5f;

}


//// 所有オブジェクトを取得
//CGameObject* object = dynamic_cast<CGameObject*>(GetListener());
//if (!object) return;
//
//// 更新前のカプセルを保存
//Capsule before = m_Capsule;
//
//// ワールド行列取得
//const D3DXMATRIX& world = object->GetWorldMatrix();
//
//// ローカル + 移動オフセットを合成
//D3DXVECTOR3 offsetA = m_LocalOffsetA + m_MoveOffsetA;
//D3DXVECTOR3 offsetB = m_LocalOffsetB + m_MoveOffsetB;
//
//// ワールド座標へ変換
//D3DXVec3TransformCoord(&m_Capsule.Start, &offsetA, &world);
//D3DXVec3TransformCoord(&m_Capsule.End, &offsetB, &world);
//
//// 半径を反映
//m_Capsule.Radius = m_Radius;
//
//// 中心位置（デバッグ・共通処理用）
//m_WorldPos = (m_Capsule.Start + m_Capsule.End) * 0.5f;
//
//// 初回だけ前後の位置を同じにする
//if (!m_IsInitialized)
//{
//    m_BeforeCapsule = m_Capsule;
//    m_IsInitialized = true;
//}
//else
//{
//    m_BeforeCapsule = before;
//}


    //// 所有オブジェクトを取得
    //CGameObject* object = dynamic_cast<CGameObject*>(GetListener());
    //if (!object) return;

    //// ワールド行列取得
    //const D3DXMATRIX& world = object->GetWorldMatrix();

    //// ローカル + 移動オフセットを合成
    //D3DXVECTOR3 offsetA = m_LocalOffsetA + m_MoveOffsetA;
    //D3DXVECTOR3 offsetB = m_LocalOffsetB + m_MoveOffsetB;

    //// ワールド座標へ変換
    //D3DXVec3TransformCoord(&m_Capsule.Start, &offsetA, &world);
    //D3DXVec3TransformCoord(&m_Capsule.End, &offsetB, &world);

    //// 半径を反映
    //m_Capsule.Radius = m_Radius;

    //// 中心位置（デバッグ・共通処理用）
    //m_WorldPos = (m_Capsule.Start + m_Capsule.End) * 0.5f;


    //// 所有オブジェクトを取得
  //CGameObject* object = dynamic_cast<CGameObject*>(GetListener());
  //if (!object) return;
  //
  //// 更新前のカプセルを保存
  //Capsule before = m_Capsule;
  //
  //// ワールド行列取得
  //const D3DXMATRIX& world = object->GetWorldMatrix();
  //
  //// ローカル + 移動オフセットを合成
  //D3DXVECTOR3 offsetA = m_LocalOffsetA + m_MoveOffsetA;
  //D3DXVECTOR3 offsetB = m_LocalOffsetB + m_MoveOffsetB;
  //
  //// ワールド座標へ変換
  //D3DXVec3TransformCoord(&m_Capsule.Start, &offsetA, &world);
  //D3DXVec3TransformCoord(&m_Capsule.End, &offsetB, &world);
  //
  //// 半径を反映
  //m_Capsule.Radius = m_Radius;
  //
  //// 中心位置（デバッグ・共通処理用）
  //m_WorldPos = (m_Capsule.Start + m_Capsule.End) * 0.5f;
  //
  //// 初回だけ前後の位置を同じにする
  //if (!m_IsInitialized)
  //{
  //    m_BeforeCapsule = m_Capsule;
  //    m_IsInitialized = true;
  //}
  //else
  //{
  //    m_BeforeCapsule = before;
  //}