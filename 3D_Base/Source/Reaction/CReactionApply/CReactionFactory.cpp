#include "CReactionFactory.h"
#include "CBoost/CBoost.h"
#include "KnockBack/CKnockBack.h"
#include "CFiring/CFiring.h"

std::shared_ptr<CReaction> CReactionFactory::Create(
    std::string type)
{
    //リアクションの設定
    if (type == "Boost")
    {
        return std::make_unique<CBoost>();
    }
    else if (type == "KnockBack")
    {
        return std::make_unique<CKnockBack>();
    }
    else if (type == "Firing")
    {
        return std::make_unique<CFiring>();
    }
    else
    {
        return nullptr;
    }

}