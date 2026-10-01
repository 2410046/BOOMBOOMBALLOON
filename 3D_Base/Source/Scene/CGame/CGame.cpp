#include "CGame.h"
#include "CGameObject/CSpriteObject/CTime/CTime.h"		//タイムクラス
#include "Scene/SelectText/CSelectText.h"               //選択肢の関数
#include "Collision/CollisionManager/CollisionManager.h"
#include "CMeshObject/CTracking/CTrackingManager/CTrackingManager.h"
#include "Reaction/ReactionManager.h"
// 定数定義
namespace 
{
	static const D3DXVECTOR3 Sky_Pos   
		= D3DXVECTOR3(0.f, -1.f, 11.f);		//スカイ座標
	static const D3DXVECTOR3 Camera_Pos 
		= D3DXVECTOR3(0.0f, 9.0f, -2.0f);	//カメラ座標
	static const D3DXVECTOR3 Look_Pos   
		= D3DXVECTOR3(0.0f, 2.0f, 10.0f);	//カメラの方向座標
	static const D3DXVECTOR3 Light_Pos  
		= D3DXVECTOR3(1.f, 2.f, 0.f);		//ライト座標

	//４つボタンの配置
	static const float TablePos[4][2] =
	{
		{  0.f,  20.f }, // 下
		{  20.f,  0.f }, // 右
		{  0.f, -20.f }, // 上
		{ -20.f,  0.f }, // 左
	};

	constexpr int ScoreTextCount = 2;	// スコアテキストの数
	constexpr int ButtonCount    = 4;	// ボタンの数
}
//コンストラクタ.
CGame::CGame()
	: CScene				()
	, m_PlayerCount			( 0 )
{
}
//デストラクタ.
CGame::~CGame()
{
	//破棄関数
	Release();
}

//構築関数
void CGame::Create()
{
	//プレイヤー人数の取得
	//m_PlayerCount = CGameData::GetInstance()->PlayerNo();
	m_PlayerCount = 4;
	// スカイのインスタンス生成
	m_pSky      = std::make_unique<CCharacter>();
	//雲のインスタンス生成
	m_pCloud	= std::make_unique<CCloud>();
}

//ロード関数.
HRESULT CGame::LoadData()
{
	//メッシュの読み込み
	m_pSky->AttachMesh(*AssetManager::GetStatic(L"Sky\\Sky1"));
	//座標の読み込み
	m_pSky->SetPosition(Sky_Pos);
	D3DXQUATERNION quaternion;

	D3DXQuaternionRotationYawPitchRoll(
		&quaternion,
		-D3DX_PI / 1.99f,  // 左90度
		0.0f,
		0.0f);
	m_pSky->SetQuaternion(quaternion);
	// プレイヤーの数
	for (int p = 0; p < m_PlayerCount; ++p)
	{
		//プレイヤーの生成
		m_pPlayer.NewPlayer(p);
		//スコアの生成
		m_pScores.NewScore(p);
	}
	m_pCloud->LoadData();
	//時間のリセット
	CTime::GetInstance()->Reset();
	// カメラの座標や角度の設定
	CCamera::GetInstance()->SetCamera(Camera_Pos, Look_Pos);
	//ライトの設定
	CCamera::GetInstance()->SetLight(Light_Pos);
	//音楽を再生
	CSoundManager::PlayLoop(CSoundManager::enList(CGameData::BGMNo()));
	return S_OK;
}
//解放関数.
void CGame::Release()
{
		//初期化
	CollisionManager::GetInstance()->Init();
	CReactionManager::GetInstance()->Init();
	CTrackingManager::GetInstance()->Init();
}
//動作関数
void CGame::Update()
{
	//CTime::GetInstance()->Update();
	CReactionManager::GetInstance()->Update();

	m_pPlayer.Update();

	m_Shot.Update(
		m_pPlayer.GetMoveStates(CPlayer::enMoveState::Shot));

	m_Balloon.Update(
		m_pPlayer.GetLifes());

	CollisionManager::GetInstance()->Update();

	m_pScores.Update(
		m_pPlayer.GetMoveStates(CPlayer::enMoveState::Hit),
		m_pPlayer.GetMoveStates(CPlayer::enMoveState::Down));
	//スカイの動作関数
	Sky();
    //シーン遷移
	Next();

}


//描画処理
void CGame::Draw()
{
	// カメラのインスタンスを取得
	auto* camera = CCamera::GetInstance();

	camera->Camera();		//カメラ関数
	camera->Projection();	//プロジェクション関数

	m_pSky->Draw(camera);

	m_pCloud->Draw(camera);

	m_pPlayer.Draw(camera);
	m_pScores.Draw();
	m_Shot.Draw(camera);
	m_Balloon.Draw(camera);

	//CTime::GetInstance()->Draw(camera);

	CEffect::GetInstance()->Draw(camera);

}

//スカイの動作
void CGame::Sky()
{
	//縦に動きながら、横にゆっくり回転
	constexpr float YSpeed = 0.0001f;
	constexpr float XSpeed = 0.01f;
	constexpr float MaxAngle = D3DX_PI / 2.0f;

	m_pSky->UpDown();
	m_pSky->Turn(XSpeed, MaxAngle);
}

//シーン遷移
void CGame::Next()
{
	//時間が来たら
	if (CTime::GetInstance()->MaxTime(CGameData::GetLimit())
		|| GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		//音楽を停止
		CSoundManager::Stop(CSoundManager::enList(CGameData::BGMNo()));
		//エフェクトをすべて止める
		CEffect::StopAll();
		//スコアをファイルに保存
		m_pScores.ResultScore();
		//リザルトに遷移
		SceneManager::GetInstance()->NextScene(SceneManager::Result);
	}
}