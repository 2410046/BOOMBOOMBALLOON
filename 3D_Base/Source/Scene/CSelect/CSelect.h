#pragma once
#include "CScene.h"
#include"CGameObject/CUIObject/SelectUI/CSelectUI.h"
#include"Scene/SelectText/CSelectText.h"  //選択肢の関数
#include"CGameObject/CMeshObject/CCharacter.h"
#include"CGameObject/CMeshObject/CPlayer/CPlayer.h"
/********************************************************************************
*	セレクトクラス.
**/
class CSelect
    : public CScene
{
public:
    //コンストラクタ
    CSelect();
    //デストラクタ
    ~CSelect() override;

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

protected:
    //プレイヤーの人数関数
    void PlayerActive();
private:
    std::unique_ptr<CStaticMeshObject>		m_pSky;		   //スカイクラス

    std::vector<std::unique_ptr<CSelectUI>> m_pSelect;  //選択肢テキストクラス
    std::vector<std::unique_ptr<CUIObject>> m_pActive;  //アクティブプレイヤークラス
    std::vector<std::unique_ptr<CPlayer>> m_pPlayer;  //プレイヤーリアクションクラス
};
