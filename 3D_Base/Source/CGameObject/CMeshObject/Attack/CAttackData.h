//#pragma once
//#include "Asset/Effect/CEffect.h"
//#include "Asset/SoundManager/CSoundManager.h"
//#include <d3dx9math.h>
//#include "Asset/CXInput/CXInput.h"
//// ==============================
//// 攻撃データ（仕様のみ）
//// ==============================
//struct enData
//{
//	// --- 入力 ---
//	CXInput::KEY padKey;	//コントローラー
//	// --- 攻撃内容 ---
//	CEffect::enList effect;	       //エフェクト
//	enType type;			       //攻撃タイプ
//	float rot;				       //エフェクトの方向
//	CSoundManager::enList sound;   //SE
//
//	enData(
//		CXInput::KEY pKey,
//		CEffect::enList eff,
//		enType t,
//		float r,
//		CSoundManager::enList s
//		)
//		: padKey(pKey)
//		, effect(eff)
//		, type(t)
//		, rot(r)
//		, sound(s)
//	{
//	}
//};
////攻撃テーブル
//extern const std::vector<enData> s_AttackTable;


#pragma once
#include "Asset/Effect/CEffect.h"
#include "Asset/SoundManager/CSoundManager.h"
#include <d3dx9math.h>
#include "Asset/CXInput/CXInput.h"
// ==============================
// 攻撃データ（仕様のみ）
// ==============================
struct enData
{
	// --- 入力 ---
	CXInput::KEY padKey;	//コントローラー
	int key0;				// プレイヤー0
	int key1;				// プレイヤー1

	// --- 攻撃内容 ---
	CEffect::enList effect;	       //エフェクト
	enType type;			       //攻撃タイプ
	float rot;				       //エフェクトの方向
	CSoundManager::enList sound;   //SE

	enData(
		CXInput::KEY pKey,
		int k0, int k1,
		CEffect::enList eff,
		enType t,
		float r,
		CSoundManager::enList s
	)
		: padKey(pKey)
		, key0(k0)
		, key1(k1)
		, effect(eff)
		, type(t)
		, rot(r)
		, sound(s)
	{
	}
};
//攻撃テーブル
extern const std::vector<enData> s_AttackTable;