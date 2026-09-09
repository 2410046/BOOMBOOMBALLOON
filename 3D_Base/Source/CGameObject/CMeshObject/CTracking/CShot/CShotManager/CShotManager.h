#pragma once
#include <vector>
#include <memory>
#include "CMeshObject/CTracking/CShot/CShot.h"

//============================================================
// ShotManager
//============================================================
class CShotManager
{
public:

    CShotManager();

    ~CShotManager();
    //生成
    void NewShot(CTracking* pTracking);
    // 更新
    void Update(
        const std::vector<bool>& shotFlags);
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
    std::vector<std::unique_ptr<CShot>>
        m_Shots;
};
