#pragma once
#include <map>
#include <memory>
#include <string>

#include "Asset/Sprite/Sprite2D/CSprite2D.h"
#include "Asset/Sprite/Sprite3D/CSprite3D.h"
#include <vector>
#include "Singleton.h"
/********************************************************************************
*   スプライトマネージャークラス
*   スプライト2D / スプライト3Dを生成・取得・解放と管理するクラス
**/
class CSpriteManager
    :public Singleton<CSpriteManager>
{
private:
    friend class Singleton<CSpriteManager>;
    CSpriteManager();
public:
    ~CSpriteManager();
    // 解放
    void Release();
    //全てのスプライトを生成
    HRESULT Create();
    //全てのスプライトを読み込む
    HRESULT LoadData();
    //スプライト2Dの情報を取得
    static CSprite2D* GetSprite2D(std::string name);
    //スプライト3Dの情報を取得
    static CSprite3D* GetSprite3D(std::string name);
protected://内部処理用
    // スプライト2D生成
    HRESULT CreateSprite2D();
    // スプライト3D生成
    HRESULT CreateSprite3D();
    //スプライト2Dの読み込み
    HRESULT LoadSprite2D();
    //スプライト3Dの読み込み
    HRESULT LoadSprite3D();
    // スプライト2Dをマップから取得
    // ※外部からは直接呼ばず、GetSprite2D()経由で使用する
    CSprite2D* Sprite2D_Internal(std::string name);
    // スプライト3Dをマップから取得
    // ※外部からは直接呼ばず、GetSprite3D()経由で使用する
    CSprite3D* Sprite3D_Internal(std::string name);
protected:
    //スプライト2Dの管理データ
    struct Sprite2DData
    {
        std::string Name;                //管理用の名前
        std::wstring File;              //画像ファイル
        CSprite2D::SPRITE_STATE State;  //スプライト構造体
    };
    //スプライト3Dの管理データ
    struct Sprite3DData
    {
        std::string Name;                //管理用の名前
        std::wstring File;              //画像ファイル
        CSprite3D::SPRITE_STATE State;  //スプライト構造体
    };
    //スプライト2Dデータに登録
    void RegisterSprite2D(const Sprite2DData& data);
    //スプライト3Dデータに登録
    void RegisterSprite3D(const Sprite3DData& data);
private:
    // スプライト本体
    std::map<std::string, std::unique_ptr<CSprite3D>> m_3DMapList;
    std::map<std::string, std::unique_ptr<CSprite2D>> m_2DMapList;
    // スプライト読み込み用データ（ファイル,構造体など）
    std::vector<Sprite2DData> m_2DData;
    std::vector<Sprite3DData> m_3DData;
};