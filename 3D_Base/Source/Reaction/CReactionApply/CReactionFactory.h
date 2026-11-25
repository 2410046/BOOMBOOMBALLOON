#pragma once
#include"CReaction.h"
class CReactionFactory
{
public:
    static std::shared_ptr<CReaction> Create(
        std::string type);
};