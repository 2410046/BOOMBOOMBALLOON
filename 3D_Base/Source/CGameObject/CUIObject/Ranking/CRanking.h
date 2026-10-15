#pragma once
#include "CGameObject/CUIObject/CUIObject.h"
#include "Singleton.h"
#include <vector>
#include <iostream>
#include <algorithm>  // これが必要
/********************************************************************************
*	ランキングクラス
**/
class CRanking
    : public CUIObject, public Singleton<CRanking>
{
public:
        //プレイヤーのスコアデータ
    struct enData
    {
        int ID = 0;                 //プレイヤーのID
        int MyScore = 0;            //プレイヤーのスコア
        int DisplayScore = 0;       //プレイヤーのスコア(表示用)
        bool CoundEnd    = false;   //カウント終了
        // デフォルトコンストラクタ
        enData() = default;
    };
private:
    friend class Singleton<CRanking>;
    CRanking();
public:
    //デストラクタ
    virtual ~CRanking() override;
   //スコアランキングに登録処理
    void Register(
        int ID,int score);
    //動作関数
    virtual void Update();
    //描画関数
    virtual void Draw() override;
    //リセット
    void Reset();
    //順位の取得
    int GetRank(int index) const;
    //カウント終了を取得
    bool GetCountEnd(int index) const;
    //ID取得
    int GetPlayerID(int index) const;
    // 座標交換
    void SwapPosition(int playerID, int targetID);
protected:
    void ConfirmRank(int playerID);
private:
    D3DXVECTOR3 m_PlayerPos[4];
    std::vector<enData> m_ScoreList;      //スコアリスト
    // 順位確定済みのプレイヤー数
    int m_ConfirmCount = 0;
};