#pragma once
#include "Singleton.h"
#include <string>

#include "Asset/SoundManager/CSoundManager.h"
#include "Asset/Effect/CEffect.h"
#include "Asset/Sprite/CSpriteManager.h"
#include "Asset/Mesh/CMeshManager.h"
/********************************************************************************
*   アセットマネージャークラス
*   アセットの読み込み・管理を行うクラス
**/
class CAssetManager
    : public Singleton<CAssetManager>
{
private:
    friend class Singleton<CAssetManager>;
    CAssetManager();
public:
    ~CAssetManager();

    //構築関数
    static HRESULT Create();
    //ロード関数
    static HRESULT LoadData(HWND hWnd);
    //スタティックメッシュの情報を取得
    static CStaticMesh* GetStatic(std::wstring name);
    //スキンメッシュの情報を取得
    static CSkinMesh* GetSkin(std::wstring name);
    //スプライト2Dの情報を取得
    static CSprite2D* GetSprite2D(std::wstring name);
    //スプライト3Dの情報を取得
    static CSprite3D* GetSprite3D(std::wstring name);
    
private:
    HWND                        m_hWnd;
};