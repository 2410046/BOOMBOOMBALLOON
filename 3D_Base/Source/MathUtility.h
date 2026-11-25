#pragma once
#include <algorithm>
template <typename T>
//値を上限か下限まで増減するとき
bool delta_clamp(T& value, T max)
{
	value = std::clamp(value, T{ 0 }, max);
	return value == T{ 0 } || value == max;
}

template <typename E>
bool UpdateTimer(E& timer, E delta, E limit)
{
    timer += delta;

    // カウントアップ（deltaがプラスの場合)
    if (delta > 0 && timer >= limit
        || delta < 0 && timer <= limit)    // （deltaがマイナスの場合)
    {
        timer = limit;
        return true;
    }
    return false;
}