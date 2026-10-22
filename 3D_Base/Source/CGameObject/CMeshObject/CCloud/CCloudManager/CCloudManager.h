#pragma once
#include <vector>
#include <memory>
#include "CMeshObject/CCloud/CCloud.h"

//============================================================
// CloudManager
//============================================================
class CCloudManager
{
public:

    CCloudManager();

    ~CCloudManager();
    //生成
    void NewCloud();
    // 更新
    void Update();
    // 描画
    void Draw(CCamera*pCamera);
    // 解放
    void Release();
private:
    // Shot生成
    void CreateShot(
        const D3DXVECTOR3& position,
        const D3DXVECTOR3& direction,
        int playerIndex);
private:
    // Shot
    std::vector<std::unique_ptr<CCloud>>
        m_Clouds;
};
