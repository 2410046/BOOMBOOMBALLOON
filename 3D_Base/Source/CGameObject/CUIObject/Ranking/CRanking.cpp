#include "CRanking.h"
#include <fstream>
#include "Scene/CGameData.h"
#include "MathUtility.h"
#include <algorithm>

//--------------------------------------------------
// 定数定義
//--------------------------------------------------
namespace
{
    constexpr float RankRaw = 70.f;       // 各順位の縦方向の間隔
    constexpr float RankY = 150.f;        // ランキングの開始Y座標

    constexpr float BaseX = 125.f;        // プレイヤーの表示開始X座標
    constexpr float BaseY = 430.f;        // プレイヤーの表示Y座標
    constexpr float RawX = 300.f;         // プレイヤー同士の横方向の間隔

    constexpr float Space = 30.f;         // スコアの数字同士の間隔

    constexpr float RankMove = 10.f;      // ランキングの移動速度
    constexpr float RankMoveMax = 200.0f; // ランキングの最大移動範囲

    constexpr int Update_Interval = 5;    // スコアの表示を更新する間隔

    constexpr int Rank_Max = 4;    // 順位の数

}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CRanking::CRanking()
    : m_ScoreList() // プレイヤーごとのスコアデータリスト
{
    // 数字描画用のスプライトを接続
    AttachSprite(*AssetManager::GetSprite2D(L"Number"));

    // スコアの表示サイズを設定
    m_vScale = D3DXVECTOR3(0.8f, 0.8f, 0.8f);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CRanking::~CRanking()
{
}

//--------------------------------------------------
// スコアの追加と登録処理
//--------------------------------------------------
void CRanking::Register(int ID, int score)
{
    // 新しいスコアデータを作成
    // ID：プレイヤーID
    // score：最終スコア
    // 0：表示用スコアの初期値
    // false：順位がまだ確定していない状態
    enData newData{ ID, score, 0, false };

    // スコアリストに新しいデータを追加
    m_ScoreList.push_back(newData);

    // 登録したプレイヤーIDを保存
    m_ID = ID;

    // スコアが高い順に並び替える
    std::sort(
        m_ScoreList.begin(),
        m_ScoreList.end(),
        [](const enData& a, const enData& b)
        {
            // スコアが同じ場合はプレイヤーIDが小さい順にする
            if (a.MyScore == b.MyScore)
            {
                return a.ID < b.ID;
            }

            // スコアが高いプレイヤーを前に配置する
            return a.MyScore > b.MyScore;
        });
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void CRanking::Update()
{
    //--------------------------------------------------
    // スコアカウントアップのスキップ処理
    //--------------------------------------------------

    // '1'キーを押した場合、スコアのカウントアップをスキップする
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
            // 対象プレイヤーのスコアデータを取得
            auto& data = m_ScoreList[i];

            // すでに順位が確定している場合はスキップ
            if (data.CoundEnd) continue;

            // プレイヤーの順位に応じて表示位置を確定する
            ConfirmRank(data.ID);

            // 順位確定済みの状態にする
            data.CoundEnd = true;
        }

        // 基底クラスの更新処理を実行
        CUIObject::Update();

        // 通常のカウントアップ処理を行わずに終了
        return;
    }

    //--------------------------------------------------
    // 通常のスコアカウントアップ処理
    //--------------------------------------------------

    // スコア更新までの経過時間を管理
    static float time = 0.0f;

    // 経過時間を加算
    time++;

    // 一定間隔ごとにスコアを更新する
    if (time >= Update_Interval)
    {
        // 経過時間をリセット
        time = 0;

        // 全プレイヤーの表示スコアを更新
        for (auto& data : m_ScoreList)
        {
            // 順位が確定しているプレイヤーは更新しない
            if (data.CoundEnd) continue;

            // 最終スコアと現在の表示スコアとの差を取得
            int diff = data.MyScore - data.DisplayScore;

            // 差を-1～1の範囲に制限して表示スコアを更新
            // 最終スコアに向かって1ずつ増減させる
            data.DisplayScore += std::clamp(diff, -1, 1);
        }

        //--------------------------------------------------
        // 順位確定処理
        //--------------------------------------------------

        // 最下位から順番に順位確定の条件を確認する
        for (int i = static_cast<int>(m_ScoreList.size()) - 1; i >= 0; --i)
        {
            // 対象プレイヤーのスコアデータを取得
            auto& data = m_ScoreList[i];

            // すでに順位が確定している場合はスキップ
            if (data.CoundEnd) continue;

            // 最終スコアに到達していなければ順位を確定しない
            if (data.DisplayScore != data.MyScore) break;

            // プレイヤーの順位に応じて表示位置を確定する
            ConfirmRank(data.ID);

            // 順位確定済みの状態にする
            data.CoundEnd = true;

            // 1回の更新で確定する順位は1人だけにする
            break;
        }
    }

    // 基底クラスの更新処理を実行
    CUIObject::Update();
}

