#include "CBalloonManager.h"
#include "CMeshObject/CTracking/CTrackingManager/CTrackingManager.h"
//============================================================
// Constructor
//============================================================

CBalloonManager::CBalloonManager()
   // : m_pTracking(nullptr)
{
}
//============================================================
// Destructor
//============================================================

CBalloonManager::~CBalloonManager()
{
    Release();
}
//生成
void CBalloonManager::NewBalloon(CTracking* pTracking)
{
    // プレイヤーIDからTracking取得
    if (pTracking == nullptr)
    {
        return;
    }
    // プレイヤーID
    int playerID =
        pTracking->GetID();

    //// 同じプレイヤーの風船が
    //// すでに存在するか確認
    //if (GetBalloon(playerID) != nullptr)
    //{
    //    return;
    //}
    // 風船生成
    auto balloon =
        std::make_unique<CBalloon>();
    // Trackingから初期位置・方向を取得
    balloon->Init(pTracking);
    // 風船登録
    m_Balloons.emplace_back(
        std::move(balloon));
}
//更新関数
void CBalloonManager::Update(
    const std::vector<int>& lifes)
{
    ////========================================================
    //// Balloon数をPlayer数に合わせる
    ////========================================================

    //while (m_Balloons.size() <
    //    m_Tracking.size())
    //{
    //    m_Balloons.emplace_back(
    //        std::make_unique<CBallun>());
    //}


    ////========================================================
    //// Playerごと
    ////========================================================

    //for (int i = 0;
    //    i < static_cast<int>(
    //        m_Tracking.size());
    //    ++i)
    //{
    //    if (!m_Balloons[i])
    //    {
    //        continue;
    //    }


    //    if (m_Tracking[i] == nullptr)
    //    {
    //        continue;
    //    }


    //    if (i >= static_cast<int>(
    //        hitFlags.size()))
    //    {
    //        continue;
    //    }


    //    if (i >= static_cast<int>(
    //        lives.size()))
    //    {
    //        continue;
    //    }


        //====================================================
        // Tracking
        //====================================================

        //D3DXVECTOR3 position =
        //    m_Tracking[i]->GetPosition();
    for (int playerID = 0;
        playerID < static_cast<int>(lifes.size());
        ++playerID)
    {
        // PlayerIDからTrackingを取得
        CTracking* pTracking =
            CTrackingManager::GetInstance()
            ->GetTracking(playerID);

        if (pTracking == nullptr)
        {
            continue;
        }
        
        int lifeCount = lifes[playerID];

        // 現在このPlayerが持っている風船数
        int balloonCount = 0;

        for (auto& balloon : m_Balloons)
        {
            if (balloon == nullptr)
            {
                continue;
            }

            if (balloon->GetID() == playerID)
            {
                balloonCount++;
            }
        }

        // Lifeより風船が少ない場合だけ生成
        while (balloonCount < lifeCount)
        {
            NewBalloon(pTracking);
            balloonCount++;
        }

        // Lifeより風船が多い場合は削除
        while (balloonCount > lifeCount)
        {
            for (auto it = m_Balloons.begin();
                it != m_Balloons.end();
                ++it)
            {
                if (*it == nullptr)
                {
                    continue;
                }

                if ((*it)->GetID() == playerID)
                {
                    m_Balloons.erase(it);
                    balloonCount--;
                    break;
                }
            }
        }

        // 配置
        UpdateTracking(
            playerID,
            pTracking,
            lifeCount);


        //// プレイヤーの残機数
        //int lifeCount = lifes[playerID];

        //// 必要な風船を生成
        //for (int i = 0; i < lifeCount; ++i)
        //{
        //    NewBalloon(pTracking);
        //}

        //// このプレイヤーの風船を配置
        //UpdateTracking(
        //    playerID,
        //    pTracking,
        //    lifeCount);

    }

    for (auto& balloon : m_Balloons)
    {
        if (balloon == nullptr)
        {
            continue;
        }

        balloon->Update();
    }

    // 死んだバルーンを削除
    m_Balloons.erase(
        std::remove_if(
            m_Balloons.begin(),
            m_Balloons.end(),
            [](const std::unique_ptr<CBalloon>& ballon)
            {
                return ballon == nullptr;
            }),
        m_Balloons.end());
}


//============================================================
// Draw
//============================================================

void CBalloonManager::Draw(CCamera*pCamera)
{
    for (auto& balloon : m_Balloons)
    {
        if (balloon == nullptr)
        {
            continue;
        }


        balloon->Draw(pCamera);
    }
}


//============================================================
// Release
//============================================================

void CBalloonManager::Release()
{
    m_Balloons.clear();
    m_Tracking.clear();
}

CBalloon* CBalloonManager::GetBalloon(int playerID)
{
    for (auto& balloon : m_Balloons)
    {
        if (balloon == nullptr)
        {
            continue;
        }

        if (balloon->GetID() == playerID)
        {
            return balloon.get();
        }
    }

    return nullptr;
}

void CBalloonManager::UpdateTracking(
    int playerID,
    CTracking* pTracking,
    int lifeCount)
{
    if (pTracking == nullptr)
    {
        return;
    }
    // プレイヤーの位置
    D3DXVECTOR3 playerPos =
        pTracking->GetPosition();
    // プレイヤーの回転
    D3DXQUATERNION quaternion =
        pTracking->GetQuaternion();

    // プレイヤーの前方向を取得
        // 前方向（X+）
    D3DXVECTOR3 forward(1.0f, 0.0f, 0.0f);
    // クォータニオンを回転行列へ変換
    D3DXMATRIX matRot;

    D3DXMatrixRotationQuaternion(
        &matRot,
        &quaternion);
    // プレイヤーの実際の前方向
    D3DXVECTOR3 dir;

    D3DXVec3TransformNormal(
        &dir,
        &forward,
        &matRot);
    // 正規化
    D3DXVec3Normalize(
        &dir,
        &dir);


    ////========================================================
    //// プレイヤーの右方向を取得
    ////========================================================

    D3DXVECTOR3 right(
        -dir.z,
        0.0f,
        dir.x);

    D3DXVec3Normalize(
        &right,
        &right);

    //========================================================
    // 風船の取得
    //========================================================
    const float Radius = 1.0f;

    // このプレイヤーの風船だけ取得
    std::vector<CBalloon*> balloons;

    for (auto& balloon : m_Balloons)
    {
        if (balloon == nullptr)
        {
            continue;
        }

        if (balloon->GetID() == playerID)
        {
            balloons.push_back(balloon.get());
        }
    }

    int count =
        static_cast<int>(balloons.size());

    if (count <= 0)
    {
        return;
    }

        // 風船が1個の場合
    if (count == 1)
    {
        D3DXVECTOR3 pos =
            playerPos;

        // 真後ろ
        pos -= dir * Radius;

        // 高さ
        pos.y += 1.0f;

        balloons[0]->SetPosition(pos);

        return;
    }
    for (int i = 0; i < count; ++i)
    {
        float angle =
            -D3DX_PI * 0.5f +
            D3DX_PI * i / (count-1);

        // 円形のX/Z成分
        float x =
            cosf(angle) * Radius;

        float z =
            sinf(angle) * Radius;
        //====================================================
        // プレイヤーの向きを基準にする
        //====================================================
        D3DXVECTOR3 pos =
            playerPos;
        // 前方向
        pos -= dir * x;
        // 右方向
        pos += right * z;
        // 高さ
        pos.y += 1.0f;
        // 位置設定
        balloons[i]->SetPosition(pos);
    }
}
