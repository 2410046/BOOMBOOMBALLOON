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
        int MyCombo = 0;            //プレイヤーの最大コンボ
        int MyMiss = 0;             //プレイヤーのミス
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
        int ID,int score,int combo,int miss);
    //動作関数
    virtual void Update();
    //描画関数
    virtual void Draw() override;
    //リセット
    void Reset();
protected:
    //ランキングを読みこむ
    void ReadRank();
    //ランキングを保存する
    void SaveRank();
    //ランキングを動かす
    void RankingMove();

    size_t GetList()const { return m_ScoreList.size(); }

private:
    std::vector<int>    m_MyScore;        //スコア配列
    size_t              m_MaxRanking;     //最大ランキング
    int                 m_RegisterScore;  //登録するスコア
    const char*         RankFile;         // ランキングファイル
    std::vector<float>  m_PosXList;       // 各順位のX座標
    int                 m_NextMoveRank;   // 次に動かす順位
    float               m_AnimationTimer; // アニメタイマー
    std::vector<enData> m_ScoreList;      //スコアリスト

};