//--------------------------------------------------
// 描画処理
//--------------------------------------------------
void CRanking::Draw()
{
    //--------------------------------------------------
    // プレイヤーごとのスコア描画
    //--------------------------------------------------

    // 登録されているプレイヤーの人数分だけ繰り返す
    // プレイヤーごとのスコア描画
    for (size_t i = 0; i < m_ScoreList.size(); ++i)
    {
        const enData& data = m_ScoreList[i];

        // プレイヤーIDに対応する順位位置を取得
        int rankIndex = GetRankIndex(data.ID);

        if (rankIndex < 0)
            continue;

        // 数字の描画パターン
        m_Patten = data.ID;

        // 順位に応じた表示位置
        m_vPosition = D3DXVECTOR3(
            BaseX + rankIndex * RawX,
            BaseY,
            0.f
        );

        // スコアを描画
        Number(data.DisplayScore, Space);
    }
}

//--------------------------------------------------
// 順位確定時の表示位置設定
//--------------------------------------------------
void CRanking::ConfirmRank(int playerID)
{
    // 順位が確定したプレイヤーの配置先
    int target = 3 - m_ConfirmCount;

    if (m_ConfirmCount >= Rank_Max)
        return;

    // 確定したプレイヤーIDを探す
    int index = -1;

    for (int i = 0; i < Rank_Max; ++i)
    {
        if (m_RankID[i] == playerID)
        {
            index = i;
            break;
        }
    }

    if (index < 0)
        return;

    // 確定したIDを取り出す
    int id = m_RankID[index];

    // 残りのIDを左に詰める
    for (int i = index; i < target; ++i)
    {
        m_RankID[i] = m_RankID[i + 1];
    }

    // 確定したIDを右側に配置
    m_RankID[target] = id;

    // 順位確定人数を加算
    ++m_ConfirmCount;
}
//順位位置を取得
int CRanking::GetRankIndex(int playerID) const
{
    for (int i = 0; i < Rank_Max; ++i)
    {
        if (m_RankID[i] == playerID)
        {
            return i;
        }
    }

    return -1;
}



//--------------------------------------------------
// 順位の取得
//--------------------------------------------------
int CRanking::GetRank(int index) const
{
    // リストの先頭は1位
    if (index == 0)
    {
        return 1;
    }

    // 前のプレイヤーとスコアが同じ場合は同順位にする
    if (m_ScoreList[index].MyScore ==
        m_ScoreList[index - 1].MyScore)
    {
        // 前のプレイヤーの順位を取得する
        return GetRank(index - 1);
    }

    // スコアが異なる場合は配列位置から順位を決める
    return index + 1;
}

//--------------------------------------------------
// スコアカウントアップ完了状態の取得
//--------------------------------------------------
bool CRanking::GetCountEnd(int index) const
{
    // 指定したプレイヤーの順位確定状態を返す
    return m_ScoreList.at(index).CoundEnd;
}
//--------------------------------------------------
// ランキングの初期化
//--------------------------------------------------
void CRanking::Reset()
{
    m_ScoreList.clear();
    m_ConfirmCount = 0;

    for (int i = 0; i < Rank_Max; ++i)
    {
        m_RankID[i] = i;
    }
}