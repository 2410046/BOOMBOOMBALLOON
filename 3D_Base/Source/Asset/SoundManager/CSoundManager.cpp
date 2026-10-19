#include "CSoundManager.h"
#include "MyMacro.h"

CSoundManager::CSoundManager()
	: m_pSound	()
{
	//インスタンス生成.
	for( int i = 0; i < enList::max; i++ )
	{
		m_pSound[i] = new CSound();
	}
}

CSoundManager::~CSoundManager()
{
	Release();

	//インスタンス破棄.
	for( int i = enList::max - 1; i >= 0; i-- )
	{
		SAFE_DELETE( m_pSound[i] );
	}
}

//サウンドデータ読込関数.
bool CSoundManager::Load( HWND hWnd )
{
	struct SoundList
	{
		int listNo;				//enList列挙型を設定.
		const TCHAR path[256];	//ファイルの名前(パス付き).
		const TCHAR alias[32];	//エイリアス名.
	};
	SoundList SList[] =
	{
		{ enList::Title ,		_T("BGM\\Title.mp3"),      _T("Title")	},
		{ enList::Mouning,		_T("BGM\\MouningGame.mp3"),_T("Mouning")},
		{ enList::Night,		_T("BGM\\NightGame.mp3"),_T("Night")},
		{ enList::Select,		_T("BGM\\Select.mp3"),     _T("Select")	},
		{ enList::Result,		_T("BGM\\空と虹.mp3"),     _T("Result")	},
	};
	//配列の最大要素数を算出 (配列全体のサイズ/配列1つ分のサイズ).
	int list_max = sizeof( SList ) / sizeof( SList[0] );
	for( int i = 0; i < list_max; i++ )
	{
		if( m_pSound[SList[i].listNo]->Open(
			SList[i].path,
			SList[i].alias,
			hWnd ) == false )
		{
			return false;
		}
	}

	return true;
}

//サウンドデータ解放関数.
void CSoundManager::Release()
{
	//開いた時と逆順で閉じる.
	for( int i = enList::max - 1; i >= 0; i-- )
	{
		if( m_pSound[i] != nullptr )
		{
			m_pSound[i]->Close();
		}
	}
}

//#include "CSoundManager.h"
//#include "MyMacro.h"
//
//CSoundManager::CSoundManager()
//	: m_pSound()
//{
//}
//
//CSoundManager::~CSoundManager()
//{
//	Release();
//}
//// サウンド読み込み
//bool CSoundManager::Load(HWND hWnd)
//{
//	// サウンドのパス
//	const TCHAR* path[]
//	{
//		_T("BGM\\Title.mp3"),
//		_T("BGM\\MouningGame.mp3"),
//		_T("BGM\\NightGame.mp3"),
//		_T("BGM\\Select.mp3"),
//		_T("BGM\\空と虹.mp3"),
//	};
//
//	const int list_max = sizeof(path) / sizeof(path[0]);
//
//	for (int i = 0; i < list_max; i++)
//	{
//		std::wstring key = path[i];
//
//		// 二重読み込み防止
//		if (m_pSound.find(key) != m_pSound.end())
//		{
//			continue;
//		}
//
//		auto* pSound = new CSound();
//
//		if (!pSound->Open(
//			path[i],
//			hWnd))
//		{
//			delete pSound;
//			return false;
//		}
//
//		m_pSound[key] = pSound;
//	}
//
//	return true;
//}
//
//// サウンド取得
//CSound* CSoundManager::GetSound(LPCTSTR alias)
//{
//	if (alias == nullptr)
//	{
//		return nullptr;
//	}
//
//	auto it = m_pSound.find(alias);
//
//	if (it == m_pSound.end())
//	{
//		return nullptr;
//	}
//
//	return it->second;
//}
//
//
//// 解放
//void CSoundManager::Release()
//{
//	for (auto& sound : m_pSound)
//	{
//		sound.second->Close();
//		SAFE_DELETE(sound.second);
//	}
//
//	m_pSound.clear();
//}