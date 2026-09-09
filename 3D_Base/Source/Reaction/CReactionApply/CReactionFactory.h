#pragma once
#include <memory>
#include "CReaction.h"

class CReactionFactory
{
public:
    static std::shared_ptr<CReaction> Create(
        CReaction::MoveType type);
};