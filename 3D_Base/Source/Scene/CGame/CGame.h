#pragma once
#include "CScene.h"				//シーンクラス
#include "CGameObject/CMeshObject/CPlayer/CPlayerManager.h"	    //プレイヤークラス
#include "CGameObject/CMeshObject/CTracking/CShot/CShotManager/CShotManager.h"	    //ショットクラス
#include "CGameObject/CMeshObject/CTracking/CBallun/CBallunManager/CBalloonManager.h"//バルーンクラス
#include "CGameObject/CMeshObject/CCloud/CCloud.h"                                  //雲クラス
#include "CGameObject/CUIObject/Score/CScoreManager.h"		//スコアマネージャークラス

/********************************************************************************
*	ゲームクラス.
**/
class CGame
	:public CScene
{
public:
	//コンストラクタ
	CGame();
	//デストラクタ
	~CGame() override;

	//構成関数
	void    Create()   override;
	//ロード関数
	HRESULT LoadData() override;
	//破棄関数
	void    Release()  override;
	//動作関数
	void    Update()   override;
	//描画関数
	void    Draw()     override;
private:
	//スカイの動作関数
	void Sky();		
	//シーン遷移関数
	void Next();
private:
	std::unique_ptr<CCloud>			           m_pCloud;	   //雲クラス
	std::unique_ptr<CStaticMeshObject>		   m_pSky;		   //スカイクラス
	
	CPlayerManager  m_pPlayer;	        //プレイヤー
	CScoreManager	m_pScores;	        //スコア
	CShotManager    m_Shot;		        //ショット
	CBalloonManager m_Balloon;          //バルーン
private:
	float m_RotY;					   // SkyのY座標
	int   m_PadButton[2] = { -1, -1 }; // コントローラーが押しているボタン(0:Pad0, 1:Pad1)
	int	  m_PlayerCount;			   // プレイヤーの人数
};
