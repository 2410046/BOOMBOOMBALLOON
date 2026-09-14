#include "CGameObject/CMeshObject/CPlayer/CPlayerManager.h"
#include "Asset/AssetManager/AssetManager.h"
#include "CMeshObject/CTracking/CTrackingManager/CTrackingManager.h"

#include "MathUtility.h"
#include <algorithm>
namespace
{
    // IDごとのプレイヤーの位置
    const D3DXVECTOR3 Player_Pos[] =
    {
        {  0.1f, 1.f, 11.5f }, // ID : 0
        {  0.1f, 1.f, 7.5f }, // ID : 1
    };
    //プレイヤーのサイズ
    constexpr float Player_Scale = 0.02f;
}
CPlayerManager::CPlayerManager()
{
}
// IDを指定してプレイヤーの生成
void CPlayerManager::NewPlayer(int ID)
{
    //プレイヤーのオブジェクト生成
    auto player = std::make_unique<CPlayer>();
    //メッシュの接続
    player->AttachMesh(*AssetManager::GetStatic(L"Player\\Player01"));
    //プレイヤーIDの設定
    player->SetID(ID);
    //サイズを設定
    player->SetScale(Player_Scale);
    //座標を設定
    player->SetPosition(Player_Pos[ID]);

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
CPlayerManager::GetShotFlags() const
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
/********************************************************************************
* Shotフラグ取得
********************************************************************************/
bool CPlayerManager::GetShotFlag(
    int ID) const
{
    if (ID < 0 ||
        ID >= static_cast<int>(
            m_Players.size()))
    {
        return false;
    }

    if (m_Players[ID] == nullptr)
    {
        return false;
    }

    return m_Players[ID]->GetShot();
}

