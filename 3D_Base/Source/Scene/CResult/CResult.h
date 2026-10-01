#pragma once
#include"CScene.h"  
#include"CGameObject/CUIObject/SelectUI/CSelectUI.h"
#include"Scene/SelectText/CSelectText.h"  //選択肢の関数
#include"CGameObject/CMeshObject/CStaticMeshObject.h"
#include"CGameObject/CMeshObject/CPlayer/CPlayer.h"
/********************************************************************************
*	リザルトクラス.
**/
class CResult
	:public CScene
{
public:
    //コンストラクタ
	CResult();
    //デストラクタ
	~CResult() override;
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
    std::vector<std::unique_ptr<CSelectUI>> m_pSelect;		//選択肢テキストクラス
    std::vector<std::unique_ptr<CUIObject>> m_pScoreText;	//スコアテキストクラス
    std::unique_ptr<CStaticMeshObject>		m_pSky;		   //スカイクラス

    std::vector<std::unique_ptr<CPlayer>> m_pPlayer;  //プレイヤーリアクションクラス
    int m_PlayerCount;
};
