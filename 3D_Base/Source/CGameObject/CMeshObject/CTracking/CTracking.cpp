#include "CTracking.h"
#include "CGameObject/CMeshObject/CPlayer/CPlayerManager.h"	    //プレイヤークラス

//============================================================
// 対象を設定
//============================================================
void CTracking::SetTarget(CPlayer* pPlayer)
{
    m_pTarget = pPlayer;
}

//============================================================
// 座標取得
//============================================================
D3DXVECTOR3 CTracking::GetPosition() const
{
    if (m_pTarget == nullptr)
    {
        return D3DXVECTOR3(
            0.0f,
            0.0f,
            0.0f);
    }

    return m_pTarget->GetPosition();
}

//============================================================
// 方向取得
//============================================================
D3DXQUATERNION CTracking::GetQuaternion() const
{
    if (m_pTarget == nullptr)
    {
        return D3DXQUATERNION(
            0.0f,
            0.0f,
            0.0f,
            0.0f);
    }

    return m_pTarget->GetQuaternion();
}

//============================================================
// 対象取得
//============================================================
CPlayer* CTracking::GetTarget() const
{
    return m_pTarget;
}

int CTracking::GetID() const
{
    if (m_pTarget == nullptr)
    {
        return -1;
    }

    return m_pTarget->GetID();
}