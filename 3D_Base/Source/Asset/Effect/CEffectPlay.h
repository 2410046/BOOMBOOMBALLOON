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
    CEffect::SetQuaternion(m_Effect, Quaternion );
}
inline void EffectUpdateY(
    ::EsHandle m_Effect, const D3DXVECTOR3& position, const D3DXQUATERNION& Quaternion)
{
    // 前方向（Z+）を基準方向として設定
    D3DXVECTOR3 forward(0.0f, 0.f, 1.f);

    // クォータニオンを回転行列へ変換
    D3DXMATRIX matRot;
    D3DXMatrixRotationQuaternion(&matRot, &Quaternion);

    // 基準となる前方向を回転させ、実際の進行方向を求める
    D3DXVECTOR3 dir;
    D3DXVec3TransformNormal(
        &dir,
        &forward,
        &matRot);

    // 進行方向を正規化して、方向のみを取得
    D3DXVec3Normalize(&dir, &dir);

    CEffect::SetLocation(m_Effect, position);
    CEffect::SetRotationY(m_Effect, dir, D3DXToRadian(90.f));
}
//エフェクトの終了
inline void EffectEnd(::EsHandle m_Effect)
{
    CEffect::Stop(m_Effect);
}