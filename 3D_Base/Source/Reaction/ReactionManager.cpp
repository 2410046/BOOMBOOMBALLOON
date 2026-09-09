#include "ReactionManager.h"
#include <algorithm>

CReactionManager::CReactionManager()
    :m_List()
{
}
CReactionManager::~CReactionManager()
{
}

// 初期化
void CReactionManager::Init()
{
    m_List.clear();
}
void CReactionManager::Apply(CReaction::MoveType type)
{
    for (auto& reaction : m_List)
    {
        if (auto* reaction = GetReaction(type))
        {
            //reaction->Apply(aa);
            return;
        }
    }
}
// 更新関数
void CReactionManager::Update(/*D3DXVECTOR3 pos*/)
{
    //----------------------------------
    // リアクション更新
    //----------------------------------
    for (const auto& pReaction : m_List)
    {
        //座標を設定
        pReaction->Update();
    }
}
//リアクション
CReaction* CReactionManager::GetReaction(CReaction::MoveType type)
{
    for (auto& reaction : m_List)
    {
        if (reaction->GetType() == type)
        {
            return reaction.get();
        }
    }
    return nullptr;
}

