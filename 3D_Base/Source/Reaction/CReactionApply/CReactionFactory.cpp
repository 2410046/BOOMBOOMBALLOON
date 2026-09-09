#include "CReactionFactory.h"
#include "CBoost/CBoost.h"
#include "KnockBack/CKnockBack.h"
#include "CFiring/CFiring.h"

std::shared_ptr<CReaction> CReactionFactory::Create(
    CReaction::MoveType type)
{
    switch (type)
    {
    case CReaction::Boost:
        return std::make_unique<CBoost>();

    case CReaction::KnockBack:
        return std::make_unique<CKnockBack>();

    case CReaction::Firing:
        return std::make_unique<CFiring>();
    default:
        return nullptr;
    }
}