#include "CRanking.h"
#include <fstream>
#include "Scene/CGameData.h"
#include "MathUtility.h"
#include <algorithm>
namespace
{
    constexpr float RankRaw = 70.f;   // 各順位の縦間隔
    constexpr float RankY = 150.f;  // ランキング開始Y座標

    constexpr float BaseX = 850.f; // 表示開始X座標
    constexpr float BaseY = 210.f; // 表示開始Y座標
    constexpr float RawX = 190.f; // 各項目の横間隔
    constexpr float RawY = 120.f; // 各項目の縦間隔

    constexpr float Space = 40.f; // 数字の間隔
    // 点滅速度
    constexpr float Alpha_Speed = 0.1f;
    // アルファ値の基準値
    constexpr float Alpha_Center = 0.75f;
    // アルファ値の変化幅
    constexpr float Alpha_Range = 0.25f;
    //不透明
    constexpr float alpha = 1.0f;
    //ランキングの移動速度
    constexpr float RankMove = 10.f;
    //ランキングの移動最大範囲
    constexpr float RankMoveMax = 200.0f; 
}
CRanking::CRanking()
    : m_MyScore       ( )         // スコア配列
    , m_MaxRanking    ( 5 )       // 最大ランキング数
    , m_RegisterScore ( -1 )      // 直前登録スコア
    , m_PosXList      ( )         // 各順位のX座標
    , m_NextMoveRank  ( 0 )       // 次に動かす順位
    , m_AnimationTimer( 0.f )     // アニメタイマー
    , m_ScoreList     ( )         // 詳細スコアリスト
    , RankFile        ( nullptr )
{
       //スプライトを接続
       AttachSprite(
           *CSpriteManager::GetSprite2D("Number"));
       // ランキング位置初期化（画面外からスタート）
       m_PosXList.resize(m_MaxRanking, -20.0f);
       //パターン番号
       m_Patten = 2;
}

CRanking::~CRanking()
{
}

//スコアの追加と登録処理
void CRanking::Register(
    int ID, int score, int combo, int miss)
{   
    // ランキングファイル名を設定
    RankFile = CGameData::GetRank();
    // ランキングファイルを読み込む
    ReadRank();

    //--------------------------------------------------------
    // 新しいスコアデータ作成
    //--------------------------------------------------------
    // プレイヤーID・スコア・コンボ・ミス数をまとめて保存
    enData newData{ ID, score, combo, miss };
    
    // スコアリストに追加
    m_ScoreList.push_back(newData);

  // 直前に登録したスコアなら処理終了
     if (score == m_RegisterScore)
     {
         return;
     }

  // 既にランキングに存在するスコアも無視
    if (std::find(m_MyScore.begin(), m_MyScore.end(), score) != m_MyScore.end())
    {
        return;
    }

    // スコア配列に追加（ランキング用）
    m_MyScore.push_back(score);

    // スコアを降順で並び替え（高い順）
    std::sort(m_MyScore.begin(), m_MyScore.end(), std::greater<int>());

      // 最大ランキング数を超えた場合
      // 余分なスコアを削除
    if (m_MyScore.size() > m_MaxRanking)
    {
        m_MyScore.resize(m_MaxRanking);
    }
    // 更新されたランキングをファイルに保存
    SaveRank();
}
//動作関数
void CRanking::Update()
{
    // 点滅演出用タイマー（アルファ値を周期的に変化）
    static float time = 0.0f;
    time += Alpha_Speed;
    // sin波でアルファ値を変化させ、点滅演出を行う
    m_Alpha
        = Alpha_Center + sinf(time) * Alpha_Range;
    // ランキングを横方向にスライド移動
    RankingMove();
    CUIObject::Update();
}
//描画関数
void CRanking::Draw()
{
        // ランキングの描画
        for (size_t rank = 0; rank < m_MaxRanking; ++rank)
        {
            int ScoreRank = 0;
            // 数字表示用パターン設定（共通デザイン）
            m_Patten = 2;
            // スコアが存在する場合のみ取得
            if (rank < m_MyScore.size())
            {
                ScoreRank = m_MyScore[rank];
            }
            // 各順位ごとのX座標（アニメーションで変化）
            float x = m_PosXList[rank];

           // プレイヤースコアかどうか判定
            bool isPlayerScore = false;

            for (auto& data : m_ScoreList)
            {
                // ランキングスコアと一致したら
                // プレイヤースコアとして扱う
                if (data.MyScore == ScoreRank)
                {
                    isPlayerScore = true;
                    break;
                }
            }
            // ランキングに追加された
            // プレイヤーのスコアを点滅
            if (isPlayerScore)
            {
                m_pSprite->SetAlpha(m_Alpha);
            }
            else
            {
                m_pSprite->SetAlpha(alpha);
            }
            //座標
            m_vPosition = D3DXVECTOR3(
                x, RankY + (rank * RankRaw), 0.0f);
            // 数字描画
            Number(m_vPosition, ScoreRank, Space);
        }
    
    //--------------------------------------------------
    // プレイヤーのスコアを描画
    //--------------------------------------------------
        for (size_t i = 0; i < m_ScoreList.size(); ++i)
        {
            // プレイヤーごとのデータ取得
            const enData& data = m_ScoreList[i];
            // 表示内容（コンボ・ミス・スコア）
            int values[] 
                = { data.MyCombo,data.MyMiss,data.MyScore };

            //スコア、コンボ、ミスの描画
            for (int j = 0; j < 3; ++j)
            {
                // プレイヤーごとに表示パターン変更
                m_Patten = data.ID;
                D3DXVECTOR3 pos =  D3DXVECTOR3(
                        BaseX + i * RawX, BaseY + j * RawY, 0.f);
                //スコア、コンボ、ミスは点滅しない
                m_pSprite->SetAlpha(alpha); 
                // 数値描画
                Number(pos, values[j], Space);
            }
        }
}

