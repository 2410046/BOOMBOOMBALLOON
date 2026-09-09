#pragma once

//----------------------------------------------------
// UpdateTimer
// 値を  max の範囲まで増やす
//----------------------------------------------------
template <typename T>
bool UpdateTimer(T& timer, T delta, T limit)
{
    timer += delta;

    // カウントアップ（deltaがプラスの場合)
    if (delta > 0 && timer >= limit)
    {
        timer = 0;
        return true;
    }

    // カウントダウン（deltaがマイナスの場合)
    if (delta < 0 && timer <= limit)
    {
        timer = limit;
        return true;
    }

    return false;
}
//----------------------------------------------------
// Wrap
// 値が範囲外になった場合、反対側へ循環させる
//----------------------------------------------------
template <typename W>
W Wrap(W value, W min, W max)
{
    if (value < min)
    {
        return max;
    }
    if (value > max)
    {
        return min;
    }
    return value;
}
