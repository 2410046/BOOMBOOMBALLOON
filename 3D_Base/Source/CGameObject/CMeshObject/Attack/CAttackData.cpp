//#include "CAttackData.h"
//// 攻撃データテーブル
//const std::vector<enData> s_AttackTable =
//{
//	//アタックA
//    enData(CXInput::KEY::A,
//		CEffect::AttackA, enType::A, 180.f, CSoundManager::SE_AttackAX),
//   //アタックB
//	enData(CXInput::KEY::B,
//		CEffect::AttackB, enType::B, -20.f, CSoundManager::SE_AttackBY),
//   //アタックX
//	enData(CXInput::KEY::X, 
//		CEffect::AttackX, enType::X, 30.f, CSoundManager::SE_AttackAX),
//	//アタックY
//	enData(CXInput::KEY::Y,
//
//
//		CEffect::AttackY, enType::Y, 1.f, CSoundManager::SE_AttackBY)
//};

#include "CAttackData.h"
// 攻撃データテーブル
const std::vector<enData> s_AttackTable =
{
	//アタックA
    enData(CXInput::KEY::A, 'S', '1',
		CEffect::AttackA, enType::A, 180.f, CSoundManager::SE_AttackAX),
   //アタックB
	enData(CXInput::KEY::B, 'D', '2',
		CEffect::AttackB, enType::B, -20.f, CSoundManager::SE_AttackBY),
   //アタックX
	enData(CXInput::KEY::X, 'A', '3',
		CEffect::AttackX, enType::X, 30.f, CSoundManager::SE_AttackAX),
	//アタックY
	enData(CXInput::KEY::Y, 'W', '4',
		CEffect::AttackY, enType::Y, 1.f, CSoundManager::SE_AttackBY)
};

