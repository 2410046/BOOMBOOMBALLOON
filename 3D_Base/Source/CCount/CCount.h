#pragma once
#include <unordered_map>
#include "MathUtility.h"
/********************************************************************************
*	カウントクラス
*   攻撃回数やクールタイムを管理する基底クラス
**/
class CCount
{
public:
	virtual ~CCount() = default;
	// クールタイム中の状態を取得
	std::unordered_map<std::string, bool> GetCoolFlag() const;
protected:
	// クールタイムの管理データ
	struct CoolData
	{
		int count = 0;
		int maxcount = 0;
		float coolTime = 180.0f;
		float coolTimer = 0.0f;
		bool isCoolTime = false;
	};
    // 攻撃回数を制限、クールタイムを判定
	bool LimitCoolTime(const std::string& name);
	//クールタイムの更新
	void UpdateCoolTime();
protected:
	// 攻撃ごとのクールタイム管理
	std::unordered_map<std::string, CoolData> m_CoolData = {};
};
