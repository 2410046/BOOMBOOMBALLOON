#include "CSoundManager.h"
#include "MyMacro.h"
CSoundManager::CSoundManager()
    : m_pSound()
{
}

CSoundManager::~CSoundManager()
{
    Release();
}
// サウンド読み込み
bool CSoundManager::Load(HWND hWnd)
{
	const TCHAR* path[] =
	{
		{ _T("BGM\\Title")       },
		{ _T("BGM\\MouningGame") },
		{ _T("BGM\\NightGame")   },
		{ _T("BGM\\Select")      },
		{ _T("BGM\\空と虹")      },
	};

	int list_max = sizeof(path) / sizeof(path[0]);

	for (int i = 0; i < list_max; i++)
	{
		const TCHAR* fileName = path[i];

		auto& pSound = m_pSound[fileName];

		if (!pSound)
		{
			pSound = std::make_unique<CSound>();
		}

		if (!pSound->Open(path[i], hWnd))
		{
			return false;
		}
	}

    return true;
}

//サウンドデータ解放関数.
void CSoundManager::Release()
{
	for (auto& sound : m_pSound)
	{
		sound.second->Close();
	}

	m_pSound.clear();
}

