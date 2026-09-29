#pragma once
#include"CEffect.h"
//エフェクトハンドル
inline EsHandle CreateEffect(
    CEffect::enList type,
    const D3DXVECTOR3& position,
    const D3DXVECTOR3& rotation,
    float scale,
    float speed = 1.0f)
{
    EsHandle effect = CEffect::Play(type, position);

    CEffect::SetScale(
        effect,
        D3DXVECTOR3(scale, scale, scale));

    CEffect::SetRotation(effect, rotation);
    CEffect::SetLocation(effect, position);
    CEffect::SetSpeed(effect, speed);

    return effect;
}

//エフェクトの更新
inline void EffectUpdate(
    ::EsHandle m_Effect, const D3DXVECTOR3& position, const D3DXVECTOR3& rotation)
{
    CEffect::SetLocation(m_Effect, position);
    CEffect::SetRotation(m_Effect, rotation);
}

//エフェクトの終了
inline void EffectEnd(::EsHandle m_Effect)
{
    CEffect::Stop(m_Effect);
}