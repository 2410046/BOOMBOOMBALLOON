#pragma once
#include "Singleton.h"
#include <string>

#include "Asset/SoundManager/CSoundManager.h"
#include "Asset/Effect/CEffect.h"
#include "Asset/Sprite/CSpriteManager.h"
#include "Asset/Mesh/CMeshManager.h"
/********************************************************************************
*   アセットマネージャークラス
*
**/
class AssetManager
    : public Singleton<AssetManager>
{
private:
    friend class Singleton<AssetManager>;
    AssetManager();
public:
    ~AssetManager();

    //構築関数
    static HRESULT Create(HWND hWnd);
    //ロード関数
    static HRESULT LoadData();
    //スタティックメッシュの情報を取得
    static CStaticMesh* GetStatic(std::string name);

    //スキンメッシュの情報を取得
    static CSkinMesh* GetSkin(std::string name);

    //スプライト2Dの情報を取得
    static CSprite2D* GetSprite2D(std::string name);

    //スプライト3Dの情報を取得
    static CSprite3D* GetSprite3D(std::string name);
    
private:
    HWND                        m_hWnd;
};