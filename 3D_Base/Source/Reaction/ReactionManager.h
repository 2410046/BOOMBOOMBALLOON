#pragma once
#include <vector>
#include <memory>
#include "CReaction.h"
#include"Singleton.h"
//======================================
// リアクション管理クラス
//======================================
class CReactionManager
    :public Singleton<CReactionManager>
{
private:
    friend class Singleton<CReactionManager>;
    CReactionManager();
public:
    ~CReactionManager();
    // 初期化
    void Init();
    // 出現
    void Apply(CReaction::MoveType type);
    // 更新関数
    void Update();

    CReaction* GetReaction(CReaction::MoveType type);
private:
    std::vector<std::shared_ptr<CReaction>> m_List;
};