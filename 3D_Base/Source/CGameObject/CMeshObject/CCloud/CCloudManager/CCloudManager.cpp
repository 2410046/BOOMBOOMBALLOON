#include "CCloudManager.h"
#include "CGameObject/CUIObject/CTime/CTime.h"		//タイムクラス
namespace
{
    const int ObjectCount = 51;
    const float Radius = 100.0f;
}
CCloudManager::CCloudManager()
{
}

CCloudManager::~CCloudManager()
{
    Release();
}
//動いた雲にショットを当てると5方向に弾を発射.雲はBOOSTとSHOTがぶつかったプレイヤーの球を発射する
void CCloudManager::NewCloud()
{
    D3DXVECTOR3 m_Min = D3DXVECTOR3(-8.f, 1.f, 5.5f);
    D3DXVECTOR3 m_Max = D3DXVECTOR3(7.f, 1.f, 17.5f);
    for (int i = 0;i < ObjectCount;i++)
    {
        // Cloud生成
        auto cloud =
            std::make_unique<CCloud>();

        //メッシュを接続
        cloud->AttachMesh(*AssetManager::GetStatic(L"Asset\\Cloud"));
        // 円周上の角度を計算
        const float angle = 2.0f * D3DX_PI * i / ObjectCount;

        // 円状の座標を計算
        const D3DXVECTOR3 Pos = D3DXVECTOR3(
            -1.0f + 14.0f * cosf(angle),  // X座標
            1.0f,                         // Y座標
            13.5f + 11.9f * sinf(angle)   // Z座標
        );

        // 座標を設定
        cloud->SetPosition(Pos);
        // 登録
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