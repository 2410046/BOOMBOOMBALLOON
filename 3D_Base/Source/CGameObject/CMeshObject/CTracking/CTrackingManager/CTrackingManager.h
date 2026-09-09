#pragma once

class CPlayer;
/********************************************************************************
* 追跡クラス
* プレイヤーの座標と方向を取得
*
**/
#pragma once

#include <memory>
#include <vector>

#include "CMeshObject/CTracking/CTracking.h"
#include "Singleton.h"
/********************************************************************************
* トラッキングマネージャー
********************************************************************************/
class CTrackingManager
    :public Singleton<CTrackingManager>
{

private:
    // シングルトン
    friend class Singleton<CTrackingManager>;
public:
    // 初期化
    void Init();

    // Tracking登録
    void AddTracking(
        std::unique_ptr<CTracking> tracking);

    // IDからTracking取得
    CTracking* GetTracking(int ID);

private:
    // Trackingを所有
    std::vector<std::unique_ptr<CTracking>> m_Trackings;
};