//ランキングを読み込む
void CRanking::ReadRank()
{
    // ランキングファイルを開く
    std::ifstream ifs(RankFile);
    if (!ifs.is_open())  // ファイルが開けなかった場合は何もせず終了
        return;

    // 現在のスコアリストをクリア
    m_MyScore.clear();

    int score;
    // ファイルからスコアを1つずつ読み込み、リストに追加
    while (ifs >> score)
    {
        m_MyScore.push_back(score);
    }

    // スコアを降順にソート（高いスコアが先頭にくるように）
    std::sort(
        m_MyScore.begin(), m_MyScore.end(), std::greater<int>());

    // 最大ランキング数を超えていたら切り詰める
    if (m_MyScore.size() > m_MaxRanking)
    {
        m_MyScore.resize(m_MaxRanking);
    }

    // 読み込んだスコアが1件以上ある場合
    if (!m_MyScore.empty())
    {
        // 最高スコアを登録済みスコアとして保持
        m_RegisterScore = m_MyScore.front();
    }

    // ファイルを閉じる
    ifs.close();

}
//ランキングを保存
void CRanking::SaveRank()
{
    std::ofstream ofs(RankFile);
    if (!ofs.is_open())
        return;

    for (size_t i = 0; i < m_MyScore.size(); ++i)
    {
        ofs << m_MyScore[i] << std::endl;
    }

    ofs.close();
}


// ランキング移動処理
void CRanking::RankingMove()
{
    //--------------------------------------------------
    // アニメーション時間更新
    //--------------------------------------------------
    // フレームベースで時間を加算（60FPS想定）
    m_AnimationTimer += 1.0f / 60.0f;

    // 一定時間ごとに次の行を移動対象に追加
    // → ランキングが上から順に動く演出
    if (m_NextMoveRank < m_MaxRanking &&
        m_AnimationTimer >= 0.1f)
    {
        m_NextMoveRank++;
        m_AnimationTimer = 0.0f;
    }
    // ランキングの移動処理
    for (int i = 0; i < m_NextMoveRank; ++i)
    {
        // X座標を更新（横移動）
        m_PosXList[i] += RankMove;
        // 画面外に出ないよう制限
        m_PosXList[i] 
            = std::clamp(m_PosXList[i],0.f, RankMoveMax);
    }
}

//シーン遷移のときまた同じ場所に戻す
void CRanking::Reset()
{
    m_NextMoveRank = 0;
    m_AnimationTimer = 0.0f;
    std::fill(m_PosXList.begin(), m_PosXList.end(), -19.0f);
    m_ScoreList.clear();
    m_MyScore.clear();       //新しいスコアをスコアリストに追加
    RankFile = nullptr;
}