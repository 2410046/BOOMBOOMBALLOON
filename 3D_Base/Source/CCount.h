#pragma once
#include <algorithm>
/********************************************************************************
*	カウントクラス.時間管理に使用する。
**/
//カウント
inline int CountUpdate()
{
    // 現在時間取得（秒）
    float currentTime = timeGetTime() / 1000.0f;

    // 前回更新からの経過時間を加算
    m_FrameTime += currentTime - m_LastUpdateTime;
    m_LastUpdateTime = currentTime;

    // 経過した秒数を返す
    return static_cast<int>(m_FrameTime);
};
//時間を止める
inline int MaxCount(int MaxTime)
{
    if (CountUpdate() >= MaxTime)
    {
        return CountUpdate() = MaxTime;
    }
}

inline float m_FrameTime;       // 累積経過時間（秒）
inline float m_LastUpdateTime;  // 前回更新時刻（秒）


