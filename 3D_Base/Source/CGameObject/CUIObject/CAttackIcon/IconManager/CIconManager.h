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
    void NewIcon(int ID);
    // 動作関数
    void Update(/*const std::vector<int>& point*/);
    // 描画関数
    void Draw();
    // プレイヤーIDから対応するスコアオブジェクトを取得
  // CAttackIcon* GetIcon(int ID);
private:
    std::vector<std::unique_ptr<CAttackIcon>> m_Icons; // スコア
};