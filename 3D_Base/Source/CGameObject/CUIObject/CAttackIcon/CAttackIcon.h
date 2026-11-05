#pragma once
#include "CGameObject/CUIObject/CUIObject.h"
/********************************************************************************
*	アイコンクラス
**/
class CAttackIcon
	:public CUIObject
{
public:
	CAttackIcon();
	//デストラクタ
	~CAttackIcon();
	//動作関数
	virtual void Update() override;
	//描画関数
	virtual void Draw() override;

	// クールタイム情報を設定
	void SetCoolFlag(const std::unordered_map<std::string, bool>& data)
	{
		m_CoolTime = data;
	}
private:
	// クールタイム管理
	std::unordered_map<std::string, bool> m_CoolTime;
	static const int Max = 2;
	float m_Alpha[Max];
};