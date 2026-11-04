#pragma once
#include <algorithm>
template <typename T>
//値を上限か下限まで増減するとき
bool delta_clamp(T& value, T max)
{
	value = std::clamp(value, T{ 0 }, max);
	return value == T{ 0 } || value == max;
}
