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
// サウンドデータの読み込み
bool CSoundManager::Load(HWND hWnd)
{
	// 読み込むサウンドファイル
	const TCHAR* path[] =
	{
		{ _T("BGM\\Title")       },
		{ _T("BGM\\MouningGame") },
		{ _T("BGM\\NightGame")   },
		{ _T("BGM\\Select")      },
		{ _T("BGM\\空と虹")      },

		{ _T("SE\\Ballon")       },
		{ _T("SE\\BaseHit")      },
		{ _T("SE\\Boost")        },
		{ _T("SE\\Dead")         },
		{ _T("SE\\Down")         },
		{ _T("SE\\Enter")        },
		{ _T("SE\\PlayerHit")    },
		{ _T("SE\\Select")       },
		{ _T("SE\\Shot")         },
	};
	// 配列の要素数を取得
	int list_max = sizeof(path) / sizeof(path[0]);
	// サウンドを順番に読み込む
	for (int i = 0; i < list_max; i++)
	{
		// ファイル名を取得
		const TCHAR* fileName = path[i];
		// 管理用のサウンドを取得
		auto& pSound = m_pSound[fileName];
		// サウンドが未生成の場合は生成
		if (!pSound)
		{
			pSound = std::make_unique<CSound>();
		}
		// サウンドファイルを読み込み
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
	// 登録されているサウンドを解放
	for (auto& sound : m_pSound)
	{
		//音声ファイルを閉じる
		sound.second->Close();
	}

	m_pSound.clear();
}

