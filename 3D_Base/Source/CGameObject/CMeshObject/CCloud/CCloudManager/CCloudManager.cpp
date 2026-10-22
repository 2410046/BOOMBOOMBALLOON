#include "CCloudManager.h"
//============================================================
// Constructor
//============================================================

CCloudManager::CCloudManager()
{
}

CCloudManager::~CCloudManager()
{
    Release();
}

void CCloudManager::NewCloud()
{
    D3DXVECTOR3 m_Min = D3DXVECTOR3(-8.f, 1.f, 5.5f);
    D3DXVECTOR3 m_Max = D3DXVECTOR3(7.f, 1.f, 17.5f);
    for (int i = 0;i <= 50;i++)
    {
        // Cloud生成
        auto cloud =
            std::make_unique<CCloud>();

        //メッシュを接続
        cloud->AttachMesh(*AssetManager::GetStatic(L"Asset\\Cloud"));
        const D3DXVECTOR3 Pos = D3DXVECTOR3(-8.f+(i * 1.f), 1.f, 5.5f + (i * 1.f));
        cloud->SetPosition(Pos);
        // Shot登録
        m_Clouds.emplace_back(
            std::move(cloud));
    }

}

void CCloudManager::Update()
{
    // Shot更新
    for (auto& cloud : m_Clouds)
    {
        if (cloud == nullptr)
        {
            continue;
        }

        cloud->Update();
    }

    //Shotを削除
        //m_Cloud.erase(
        //    std::remove_if(
        //        m_Shots.begin(),
        //        m_Shots.end(),
        //        [](const std::unique_ptr<CShot>& shot)
        //        {
        //            return shot == nullptr ||
        //                !shot->GetFlag();
        //        }),
        //    m_Shots.end());
}
void CCloudManager::Draw(CCamera*pCamera)
{
    for (auto& cloud : m_Clouds)
    {
        if (cloud == nullptr)
        {
            continue;
        }
        cloud->Draw(pCamera);
    }
}

void CCloudManager::Release()
{
    m_Clouds.clear();
}