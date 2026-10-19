#pragma once
#include "Asset/Effect/CEffect.h"
#include "Asset/SoundManager/CSoundManager.h"
#include <d3dx9math.h>
//タイプごとの設定
struct IDData
{
	D3DXVECTOR4           Color;	    //色
	std::wstring           DeleteEffect;	//削除エフェクト

	IDData(
		D3DXVECTOR4 color,
		std::wstring  Delete)
		: Color(color)
		, DeleteEffect(Delete)
	{
	}
};
//IDテーブル
inline  const
std::vector<IDData> s_IDTable=
{
   //ID1
   IDData(D3DXVECTOR4(1.0f, 0.5f, 0.5f, 1.0f),L"DeleteA"),
   //ID2
   IDData(D3DXVECTOR4(0.4f, 0.8f,1,1),L"DeleteB"),
   //ID3
   IDData(D3DXVECTOR4(1,1,0,1),L"DeleteX"),
   //ID4
   IDData(D3DXVECTOR4(0,1,0,1),L"DeleteY")
};
