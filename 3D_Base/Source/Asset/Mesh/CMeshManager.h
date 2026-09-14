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
    // スタティックメッシュ取得
    static CStaticMesh* GetStatic(const std::wstring& name);
    // スキンメッシュ取得
    static CSkinMesh* GetSkin(const std::wstring& name);
    // 解放
    void Release();
protected://内部処理用
   // スタティックメッシュをマップから取得
    // GetStatic()経由で使用する
    CStaticMesh* GetStatic_Internal(const std::wstring& name);
    // スキンメッシュをマップから取得
     // GetSkin()経由で使用する
    CSkinMesh* GetSkin_Internal(const std::wstring& name);
private:
    // メッシュ本体
    std::map<std::wstring, std::unique_ptr<CSkinMesh>>   m_SkinMapList;
    std::map<std::wstring, std::unique_ptr<CStaticMesh>> m_StaticMapList;

};
