#include "CGameObject/CMeshObject/CPlayer/CPlayerManager.h"
#include "Asset/AssetManager/AssetManager.h"
#include "CMeshObject/CTracking/CTrackingManager/CTrackingManager.h"
namespace
{
    // IDごとのプレイヤーの位置
    const D3DXVECTOR3 Player_Pos[] =
    {
        {  -6.f, 1.f, 5.5f }, // ID : 0
        {  -8.f, 1.f, 13.5f }, // ID : 1
        {  6.f, 1.f, 5.5f }, // ID : 2
        {  6.f, 1.f, 13.5f }, // ID : 2
    };
    //プレイヤーのサイズ  
    constexpr float Player_Scale = 0.02f;
    constexpr int Max = 4;
    constexpr bool m_Com[] = { true };
}
CPlayerManager::CPlayerManager()
{
}
// IDを指定してプレイヤーの生成
void CPlayerManager::NewPlayer()
{
    // コントローラー接続数
    int padCount = CXInput::GetInstance(0)->GetPadID();

    // 人間プレイヤーは1人
    int playerCount = 1;

    // COM人数
    int comCount = Max - playerCount;

    for (int i = 0; i < Max; i++)
    {
         //プレイヤーのオブジェクト生成
         //auto player = std::make_unique<CPlayer>();

         std::unique_ptr<CPlayer> player = nullptr;


         if (i < padCount)
         {
             player = std::make_unique<CPlayer>();
         }
         else
         {
             player = std::make_unique<CCom>();
         }

         //メッシュの接続
         player->AttachMesh(*AssetManager::GetStatic(L"Player\\Player01"));
         //プレイヤーIDの設定
         player->SetID(i);
         //サイズを設定
         player->SetScale(Player_Scale);
         //座標を設定
         player->SetPosition(Player_Pos[i]);

         //プレイヤー登録
         m_Players.emplace_back(std::move(player));
        
         auto tracking =
             std::make_unique<CTracking>();

         // 今登録したプレイヤーを追跡
         tracking->SetTarget(
             m_Players.back().get());

         // TrackingManagerへ登録
         CTrackingManager::GetInstance()
             ->AddTracking(
                 std::move(tracking));
    }

    // 全プレイヤー情報を生成後にCOMへ他プレイヤー参照を共有
    std::vector<CPlayer*> rawPlayers = GetPlayers();
    for (auto& player : m_Players)
    {
        player->SetTargetPlayers(rawPlayers);
    }
}
//動作関数
void CPlayerManager::Update()
{
    for (auto& player : m_Players)
    {
        player->Update();
    }
}
//描画関数
void CPlayerManager::Draw(const CCamera* pCamera)
{
    for (auto& player : m_Players)
    {
        if (!player)
        {
            continue;
        }

        player->Draw(pCamera);
    }
}
// 全プレイヤー取得
std::vector<CPlayer*> CPlayerManager::GetPlayers() const
{
    std::vector<CPlayer*> result;
    for (auto& p : m_Players)
    {
        result.push_back(p.get()); // unique_ptr の生ポインタを返す
    }
    return result;
}
// プレイヤー取得
CPlayer* CPlayerManager::GetPlayer(int index)
{
    if (index >= 0 && index < static_cast<int>(m_Players.size()))
    {
        return m_Players[index].get(); // 所有権は保持したままポインタを返す
    }
    return nullptr;
}
/********************************************************************************
* すべてのプレイヤーのShotフラグ取得
********************************************************************************/
std::vector<bool>
CPlayerManager::GetShots() const
{
    std::vector<bool> result;

    for (const auto& player : m_Players)
    {
        if (player == nullptr)
        {
            result.push_back(false);
            continue;
        }

        result.push_back(
            player->GetShot());
    }

    return result;
}
//全プレイヤーのライフを取得
std::vector<int>
CPlayerManager::GetLifes() const
{
    std::vector<int> result;

    for (const auto& player : m_Players)
    {
        if (player == nullptr)
        {
            result.push_back(false);
            continue;
        }
        result.push_back(
            player->GetLife());
    }

    return result;
}
//全プレイヤーのポイントを取得
std::vector<int> CPlayerManager::GetPoints() const
{
    std::vector<int> result;

    for (const auto& player : m_Players)
    {
        if (player == nullptr)
        {
            result.push_back(false);
            continue;
        }
        result.push_back(
            player->GetPoint());
    }

    return result;
}
//全プレイヤーのクールタイムフラグを取得
std::vector<std::unordered_map<std::string, bool>> CPlayerManager::GetCoolFlag() const
{
    std::vector<std::unordered_map<std::string, bool>> result;

    for (const auto& player : m_Players)
    {
        if (player == nullptr)
        {
            result.push_back({});
            continue;
        }
        result.push_back(
            player->GetCoolFlag());
    }

    return result;
}

