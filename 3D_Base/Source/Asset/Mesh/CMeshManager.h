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
    // 全解放
    void Release();
    //全てのメッシュを生成
    HRESULT Create();
    //全てのメッシュを読み込む
    HRESULT LoadData();
    //スタティックメッシュの情報を取得
    static CStaticMesh* GetStatic(std::string name);
    //スキンメッシュの情報を取得
    static CSkinMesh* GetSkin(std::string name);

protected://内部処理用
    //スタティックメッシュ生成
    HRESULT CreateStatic();
    //スキンメッシュ生成
    HRESULT CreateSkin();
    //スタティックメッシュの読み込み
    HRESULT LoadStatic();
    //スキンメッシュの読み込み
    HRESULT LoadSkin();
   // スタティックメッシュをマップから取得
    // GetStatic()経由で使用する
    CStaticMesh* GetStatic_Internal(std::string name);
    // スキンメッシュをマップから取得
     // GetSkin()経由で使用する
    CSkinMesh* GetSkin_Internal(std::string name);
protected:
    //スタティックメッシュの管理データ
    struct StaticData
    {
        std::string Name;                //管理用の名前
        std::wstring File;              //メッシュファイル
    };
    //スキンメッシュの管理データ
    struct SkinData
    {
        std::string Name;                  //管理用の名前
        std::wstring File;              //メッシュファイル
    };
    //スタティックメッシュデータに登録
    void RegisterStatic(const StaticData& data);
    //スキンメッシュデータに登録
    void RegisterSkin(const SkinData& data);
private:
    // メッシュ本体
    std::map<std::string, std::unique_ptr<CSkinMesh>>   m_SkinMapList;
    std::map<std::string, std::unique_ptr<CStaticMesh>> m_StaticMapList;
    // メッシュ読み込み用データ
    std::vector<StaticData> m_StaticData;
    std::vector<SkinData> m_SkinData;

};
