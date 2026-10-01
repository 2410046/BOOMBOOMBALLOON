//#pragma once
//#include <algorithm>
//#include "CGameObject/CSpriteObject/CTime/CTime.h"		//タイムクラス
///********************************************************************************
//*	カウントクラス.時間管理に使用する。
//**/
//inline float m_LastUpdateTime;  // 前回更新時刻（秒）
//
//inline float GetCurrentTimes()
//{
//    return timeGetTime() / 1000.0f;
//}
//
////カウント
//inline float CountUpdate(float & m_Count)
//{
//    // 現在時間取得（秒）
//    float currentTime = timeGetTime() / 1000.0f;
//
//    // 前回更新からの経過時間を加算
//    m_Count += currentTime - GetCurrentTimes();
//
//    // 経過した秒数を返す
//    return m_Count;
//};
////時間を止める
//inline float MaxCount(float m_Count ,float maxTime)
//{
//    return  m_Count = std::clamp(m_Count, 0.f, maxTime);;
//}
////------------------------------------------------------------
//// カウントリセット
////------------------------------------------------------------
//inline void ResetCount(float & m_Count)
//{
//    m_Count = 0.0f;
//
//    // 次回CountUpdate()で現在時刻を取り直す
//   m_LastUpdateTime = timeGetTime() / 1000.0f;
//}

#pragma once

#include <Windows.h>
#include <algorithm>
#include <unordered_map>

/********************************************************************************
*	カウントクラス
*	時間管理に使用する。
*
*	m_Countは各クラスが持つ。
*	前回更新時刻はCount側でm_Countごとに管理する。
********************************************************************************/

//------------------------------------------------------------
// m_Countごとの前回更新時刻
//------------------------------------------------------------
inline std::unordered_map<float*, float>& GetLastUpdateTimes()
{
	static std::unordered_map<float*, float> lastUpdateTimes;

	return lastUpdateTimes;
}

//------------------------------------------------------------
// 現在時刻取得
//------------------------------------------------------------
inline float GetCurrentTimes()
{
	return timeGetTime() / 1000.0f;
}

//------------------------------------------------------------
// カウント更新
//------------------------------------------------------------
inline float CountUpdate(float& m_Count)
{
	auto& lastUpdateTimes = GetLastUpdateTimes();

	// 現在時間
	float currentTime = GetCurrentTimes();

	// このm_Countが初めて登録された場合
	auto [it, inserted] =
		lastUpdateTimes.emplace(&m_Count, currentTime);

	if (inserted)
	{
		// 初回は時間を加算しない
		return m_Count;
	}

	// 前回更新から経過した時間を加算
	m_Count += currentTime - it->second;

	// 今回の時間を次回の前回時間として保存
	it->second = currentTime;

	return m_Count;
}

//------------------------------------------------------------
// 最大値で止める
//------------------------------------------------------------
inline float MaxCount(float m_Count, float maxTime)
{
	return std::clamp(m_Count, 0.0f, maxTime);
}

//------------------------------------------------------------
// カウントリセット
//------------------------------------------------------------
inline void ResetCount(float& m_Count)
{
	// カウントを0にする
	m_Count = 0.0f;

	// リセットした時刻を次回の基準時間にする
	GetLastUpdateTimes()[&m_Count] = GetCurrentTimes();
}

//------------------------------------------------------------
// カウント情報削除
//------------------------------------------------------------
inline void ReleaseCount(float& m_Count)
{
	GetLastUpdateTimes().erase(&m_Count);
}


