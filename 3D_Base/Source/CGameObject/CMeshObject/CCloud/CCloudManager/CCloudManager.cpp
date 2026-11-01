#include "CCloudManager.h"
//============================================================
// Constructor
//============================================================
namespace
{
    const int ObjectCount = 50;
    const float Radius = 100.0f;
}
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
    for (int i = 0;i < ObjectCount;i++)
    {
        // Cloud生成
        auto cloud =
            std::make_unique<CCloud>();

        //メッシュを接続
        cloud->AttachMesh(*AssetManager::GetStatic(L"Asset\\Cloud"));
        // 円周上の角度を計算
        const float angle = 2.0f * D3DX_PI * i / 51.0f;

        // 円状の座標を計算
        const D3DXVECTOR3 Pos = D3DXVECTOR3(
            -1.0f + 14.0f * cosf(angle),  // X座標
            1.0f,                         // Y座標
            13.5f + 12.0f * sinf(angle)   // Z座標
        );

        // 座標を設定
        cloud->SetPosition(Pos);
        // Shot登録
        m_Clouds.emplace_back(
            std::move(cloud));
    }


    //    //縦に動きながら、横にゆっくり回転
    //    constexpr float YSpeed = 0.001f;
    //    constexpr float XSpeed = 0.01f;
    //    constexpr float MaxAngle = D3DX_PI / 2.0f;
    //    if (m_angle >= MaxAngle)
    //    {
    //        m_angle = 0;
    //    }
    //    D3DXQUATERNION Quaternion;
    //    m_angle -= YSpeed; // 回転速度

    //    D3DXQuaternionRotationYawPitchRoll(
    //        &Quaternion,
    //        m_angle,
    //        0.f,
    //        0.0f);
    //    m_pSky->SetQuaternion(Quaternion);
    //    m_pSky->UpDown();
    //    //m_pSky->Turn(XSpeed, MaxAngle);
    //}


    //D3DXQUATERNION quaternion;

    //D3DXQuaternionRotationYawPitchRoll(
    //    &quaternion,
    //    -D3DX_PI / 3.f,  // 左90度
    //    0.0f,
    //    0.0f);

    //m_pSky->SetQuaternion(quaternion);
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