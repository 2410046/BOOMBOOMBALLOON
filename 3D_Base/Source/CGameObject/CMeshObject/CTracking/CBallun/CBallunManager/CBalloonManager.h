#pragma once
#include <vector>
#include <memory>

#include "CMeshObject/CTracking/CBallun/CBalloon.h"
#include "CMeshObject/CTracking/CTracking.h"
//============================================================
// BalloonManager
//============================================================
class CBalloonManager
{
public:
    CBalloonManager();

    ~CBalloonManager();

    void NewBalloon(CTracking* pTracking);
    // 更新関数
    void Update(
        const std::vector<int>& Life);
    // 描画関数
    void Draw( CCamera* pCamera );
    // Release
    void Release();

    CBalloon* GetBalloon(int playerID);
    //追尾
    void UpdateTracking(
            int playerID,
            CTracking* pTracking,
            int lifeCount);
private:
    // Balloon
    std::vector<std::unique_ptr<CBalloon>>
        m_Balloons;
    // Trackingへの参照
    std::vector<CTracking*>m_Tracking;
};