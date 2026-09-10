#include "CShotManager.h"
#include "CMeshObject/CTracking/CTrackingManager/CTrackingManager.h"
//============================================================
// Constructor
//============================================================

CShotManager::CShotManager()
{
}


//============================================================
// Destructor
//============================================================

CShotManager::~CShotManager()
{
    Release();
}

void CShotManager::NewShot(CTracking* pTracking)
{
    // プレイヤーIDからTracking取得
    if (pTracking == nullptr)
    {
        return;
    }
    // Shot生成
    auto shot =
        std::make_unique<CShot>();
    // Trackingから初期位置・方向を取得
    shot->Init(
        pTracking);
    // Shot登録
    m_Shots.emplace_back(
        std::move(shot));
}

//============================================================
// Update
//============================================================

void CShotManager::Update(
    const std::vector<bool>& shotFlags)
{
    // ---------------------------------------------------------
       // プレイヤーごとの発射処理
       // ---------------------------------------------------------
    // プレイヤーごとの発射処理
    for (int playerID = 0;
        playerID < static_cast<int>(shotFlags.size());
        ++playerID)
    {
        // 発射していない
        if (!shotFlags[playerID])
        {
            continue;
        }

        // PlayerIDからTrackingを取得
        CTracking* pTracking =
            CTrackingManager::GetInstance()
            ->GetTracking(playerID);

        if (pTracking == nullptr)
        {
            continue;
        }

        // Shot生成
        NewShot(pTracking);
    }

    // Shot更新
    for (auto& shot : m_Shots)
    {
        if (shot == nullptr)
        {
            continue;
        }

        shot->Update();


    }

    //Shotを削除
        m_Shots.erase(
            std::remove_if(
                m_Shots.begin(),
                m_Shots.end(),
                [](const std::unique_ptr<CShot>& shot)
                {
                    return shot == nullptr ||
                        !shot->GetFlag();
                }),
            m_Shots.end());
}


//============================================================
// CreateShot
//============================================================

void CShotManager::CreateShot(
    const D3DXVECTOR3& position,
    const D3DXVECTOR3& direction,
    int playerIndex)
{
    auto shot =
        std::make_unique<CShot>();

    m_Shots.push_back(
        std::move(shot));
}


//============================================================
// Draw
//============================================================

void CShotManager::Draw(CCamera*pCamera)
{
    for (auto& shot : m_Shots)
    {
        if (shot == nullptr)
        {
            continue;
        }
        shot->Draw(pCamera);
    }
}


//============================================================
// Release
//============================================================

void CShotManager::Release()
{
    m_Shots.clear();
}