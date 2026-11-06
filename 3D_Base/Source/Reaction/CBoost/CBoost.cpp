#include "CBoost.h"
#include <cmath>

CBoost::CBoost()
    :CReaction()
{
}

void CBoost::Apply(const ReactionParam& param)
{
    // 前方向（X+）を基準方向として設定
    D3DXVECTOR3 forward(1.0f, 0.0f, 0.f);

    // クォータニオンを回転行列へ変換
    D3DXMATRIX matRot;
    D3DXMatrixRotationQuaternion(&matRot, &param.rot);

    // 基準となる前方向を回転させ、実際の進行方向を求める
    D3DXVECTOR3 dir;
    D3DXVec3TransformNormal(
        &dir,
        &forward,
        &matRot);

    // 進行方向を正規化して、方向のみを取得
    D3DXVec3Normalize(&dir, &dir);

    // ブーストを開始
    m_State.active = true;

    // 進行方向に初速度を設定
    m_State.velocity = dir * param.power;

    // ブーストの持続時間を設定
    m_State.timer = param.time;
}

void CBoost::Update()
{

    // ブースト中でなければ処理しない
    if (m_State.active == false)
    {
        return;
    }

    D3DXVECTOR3 oldPos = *m_pPosition;
    // 現在の速度を位置に加算して移動
    *m_pPosition += m_State.velocity;

    D3DXVECTOR3 move = *m_pPosition - oldPos;

    char debug[256];

    sprintf_s(
        debug,
        "Boost Move: %.2f, %.2f, %.2f\n",
        move.x,
        move.y,
        move.z
    );

    OutputDebugStringA(debug);
    // 速度を減衰させて、徐々に勢いを弱める
    m_State.velocity *= 0.9f;

    // ブーストの残り時間を減らす
    m_State.timer -= 1.0f;

    // 持続時間が終了したらブーストを終了
    if (m_State.timer <= 0.0f)
    {
        Stop();
    }
}


//// ブースト中でなければ処理しない
//if (m_State.active == false)
//{
//    return;
//}
//
//// 1フレームの移動量
//D3DXVECTOR3 move = m_State.velocity;
//
//// 移動距離
//float distance = D3DXVec3Length(&move);
//
//// 1回あたりの最大移動距離
//float maxStep = 0.2f;
//
//// 分割数
//int stepCount = static_cast<int>(
//    std::ceil(distance / maxStep));
//
//if (stepCount < 1)
//{
//    stepCount = 1;
//}
//
//// 1回あたりの移動量
//D3DXVECTOR3 step = move / static_cast<float>(stepCount);
//
//// 分割して移動
//for (int i = 0; i < stepCount; i++)
//{
//    *m_pPosition += step;
//
//    // ここで当たり判定を実行する
//}
//
//// 速度を減衰
//m_State.velocity *= 0.9f;
//
//// 残り時間を減らす
//m_State.timer -= 1.0f;
//
//// 持続時間が終了したらブーストを終了
//if (m_State.timer <= 0.0f)
//{
//    m_State.active = false;
//    m_State.velocity = D3DXVECTOR3(0.f, 0.f, 0.f);
//}