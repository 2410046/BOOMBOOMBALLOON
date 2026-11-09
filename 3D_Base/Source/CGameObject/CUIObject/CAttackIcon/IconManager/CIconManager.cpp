#include"CIconManager.h"
//コンストラクタ
CIconManager::CIconManager()
    : m_Icons()
{
}
//定数
namespace
{
    //----------------------------------------------------
    // IDごとのスコア表示位置
    //----------------------------------------------------
    const D3DXVECTOR3 ICON_POS[] =
    {
        {90.f, 10.f, 0.f}, // ID : 0
        {300.f, 10.f, 0.f},  // ID : 1
        {900.f, 10.f, 0.f},  // ID : 2
        {1110.f, 10.f, 0.f},  // ID : 3
    };
    constexpr int Max = 4;
}
// IDを指定してスコアを生成
void CIconManager::NewIcon()
{
    for (int i = 0; i < Max; i++)
    {
        // スコアオブジェクト生成
        auto icon = std::make_unique<CAttackIcon>();
        //スプライトを接続
        icon->AttachSprite(*AssetManager::GetSprite2D(L"AttackUser"));
        //IDを設定する
        icon->SetID(i);
        //座標を設定
        icon->SetPosition(ICON_POS[i]);
        //スコアの登録
        m_Icons.emplace_back(std::move(icon));
    }
}
//更新関数
void CIconManager::Update(
    const std::vector<std::unordered_map<std::string, bool>>& flag)
{
    for (auto& icon : m_Icons)
    {
        const int playerNo = icon->GetID();
        icon->SetCoolFlag(flag[playerNo]);
        icon->Update();
    }
}
//描画関数
void CIconManager::Draw()
{
    for (auto& icon : m_Icons)
    {
        icon->Draw();
    }
}
 