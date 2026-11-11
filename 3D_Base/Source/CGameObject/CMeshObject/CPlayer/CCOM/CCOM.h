#pragma once
#pragma once
#include "CGameObject/CMeshObject/CPlayer/CPlayer.h"

class CCom : public CPlayer
{
public:
    CCom();
    virtual ~CCom() override = default;

protected:
    // 人間操作の代わりにAI思考による操作を実行
    virtual void Controller()override;

private:
    // 一番近いターゲット（他のプレイヤー）を取得
    CPlayer* GetNearestTarget();

    // COMの思考ロジック
    void UpdateAI();

private:
    enCOMState m_ComState;
    int m_ThinkTimer; // 行動切り替え用のタイマー
};
    //// COMの行動
    //enum class enAction
    //{
    //    None,
    //    Approach,
    //    Escape,
    //    Attack,
    //    Avoid,
    //    Boost
    //};

    //// 自分のプレイヤー
    //CPlayer* m_pPlayer = nullptr;

    //// 攻撃対象
    //CPlayer* m_pTarget = nullptr;

    //// 現在の行動
    //enAction m_Action = enAction::None;

    //// 移動方向
    //D3DXVECTOR3 m_Direction = D3DXVECTOR3(0.f, 0.f, 0.f);

    //// 判断時間
    //float m_ThinkTime = 0.f;
//};