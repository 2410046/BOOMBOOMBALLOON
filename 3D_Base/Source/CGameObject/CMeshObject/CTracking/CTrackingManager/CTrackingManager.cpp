#include "CTrackingManager.h"

// 初期化
void CTrackingManager::Init()
{
    m_Trackings.clear();
}

// Tracking登録
void CTrackingManager::AddTracking(
    std::unique_ptr<CTracking> tracking)
{
    if (tracking == nullptr)
    {
        return;
    }

    m_Trackings.push_back(
        std::move(tracking));
}

// Tracking取得
CTracking*
CTrackingManager::GetTracking(int ID)
{
    if (ID < 0 ||
        ID >= static_cast<int>(
            m_Trackings.size()))
    {
        return nullptr;
    }

    return m_Trackings[ID].get();
}