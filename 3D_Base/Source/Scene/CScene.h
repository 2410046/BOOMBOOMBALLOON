#pragma once
#include <Windows.h>
#include "Scene/SceneManager/SceneManager.h"       //シーンマネージャークラス
#include "Asset/AssetManager/AssetManager.h"       //サウンドマネージャークラス
#include "Asset/CXInput/CXInput.h"	               //コントローラークラス
#include "Camera/CCamera.h"                        //カメラクラス
#include "CGameObject/CUIObject/CUIObject.h"       //UIオブジェクトクラス
#include "CGameObject/CSpriteObject/CFade/CFade.h" //フェードクラス
#include "Scene/CGameData.h"                       //データクラス
#include "CGameObject/CUIObject/SelectUI/CSelectUI.h"
#include "DirectX/CDirectX11.h"
#include <memory>
#include <vector>

/********************************************************************************
*	シーンクラス
**/
class CScene 
{
public:
    //コンストラクタ
    CScene();
    //デストラクタ
    virtual ~CScene() = default;

    //構成関数
    virtual void Create()      = 0;
    //ロード関数
    virtual HRESULT LoadData() = 0;
    //破棄関数
    virtual void Release()     = 0;
    //動作関数
    virtual void Update()      = 0;
    //描画関数
    virtual void Draw()        = 0;  
protected:
    int         m_Select;       //選択No
    bool        m_Start;        //選択決定
};

