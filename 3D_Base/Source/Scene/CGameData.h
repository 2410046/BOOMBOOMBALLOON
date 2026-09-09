#pragma once
#include <array>
#include"CGameData.h"
#include"Singleton.h"
/********************************************************************************
*	ゲームデータクラス.
**/
class CGameData 
    :public Singleton<CGameData>
{
private:
    //ステージデータ
    struct StageData
    {
        int BGM              = 0;           //ステージの音楽
        const char* CSVFile  = nullptr;     //CSVファイル
        std::string SkyName  = "Sky01";     //スカイメッシュナンバー
        const char* RankFile = nullptr;     //ランキングファイル
        int LimitTime        = 0;           //制限時間
    };
    friend class Singleton<CGameData>;
public:
    //プレイヤーの人数
    static int         PlayerNo()  { return GetInstance()->m_PlayNo; }
    //ステージBGM                        
    static int         BGMNo()     { return GetInstance()->m_Data[GetInstance()->m_StageNo].BGM; }
    //CSVファイル                         
    static const char* GetCSV()    { return GetInstance()->m_Data[GetInstance()->m_StageNo].CSVFile; }
    //Skyメッシュナンバー                 
    static std::string GetSkyNo()  { return GetInstance()->m_Data[GetInstance()->m_StageNo].SkyName; }
    //ランクファイル                      
    static const char* GetRank()   { return GetInstance()->m_Data[GetInstance()->m_StageNo].RankFile; }
    //制限時間                           
    static int         GetLimit()  { return GetInstance()->m_Data[GetInstance()->m_StageNo].LimitTime; }
    //ステージナンバーを設定
    void SetMode(int No) { m_StageNo = No; }
    //プレイヤーの人数を設定
    void SetPlayNo(int No) { m_PlayNo = No; }
private:
    CGameData()
    {
        m_Data[0] 
            = { 0, "Data\\CSV\\BGM1.csv", "Sky01","Data\\Score\\Score01.txt" ,155 };
        m_Data[1] 
            = { 1, "Data\\CSV\\BGM2.csv", "Sky02","Data\\Score\\Score02.txt" ,85 };
        m_Data[2]
            = { 2, "Data\\CSV\\BGM3.csv", "Sky03","Data\\Score\\Score03.txt" ,150 };
    }
private:
    std::array<StageData, 6> m_Data{};
    int m_StageNo = 0;
    int m_PlayNo = 2;
};

