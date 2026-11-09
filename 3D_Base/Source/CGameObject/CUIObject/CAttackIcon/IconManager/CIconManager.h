#pragma once
#include <vector>
#include <memory>
#include "Asset/Sprite/CSpriteManager.h"
#include "CUIObject/CAttackicon/CAttackIcon.h"	//攻撃アイコン
/********************************************************************************
*	アイコンマネージャークラス
**/
class CIconManager
{
public:
    //コンストラクタ
    CIconManager();
    //デストラクタ
    ~CIconManager() = default;

    // アイコンの生成
    void NewIcon();
    // 動作関数
    void Update(
        const std::vector<std::unordered_map<std::string, bool>>& flag);
    // 描画関数
    void Draw();
private:
    std::vector<std::unique_ptr<CAttackIcon>> m_Icons; // スコア
};