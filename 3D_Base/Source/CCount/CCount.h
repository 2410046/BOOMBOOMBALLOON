#pragma once
#include <memory>
#include <unordered_map>
#include "MathUtility.h"
/********************************************************************************
*	カウントを使用するクラスに継承する
**/
class CCount
{
public:
	virtual ~CCount() = default;
	//クールタイム中のフラグを取得
	std::unordered_map<std::string, bool> GetCoolFlag() const;
protected:
	struct CoolData
	{
		int count = 0;
		int maxcount = 0;
		float coolTime = 180.0f;
		float coolTimer = 0.0f;
		bool isCoolTime = false;
	};
	//攻撃回数の制限
	bool LimitCoolTime(const std::string& name);
	//クールタイムの更新
	void UpdateCoolTime();
protected:
	std::unordered_map<std::string, CoolData> m_CoolData = {};
};
