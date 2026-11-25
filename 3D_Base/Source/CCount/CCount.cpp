#include"CCount.h"
//攻撃回数の制限
bool CCount::LimitCoolTime(const std::string& name)
{
	auto& data = m_CoolData.at(name);

	// 使用不可
	if (data.isCoolTime && data.count <= 0)
	{
		return false;
	}

	// 回数を減らす
	// 回数が0になったらクールタイム開始
// 回数を減らす
	data.count -= 1;

	// 回数が0以下になったらクールタイム開始
	if (data.count <= 0)
	{
		data.count = 0;
		data.isCoolTime = true;
	}

	return true;
}

//クールタイム中のフラグを取得
std::unordered_map<std::string, bool> CCount::GetCoolFlag() const
{
	std::unordered_map<std::string, bool> data;

	for (const auto& attack : m_CoolData)
	{
		data[attack.first] = attack.second.isCoolTime;
	}

	return data;
}
//クールタイム
void CCount::UpdateCoolTime()
{
	for (auto& data : m_CoolData)
	{
		// 回数が0ならクールタイム中
		if (!data.second.isCoolTime)
		{
			continue;
		}

		// クールタイム終了
		if (delta_clamp(
			data.second.coolTimer += 1.f, data.second.coolTime))
		{
			data.second.coolTimer = 0.0f;
			data.second.count = data.second.maxcount;
			data.second.isCoolTime = false;
		}
	}
}