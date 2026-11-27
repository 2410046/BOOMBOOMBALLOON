#include"CCount.h"
// 攻撃回数を制限、クールタイムを判定
bool CCount::LimitCoolTime(const std::string& name)
{
	// 指定した攻撃の管理データを取得
	auto& data = m_CoolData.at(name);

	// クールタイム中、または使用回数が残っていない場合は使用不可
	if (data.isCoolTime && data.count <= 0)
	{
		return false;
	}

	// 使用回数を減らし、残り回数が0になったらクールタイムを開始
	if (delta_clamp(
		data.count -= 1,data.maxcount))
	{
		data.isCoolTime = true;
	}

	return true;
}

// クールタイム中の状態を取得
std::unordered_map<std::string, bool> CCount::GetCoolFlag() const
{
	std::unordered_map<std::string, bool> data;
	// 各クールタイム状態を取得
	for (const auto& count : m_CoolData)
	{
		data[count.first] = count.second.isCoolTime;
	}

	return data;
}
// クールタイムの更新
void CCount::UpdateCoolTime()
{
	// 各クールタイムを更新
	for (auto& data : m_CoolData)
	{
		// クールタイム中でなければスキップ
		if (!data.second.isCoolTime)
		{
			continue;
		}

		// クールタイムが終了したら使用回数を元に戻す
		if (delta_clamp(
			data.second.coolTimer += 1.f, data.second.coolTime))
		{
			data.second.coolTimer = 0.0f;
			data.second.count = data.second.maxcount;
			data.second.isCoolTime = false;
		}
	}
}