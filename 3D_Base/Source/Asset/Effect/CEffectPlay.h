#pragma once
#include"CEffect.h"
//エフェクトハンドル
inline EsHandle CreateEffect(
    const std::u16string& fileName,
    const D3DXVECTOR3& position,
    const D3DXQUATERNION& Quaternion = D3DXQUATERNION(0.f, 0.f, 0.f, 1.f),
    float scale = 0.5f,
    float speed = 1.0f)
{
    EsHandle effect = CEffect::Play(fileName, position);

    CEffect::SetScale(
        effect,D3DXVECTOR3(scale, scale, scale));

    CEffect::SetQuaternion(effect, Quaternion);
    CEffect::SetLocation(effect, position);
    CEffect::SetSpeed(effect, speed);

    return effect;
}

//エフェクトの更新
inline void EffectUpdate(
    ::EsHandle m_Effect, const D3DXVECTOR3& position, const D3DXQUATERNION& Quaternion)
{
    CEffect::SetLocation(m_Effect, position);
    CEffect::SetQuaternion(m_Effect, Quaternion);
}

//エフェクトの終了
inline void EffectEnd(::EsHandle m_Effect)
{
    CEffect::Stop(m_Effect);
}