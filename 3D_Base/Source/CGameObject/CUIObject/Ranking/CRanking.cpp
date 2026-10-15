#include "CRanking.h"
#include <fstream>
#include "Scene/CGameData.h"
#include "MathUtility.h"
#include <algorithm>
namespace
{
    constexpr float RankRaw = 70.f;   // 各順位の縦間隔
    constexpr float RankY = 150.f;  // ランキング開始Y座標

    constexpr float BaseX = 125.f; // 表示開始X座標
    constexpr float BaseY = 430.f; // 表示開始Y座標
    constexpr float RawX = 300.f; // 各項目の横間隔


    constexpr float Space = 30.f; // 数字の間隔
    //ランキングの移動速度
    constexpr float RankMove = 10.f;
    //ランキングの移動最大範囲
    constexpr float RankMoveMax = 200.0f; 

    constexpr int   Update_Interval = 5;     // 表示更新間隔

}
CRanking::CRanking()
    : m_ScoreList     ( )         // 詳細スコアリスト
{
       //スプライトを接続
       AttachSprite(
           *AssetManager::GetSprite2D(L"Number"));
       m_vScale = D3DXVECTOR3(0.8f, 0.8f, 0.8f);

       for (int i = 0; i < 4; ++i)
       {
           m_PlayerPos[i] =
               D3DXVECTOR3(BaseX + i * RawX, BaseY, 0.f);
       }
       // ランキング位置初期化（画面外からスタート）
       //m_PosXList.resize(m_MaxRanking, -20.0f);
       //パターン番号
}

CRanking::~CRanking()
{
}

//スコアの追加と登録処理
void CRanking::Register(int ID, int score)
{
    //--------------------------------------------------------
    // 新しいスコアデータ作成
    //--------------------------------------------------------
    // プレイヤーID・スコア・コンボ・ミス数をまとめて保存
    enData newData{ ID, score ,0,false};

    // スコアリストに追加
    m_ScoreList.push_back(newData);
    //IDを取得
    m_ID = ID;
    // スコアが高い順に並び替え
    std::sort(
        m_ScoreList.begin(),
        m_ScoreList.end(),
        [](const enData& a, const enData& b)
        {
            // スコアが同じならIDの小さい順
            if (a.MyScore == b.MyScore)
            {
                return a.ID < b.ID;
            }

            // スコアが高い順
            return a.MyScore > b.MyScore;
        });
}
//動作関数
void CRanking::Update()
{
    // '1'キーを押したらスコアのカウントアップをスキップ
    if (GetAsyncKeyState('1') & 0x0001)
    {
        // 全プレイヤーの表示スコアを最終スコアにする
        for (auto& data : m_ScoreList)
        {
            data.DisplayScore = data.MyScore;
        }

        // 最下位から順番に順位を確定する
        for (int i = static_cast<int>(m_ScoreList.size()) - 1; i >= 0; --i)
        {
            auto& data = m_ScoreList[i];

            // すでに順位が確定している場合はスキップ
            if (data.CoundEnd) continue;

            // プレイヤーの表示位置を確定する
            ConfirmRank(data.ID);

            // 順位確定済みにする
            data.CoundEnd = true;
        }

        // 基底クラスの更新処理を実行
        CUIObject::Update();

        // 通常のカウントアップ処理を行わずに終了
        return;
    }

    // 通常のスコアカウントアップ処理
    static float time = 0.0f;
    time++;

    // 一定間隔ごとにスコアを更新する
    if (time >= Update_Interval)
    {
        // 経過時間をリセット
        time = 0;

        // 全プレイヤーの表示スコアを1ずつ最終スコアに近づける
        for (auto& data : m_ScoreList)
        {
            // 順位が確定している場合はスキップ
            if (data.CoundEnd) continue;

            // 最終スコアとの差を求める
            int diff = data.MyScore - data.DisplayScore;

            // 差を-1～1の範囲に制限して表示スコアを更新
            data.DisplayScore += std::clamp(diff, -1, 1);
        }

        // 最下位から順番に順位確定の条件を確認する
        for (int i = static_cast<int>(m_ScoreList.size()) - 1; i >= 0; --i)
        {
            auto& data = m_ScoreList[i];

            // すでに順位が確定している場合はスキップ
            if (data.CoundEnd) continue;

            // 最終スコアに達していなければ、次の更新まで待つ
            if (data.DisplayScore != data.MyScore) break;

            // プレイヤーの順位と表示位置を確定する
            ConfirmRank(data.ID);

            // 順位確定済みにする
            data.CoundEnd = true;

            // 1回の更新で確定する順位は1人だけにする
            break;
        }
    }

    // 基底クラスの更新処理を実行
    CUIObject::Update();
}
//描画関数
void CRanking::Draw()
{

    //--------------------------------------------------
// プレイヤーのスコアを描画
//--------------------------------------------------
    for (size_t i = 0; i < m_ScoreList.size(); ++i)
    {
        // プレイヤーごとのデータ取得
        const enData& data = m_ScoreList[i];
        //スコアの描画
       // プレイヤーごとに表示パターン変更
        m_Patten = data.ID;

        D3DXVECTOR3 pos = m_PlayerPos[data.ID];
        // 数値描画
        Number(pos, data.DisplayScore, Space);
    }
}

void CRanking::ConfirmRank(int playerID)
{
    // 右端から順に配置
    int target = 3 - m_ConfirmCount;

    if (m_ConfirmCount >= 4)
        return;

    // 移動対象のプレイヤーと配置先のプレイヤーの座標を交換
    int targetID = -1;

    for (int i = 0; i < 4; ++i)
    {
        if (m_PlayerPos[i].x == BaseX + target * RawX)
        {
            targetID = i;
            break;
        }
    }

    if (targetID < 0)
        return;

    std::swap(m_PlayerPos[playerID], m_PlayerPos[targetID]);

    ++m_ConfirmCount;
}
//座標交換
void CRanking::SwapPosition(int playerID, int targetID)
{
    if (playerID < 0 || playerID >= 4 ||
        targetID < 0 || targetID >= 4)
    {
        return;
    }

    std::swap(m_PlayerPos[playerID], m_PlayerPos[targetID]);
}
// 順位の取得
int CRanking::GetRank(int index) const
{
    if (index == 0)
    {
        return 1;
    }

    // 前のプレイヤーと同じスコアなら同順位
    if (m_ScoreList[index].MyScore ==
        m_ScoreList[index - 1].MyScore)
    {
        return GetRank(index - 1);
    }

    // スコアが違うなら配列位置から順位を決める
    return index + 1;
}
bool CRanking::GetCountEnd(int index) const
{
    return m_ScoreList.at(index).CoundEnd;
}
//プレイヤーID取得
int CRanking::GetPlayerID(int index) const
{
    return m_ScoreList.at(index).ID;
}
//シーン遷移のときまた同じ場所に戻す
void CRanking::Reset()
{
    m_ScoreList.clear();
    m_ConfirmCount = 0;

    // 初期位置に戻す
    for (int i = 0; i < 4; ++i)
    {
        m_PlayerPos[i] =
            D3DXVECTOR3(BaseX + i * RawX, BaseY, 0.0f);
    }
}