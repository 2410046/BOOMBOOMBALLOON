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
}
//ロード関数
HRESULT CSelect::LoadData()
{

	//背景の画像の読み込み、座標の設定
	m_pBack->AttachSprite(
		*CSpriteManager::GetSprite3D("SelectBack"));
	m_pBack->SetPosition(Back_Pos);

	//選択肢の画像の読み込み、パターン番号の設定、座標の設定
	for (int i = 0; i < m_pSelect.size(); ++i)
	{
		//選択肢の座標
		const D3DXVECTOR3 Sell_Pos
			= D3DXVECTOR3(600.f, 400.f + i * 100.f, 0.f);

		m_pSelect[i]->AttachSprite(
			*CSpriteManager::GetSprite2D("SelectText"));
		m_pSelect[i]->SetPatternNo(0, i);
		m_pSelect[i]->SetPosition(Sell_Pos);
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
		//PlayerSelect();
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

	m_pBack->Draw(camera);

	//選択肢の描画
	for (size_t i = 0; i < m_pSelect.size(); ++i)
	{
		m_pSelect[i]->Draw();
	}

	//フェードの描画
	CFade::GetInstance()->Draw(camera);

	CDirectX11::GetInstance()->SetDepth(true);

}

 //プレイヤーの人数選択
void CSelect::PlayerSelect()
{
	// 最大プレイヤー数
	static constexpr int Max_Player = 2;  
	// 操作対象となるプレイヤー番号（0番コントローラ）
	static constexpr int Player_Index = 0;
	// XInputのシングルトンからプレイヤーのゲームパッドを取得
	CXInput* pPad = CXInput::GetInstance(Player_Index);

	//接続したコントローラーの数
	int m_PadCount = 0;

	// コントローラーの接続をチェック
	for (int i = 0; i < Max_Player; i++) 
	{
		if (pPad->IsControllerConnected(i))
		{
			m_PadCount++;
		}
	}
	 //プレイヤー人数を決定
	CGameData::GetInstance()->SetPlayNo(m_PadCount);
}
