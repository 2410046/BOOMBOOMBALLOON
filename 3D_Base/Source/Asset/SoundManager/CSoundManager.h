#pragma once
#include "CSound.h"		//サウンドクラス.
#include "Singleton.h"
/**************************************************
*	サウンドマネージャークラス.
*	Manager(マネージャー)：管理者.
*		Singleton(シングルトン：デザインパターンの１つ)で作成.
**/
class CSoundManager
	:public Singleton<CSoundManager>
{
public:
	//サウンドリスト列挙型.
	enum enList
	{
		//BGM
		Title,
		Mouning,
		Night,
		Select,
		Result,
		//音が増えたら「ここ」に追加してください.
		max,		//最大数.
	};

private:
	friend class Singleton<CSoundManager>;
	CSoundManager();
public:
	~CSoundManager();

	//サウンドデータ読込関数.
	bool Load( HWND hWnd );
	//サウンドデータ解放関数.
	void Release();

	//SEを再生する.
	static void PlaySE( enList list ) {
		CSoundManager::GetInstance()->m_pSound[list]->PlaySE();
	}

	//ループ再生する.
	static void PlayLoop( enList list ) {
		CSoundManager::GetInstance()->m_pSound[list]->PlayLoop();
	}
	//停止する.
	static void Stop( enList list ) {
		CSoundManager::GetInstance()->m_pSound[list]->Stop();
	}
	static void PlayFrom(enList list, DWORD startMs, bool bNotify = false) {
		CSoundManager::GetInstance()->m_pSound[list]->PlayFrom(startMs, bNotify);
	}

	static void SetVolume(enList list, LONG volume)
	{
		CSoundManager::GetInstance()->m_pSound[list]->SetVolume(volume);
	}
private:
	CSound*		m_pSound[enList::max];
};

//#pragma once
//#include "CSound.h"		//サウンドクラス.
//#include "Singleton.h"
//#include <string>
//#include <unordered_map>
///**************************************************
//*	サウンドマネージャークラス.
//*	Manager(マネージャー)：管理者.
//*		Singleton(シングルトン：デザインパターンの１つ)で作成.
//**/
//class CSoundManager
//	:public Singleton<CSoundManager>
//{
//private:
//	friend class Singleton<CSoundManager>;
//	CSoundManager();
//public:
//	~CSoundManager();
//
//	//サウンドデータ読込関数.
//	bool Load(HWND hWnd);
//	//サウンドデータ解放関数.
//	void Release();
//
//	//SEを再生する.
//	static void PlaySE(const std::wstring& alias) {
//		GetInstance()->m_pSound[alias]->PlaySE();
//	}
//	//ループ再生する.
//	static void PlayLoop(const std::wstring& alias) {
//		GetInstance()->m_pSound[alias]->PlayLoop();
//	}
//	//停止する.
//	static void Stop(const std::wstring& alias) {
//		GetInstance()->m_pSound[alias]->Stop();
//	}
//	static void SetVolume(const std::wstring& alias, LONG volume)
//	{
//		GetInstance()->m_pSound[alias]->SetVolume(volume);
//	}
//
//private:
//	// サウンド取得
//	CSound* GetSound(LPCTSTR path);
//private:
//	std::unordered_map<std::wstring, CSound*> m_pSound;
//};