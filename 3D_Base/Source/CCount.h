#pragma once
#include <algorithm>
/********************************************************************************
*	カウントクラス.時間管理に使用する。
**/

inline float m_FrameTime;       // 累積経過時間（秒）
inline float m_LastUpdateTime;  // 前回更新時刻（秒）

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
inline float MaxCount(float maxTime)
{
    m_FrameTime = std::clamp(m_FrameTime, 0.f,maxTime);

    return m_FrameTime;
}


inline bool Limit(float maxTime)
{
    CountUpdate();
    if (m_FrameTime >= maxTime)
    {
        //ResetCount();
        return true;
    }
    //m_FrameTime = std::clamp(m_FrameTime, 0.f,maxTime);

    return false;
}
//------------------------------------------------------------
// カウントリセット
//------------------------------------------------------------
inline void ResetCount()
{
    m_FrameTime = 0.0f;

    // 次回CountUpdate()で現在時刻を取り直す
   m_LastUpdateTime = timeGetTime() / 1000.0f;
}




