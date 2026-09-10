#pragma once
#include <vector>
#include <memory>
#include "CGameObject/CMeshObject/CPlayer/CPlayer.h"//プレイヤークラス
#include "CGameObject/CMeshObject/CTracking/CTracking.h"//追尾クラス
/********************************************************************************
* プレイヤーマネージャークラス
**/
class CPlayerManager
{
public:
    //コンストラクタ
    CPlayerManager();
    //デストラクタ
    ~CPlayerManager() = default;

    // IDを指定してプレイヤーの生成
    void NewPlayer(int ID);
    // 動作関数
    void Update();
    //描画関数
    void Draw(const CCamera* pCamera);
    // 全プレイヤー取得
    std::vector<CPlayer*> GetPlayers()const;
    //プレイヤーの取得
    CPlayer* GetPlayer(int index);

    // 全プレイヤーのShotフラグ取得
    std::vector<bool> GetShotFlags() const;
    //全プレイヤーのライフ取得
    std::vector<int> GetLifes() const;
    // Shotフラグ取得
    bool GetShotFlag(int ID) const;
private:
    std::vector<std::unique_ptr<CPlayer>> m_Players;     //プレイヤー
    //std::vector<std::unique_ptr<CTracking>> m_Tracking;  //追尾
};
