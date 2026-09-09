#include "CFiring.h"


CFiring::CFiring()
    :CReaction()
{
}

void CFiring::Apply(const ReactionParam& param)
{
	m_ShotBaseRot  = param.rot;//クオータニオンを取得
	m_State.active = true;
	m_State.timer  = 5.f;
}

void CFiring::Update()
{
	if (m_State.active == false)
	{
		return;
	}
	// 状態経過時間を減少させる
	m_State.timer -= 0.1f;
   // 傾き計算用の時間係数を算出
   // 0～1の範囲で変化する値として使用する
	float t = m_State.timer / 5.0f;

	// サイン波を使ってピッチ角を計算
	// 発射後の上下方向の揺れ（傾き）を滑らかに変化させる
	float pitch = D3DX_PI / 4.0f * sinf(t * D3DX_PI);

	// 傾き回転用のクォータニオンを作成
	D3DXQUATERNION tilt;
	// Yaw、Rollは固定し、Pitch方向のみ回転させる
	D3DXQuaternionRotationYawPitchRoll(
		&tilt,
		0.f,
		0.f,
		pitch);

	// 発射時の基準回転に対して、今回の傾きを合成する
	// 常に元の発射姿勢を基準にして傾きを適用する
	*m_pQuaternion = tilt * m_ShotBaseRot;

	//終了
	if (m_State.timer <= 0.0f)
	{
		//タイマーをリセット
		m_State.timer = 5.f;
		m_State.active = false;
	}
}
