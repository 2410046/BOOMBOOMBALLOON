#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "Asset/Mesh/SkinMesh/CSkinMesh.h"
#include "Asset/Mesh/StaticMesh/CStaticMesh.h"
#include "Singleton.h"

/********************************************************************************
*   メッシュマネージャークラス
*   スキンメッシュ / スタティックメッシュを生成・取得・解放と管理するクラス   
**/
class CMeshManager
    : public Singleton<CMeshManager>
{
private:
    friend class Singleton<CMeshManager>;
    CMeshManager();
public:
    ~CMeshManager();
    // 解放
    void Release();
   // スタティックメッシュをマップから取得
    CStaticMesh* GetStatic(const std::wstring& name);
    // スキンメッシュをマップから取得
    CSkinMesh* GetSkin(const std::wstring& name);
private:
    // メッシュ本体
    std::map<std::wstring, std::unique_ptr<CSkinMesh>>   m_SkinMapList;
    std::map<std::wstring, std::unique_ptr<CStaticMesh>> m_StaticMapList;

};
