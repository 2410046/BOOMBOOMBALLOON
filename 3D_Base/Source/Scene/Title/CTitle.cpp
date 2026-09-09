#include "CTitle.h"   //タイトルクラス
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
	constexpr int SellCount = 2;            //選択肢の数
}
//コンストラクタ.
CTitle::CTitle()
	: CScene()
{
}
//デストラクタ
CTitle::~CTitle()
{
	//破棄関数
	Release();
}

//構成関数
void CTitle::Create()
{
	//背景の生成
	m_pBack = std::make_unique<CSpriteObject>();
	for (int i = 0; i < SellCount; ++i)//選択肢の数
	{
		//選択肢の生成
		auto sel = std::make_unique<CSelectUI>();
		m_pSelect.push_back(std::move(sel));
	}

}

//ロード関数
HRESULT CTitle::LoadData()
{
	//背景の画像の読み込み、座標の設定
	m_pBack->AttachSprite(
		*CSpriteManager::GetSprite3D("TitleBack"));
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
void CTitle::Release()
{
}

//動作関数
void CTitle::Update()
{
	//BGMをループ再生する
	CSoundManager::PlayLoop(CSoundManager::enList::Title);
	//選択肢の設定
	Selecter(m_Select, (int)m_pSelect.size(), m_Start);

	//--------------------
	// シーン遷移
	//--------------------
	//選択中
	if (m_Start == false)
	{
		// 選択中のインデックスに応じてスプライトの表示状態（透明度）を更新		
		for (int i = 0; i < m_pSelect.size(); ++i)
		{
			//選択されたときの状態
			m_pSelect[i]->SellState(
				i, m_Select,[](int i) { return i; });
		}
	}
	else  //決定
	{
		//フェードが終わったら
		if (CFade::GetInstance()->FadeOut())
		{
			//音楽を停止
			CSoundManager::Stop(CSoundManager::enList(3));

			// 選択内容に応じて遷移先を分岐
			switch (m_Select)
			{
			case 0:
				//セレクトシーンに遷移
				SceneManager::GetInstance()->NextScene(SceneManager::Select);
				break;
			case 1:
				//ゲーム終了
				PostQuitMessage(0);
				break;
			}
			//選択可能
			m_Start = false;
		}
	}

}

//描画関数
void CTitle::Draw()
{
	// カメラのインスタンスを取得
	auto* camera = CCamera::GetInstance();

	camera->Camera();		//カメラ関数
	camera->Projection();	//プロジェクション関数

	CDirectX11::GetInstance()->SetDepth(false);
	//背景の描画
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