#pragma once

class CPlayer;
/********************************************************************************
* 追跡クラス
* プレイヤーの座標と方向を取得
*
**/
class CTracking
{
public:

    CTracking() = default;
    ~CTracking() = default;

    // 追跡対象を設定
    void SetTarget(CPlayer* pPlayer);

    // Playerの座標
    D3DXVECTOR3 GetPosition() const;

    // Playerの方向
    D3DXQUATERNION GetQuaternion() const;

    // 対象取得
    CPlayer* GetTarget() const;
    //ID
    int GetID() const;
private:

    CPlayer* m_pTarget = nullptr;
};