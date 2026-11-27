#pragma once

//警告についてのコード分析を無効にする.4005:再定義.
#pragma warning(disable:4005)
#include "Singleton.h"
//DirectX9.
#include <d3dx9.h>

//ライブラリ読み込み.
#pragma comment( lib, "winmm.lib" )
//DirectX9.
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

//#pragma comment( lib, "audio.lib" )

/**************************************************
*	DirectX9 セットアップ.
**/
class CDirectX9
	:public Singleton<CDirectX9>
{
private:
	//シングルトン
	friend class Singleton<CDirectX9>;
	CDirectX9();
public:
	~CDirectX9();
	//DirectX9構築.
	HRESULT Create( HWND hWnd );
	//DirectX9解放.
	void Release();
	//デバイスオブジェクトを取得.
	static LPDIRECT3DDEVICE9 GetDevice() { return GetInstance()->m_pDevice9; }
private:
	LPDIRECT3DDEVICE9	m_pDevice9;	//デバイスオブジェクト.
};