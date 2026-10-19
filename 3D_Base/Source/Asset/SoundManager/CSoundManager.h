#pragma once
#include "CSound.h"		//サウンドクラス.
#include "Singleton.h"
#include <string>
#include <unordered_map>
#include <memory>
/**************************************************
*	サウンドマネージャークラス.
*	Manager(マネージャー)：管理者.
*		Singleton(シングルトン：デザインパターンの１つ)で作成.
**/
class CSoundManager
	:public Singleton<CSoundManager>
{
private:
	friend class Singleton<CSoundManager>;
	CSoundManager();
public:
	~CSoundManager();

	//サウンドデータ読込関数.
	bool Load(HWND hWnd);
	//サウンドデータ解放関数.
	void Release();

	//SEを再生する.
	static void PlaySE(const std::basic_string<TCHAR>& alias) {
		GetInstance()->m_pSound.at(alias)->PlaySE();
	}
	//ループ再生する.
	static void PlayLoop(const std::basic_string<TCHAR>& alias) {
		GetInstance()->m_pSound.at(alias)->PlayLoop();
	}
	//停止する.
	static void Stop(const std::basic_string<TCHAR>&  alias) {
		GetInstance()->m_pSound.at(alias)->Stop();
	}
	static void SetVolume(const std::basic_string<TCHAR>& alias, LONG volume)
	{
		GetInstance()->m_pSound.at(alias)->SetVolume(volume);
	}
private:
	//std::unordered_map<std::string, std::unique_ptr<CSound>> m_pSound;
	std::unordered_map
		<std::basic_string<TCHAR>,std::unique_ptr<CSound>> m_pSound;
};