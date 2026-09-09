#pragma once
#include "CReaction.h"

class CFiring
    :public CReaction
{
public:
    CFiring();
    ~CFiring()override {};
    //出現
    void Apply(const ReactionParam& param)override;
    //更新関数
    void Update()override;
    //モーションを設定
    virtual MoveType GetType() const override { return MoveType::Firing; };
    //virtual D3DXQUATERNION GetRot() const override { return m_vQuaternion; };
private:
    D3DXQUATERNION m_ShotBaseRot;


};

