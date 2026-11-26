#include "CShotManager.h"
#include "CMeshObject/CTracking/CTrackingManager/CTrackingManager.h"

CShotManager::CShotManager()
{
}

CShotManager::~CShotManager()
{
    Release();
}

void CShotManager::NewShot(CTracking* pTracking)
{
#if 0
    // プレイヤーIDからTracking取得
    if (pTracking == nullptr)
    {
        return;
    }
    float Angle = 0.f;
    // Shot生成
    auto shot =
        std::make_unique<CShot>();
    // Trackingから初期位置・方向を取得
    shot->Init(
        pTracking, Angle);
    // Shot登録
    m_Shots.emplace_back(
        std::move(shot));

#else
    if (pTracking == nullptr)
    {
        return;
    }

    // プレイヤーのライフ数
    int Life = pTracking->GetLife();
    // 発射角度の間隔
    const float ShotAngle = 35.f;

    for (int i = 1; i <= Life; i++)
    {
        float Angle = 0.f;

        // 発射方向を均等に配置
        if (Life > 1)
        {
            Angle = -ShotAngle * (Life - 1) / 2.f
                + ShotAngle * i;
        }

        // Shot生成
        auto shot = std::make_unique<CShot>();

        // 初期位置・発射方向を設定
        shot->Init(pTracking, Angle);

        // Shot登録
        m_Shots.emplace_back(std::move(shot));
    }
#endif
}

void CShotManager::Update(
    const std::vector<bool>& shotFlags)
{
    // プレイヤーごとの発射処理
    for (int playerID = 0; 
        playerID < static_cast<int>(shotFlags.size()); ++playerID)
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
// Shot生成
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