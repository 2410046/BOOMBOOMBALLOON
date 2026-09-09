#pragma once
#include "CReaction.h"

class CKnockBack
    :public CReaction
{
public:
    CKnockBack();
    ~CKnockBack()override{};
    //出現
    void Apply(const ReactionParam& param)override;
    //更新関数
    void Update()override;
    //モーションを設定
    virtual MoveType GetType() const override { return MoveType::Boost; };
protected:
};

