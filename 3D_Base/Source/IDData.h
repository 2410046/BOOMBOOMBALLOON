#pragma once
#include "Asset/Effect/CEffect.h"
#include "Asset/SoundManager/CSoundManager.h"
#include <d3dx9math.h>
//タイプごとの設定
struct IDData
{
	D3DXVECTOR4           Color;	    //色
	std::u16string        BoostEffect;	//ブーストエフェクト
	std::u16string        DeleteEffect;	//削除エフェクト

	IDData(
		D3DXVECTOR4 color,
		const std::u16string& Boost, 
		const std::u16string& Delete)
		: Color(color)
		, BoostEffect(Boost)
		, DeleteEffect(Delete)
	{
	}
};
//IDテーブル
inline  const
std::vector<IDData> s_IDTable=
{
   //ID1
   IDData(D3DXVECTOR4(1.0f, 0.5f, 0.5f, 1.0f),u"Boost1",u"delete1"),
   //ID2
   IDData(D3DXVECTOR4(0.4f, 0.8f,1,1),u"Boost2",u"delete2"),
   //ID3
   IDData(D3DXVECTOR4(1,1,0,1),u"Boost3",u"delete3"),
   //ID4
   IDData(D3DXVECTOR4(0,1,0,1),u"Boost4",u"delete4")
};
