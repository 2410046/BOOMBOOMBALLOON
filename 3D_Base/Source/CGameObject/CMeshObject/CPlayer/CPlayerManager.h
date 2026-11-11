#pragma once
#include <vector>
#include <memory>
#include "CGameObject/CMeshObject/CPlayer/CPlayer.h"//プレイヤークラス
#include "CGameObject/CMeshObject/CPlayer/CCOM/CCOM.h"//コンピュータークラス
#include "CGameObject/CMeshObject/CTracking/CTracking.h"//追尾クラス
#include "CGameObject/CUIObject/CAttackIcon/CAttackIcon.h"	//攻撃アイコン
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
    void NewPlayer();
    // 動作関数
    void Update();
    //描画関数
    void Draw(const CCamera* pCamera);
    // 全プレイヤー取得
    std::vector<CPlayer*> GetPlayers()const;
    //プレイヤーの取得
    CPlayer* GetPlayer(int index);

    // 全プレイヤーのShotフラグ取得
    std::vector<bool> GetShots() const;
    //全プレイヤーのライフ取得
    std::vector<int> GetLifes() const;
    //全プレイヤーのポイント取得
    std::vector<int> GetPoints() const;
    //全プレイヤーのクールタイムフラグを取得
    std::vector<std::unordered_map<std::string, bool>> GetCoolFlag() const;
private:
    std::vector<std::unique_ptr<CPlayer>> m_Players;     //プレイヤー
    std::vector<std::unique_ptr<CCom>> m_Coms;
};
