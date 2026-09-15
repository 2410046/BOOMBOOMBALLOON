#include "CSelect.h"

// 定数定義
namespace
{
	static const D3DXVECTOR3 Back_Pos  
		= D3DXVECTOR3(-0.1f, 1.5f, 20.f);	//背景座標
	static const D3DXVECTOR3 Camera_Pos
		= D3DXVECTOR3(0.0f, 1.0f, -2.0f);	//カメラ座標
	static const D3DXVECTOR3 Look_Pos   
		= D3DXVECTOR3(0.0f, 1.0f, 10.0f);	//カメラの方向座標
	static const D3DXVECTOR3 Light_Pos  
		= D3DXVECTOR3( 1.f, 1.f, -1.f );	//ライト座標
	 //選択肢の数
	constexpr int SellCount = 2;
	//プレイヤーの最大人数
	constexpr int PlayerCount = 4;

}
//コンストラクタ.
CSelect::CSelect()
	: CScene			(  )
{
}
//デストラクタ.
CSelect::~CSelect()
{
	//破棄関数
	Release();
}
//構成関数
void CSelect::Create()
{
	////スプライトのインスタンス作成.
	m_pBack   = std::make_unique<CSpriteObject>();

	for (int i = 0; i < SellCount; ++i)//選択肢の数
	{
		//選択肢の生成
		auto sel = std::make_unique<CSelectUI>();
		m_pSelect.push_back(std::move(sel));
	}

	for (int i = 0; i < PlayerCount; ++i)//選択肢の数
	{
		//選択肢の生成
		auto active = std::make_unique<CUIObject>();
		m_pActive.push_back(std::move(active));

		//選択肢の生成
		auto player = std::make_unique<CPlayer>();
		m_pPlayer.push_back(std::move(player));
	}

}
//ロード関数
HRESULT CSelect::LoadData()
{
	//背景の画像の読み込み、座標の設定
	m_pBack->AttachSprite(
		*CSpriteManager::GetSprite3D(L"Select"));
	m_pBack->SetPosition(Back_Pos);

	//選択肢の画像の読み込み、パターン番号の設定、座標の設定
	for (int i = 0; i < m_pSelect.size(); ++i)
	{
		//選択肢の座標
		const D3DXVECTOR3 Sell_Pos
			= D3DXVECTOR3(600.f, 400.f + i * 100.f, 0.f);

		m_pSelect[i]->AttachSprite(
			*CSpriteManager::GetSprite2D(L"Text"));
		m_pSelect[i]->SetPatternNo(0, i);
		m_pSelect[i]->SetPosition(Sell_Pos);
	}

	for (int i = 0; i < m_pActive.size(); ++i)
	{
		//プレイヤー表記の座標
		const D3DXVECTOR3 Active_Pos
			= D3DXVECTOR3(100.f + i * 300.f, 100.f, 0.f);
		//プレイヤーの座標
		const D3DXVECTOR3 Player_Pos
			= D3DXVECTOR3(-5.f + (i * 3.1f), 1.f, 7.f);

		m_pActive[i]->AttachSprite(
			*CSpriteManager::GetSprite2D(L"ActiveUser"));
		m_pActive[i]->SetPatternNo(0, 0);
		m_pActive[i]->SetPosition(Active_Pos);

		m_pPlayer[i]->AttachMesh(
			*CMeshManager::GetStatic(L"Player\\Player01"));
		m_pPlayer[i]->SetPosition(Player_Pos);
		m_pPlayer[i]->SetScale(0.01f, 0.01f, 0.01f);
		m_pPlayer[i]->SetID(i);

	}

	// カメラの座標や角度の設定
	CCamera::GetInstance()->SetCamera(Camera_Pos, Look_Pos);
	//ライトの設定
	CCamera::GetInstance()->SetLight(Light_Pos);

	return S_OK;
}
//破棄関数
void CSelect::Release()
{
}
//動作関数
void CSelect::Update()
{
	//BGMをループ再生する
	CSoundManager::PlayLoop(CSoundManager::enList::Select);

	//選択肢の設定
	Selecter(m_Select, (int)m_pSelect.size(), m_Start);


	//--------------------
	// シーン遷移
	//--------------------

	//選択中の場合
	if (m_Start == false)
	{
		// 選択中のインデックスに応じてスプライトの表示状態（透明度）を更新		
		for (int i = 0; i < m_pSelect.size(); ++i)
		{
			//選択されたときの状態
			m_pSelect[i]->SellState(
				i, m_Select, [](int i) { return i; });
		}
		//プレイヤーの人数選択
		PlayerActive();
	}
	else	//決定
	{
		//フェードを進行
		if (CFade::GetInstance()->FadeOut())
		{
			//音楽を停止
			CSoundManager::Stop(CSoundManager::enList::Select);

			// 選択内容に応じて遷移先を分岐
			switch (m_Select)
			{
			case 0:
				//タイトルシーンに遷移
				SceneManager::GetInstance()->NextScene(SceneManager::Title);
				break;
			case 1:
				//ゲームシーンに遷移
				SceneManager::GetInstance()->NextScene(SceneManager::Game);
				break;
			}
			//選択可能
			m_Start = false;
		}
	}


}
//描画関数
void CSelect::Draw()
{
	// カメラのインスタンスを取得
	auto* camera = CCamera::GetInstance();

	camera->Camera();		//カメラ関数
	camera->Projection();	//プロジェクション関数

	CDirectX11::GetInstance()->SetDepth(false);

	//m_pBack->Draw(camera);

	//選択肢の描画
	for (size_t i = 0; i < m_pSelect.size(); ++i)
	{
		m_pSelect[i]->Draw();
	}

	for (size_t i = 0; i < m_pActive.size(); ++i)
	{
		m_pActive[i]->Draw();
		m_pPlayer[i]->Draw(camera);
	}

	//フェードの描画
	CFade::GetInstance()->Draw(camera);

	CDirectX11::GetInstance()->SetDepth(true);

}

 //プレイヤーの人数選択
void CSelect::PlayerActive()
{
	// 最大プレイヤー数
	static constexpr int Max_Player = 4;

	// 操作対象となるプレイヤー番号
	// 0番コントローラーを使用
	static constexpr int Player_Index = 0;

	// XInputのシングルトンからゲームパッドを取得
	CXInput* pPad = CXInput::GetInstance(Player_Index);

	// 現在接続されているコントローラーの数
	int m_PadCount = 0;

	// 各プレイヤーのコントローラー接続状態を確認
	for (int i = 0; i < Max_Player; i++)
	{
		// コントローラーが接続されている場合
		if (pPad->IsControllerConnected(i))
		{
			// 接続されているコントローラー数を加算
			m_PadCount++;
		}
	}

	// プレイヤーの表示状態を更新
	for (int i = 0; i < m_pActive.size(); ++i)
	{
		// 接続されているコントローラー数と
		// プレイヤー番号が一致した場合
		if (i < m_PadCount)
		{
			// 該当するプレイヤーの表示パターンを変更
			// i + 1 はプレイヤー番号（P1～P4）
			m_pActive[i]->SetPatternNo(0, i + 1);
			//プレイヤーを動かす
			m_pPlayer[i]->UpDown();
		}
		else
		{
			// 接続されていないプレイヤーをCOM
			m_pActive[i]->SetPatternNo(0, 0);
		}
	}

	// 接続されているコントローラー数を
	// プレイする人数としてゲームデータに設定
	CGameData::GetInstance()->SetPlayNo(m_PadCount);
}
