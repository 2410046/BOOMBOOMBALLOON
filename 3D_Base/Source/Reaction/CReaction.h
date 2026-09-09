#pragma once
/********************************************************************************
* リアクションクラス
**/
#include <memory>
class CReaction
{
public:
    // 動きのタイプ
    enum MoveType
    {
        Boost,      //ブースト
        Firing,     //射撃
        KnockBack,  //ノックバック
    };
    struct ReactionParam
    {
        D3DXVECTOR3 from = {};
        D3DXVECTOR3 to = {};

        D3DXQUATERNION rot = {};

        float power = 0.5f;
        float time = 10.f;
    };
protected:
    //リアクションステータス
    struct ReactionState
    {
        bool active = false;          // アクション中か
        D3DXVECTOR3 velocity;         // 速度
        float timer = 0.0f;           // 継続時間
    };
public:
    CReaction();
    virtual ~CReaction() = default;
     //初期化
    virtual void Apply(const ReactionParam& param) = 0;
     //更新関数
	 virtual void Update() = 0;
     //座標を設定
    void SetPosition(D3DXVECTOR3* pos)
    {
        m_pPosition = pos;
    }
    //回転を設定
    void SetQuaternion(D3DXQUATERNION* Quoternion)
    {
        m_pQuaternion = Quoternion;
    }
     //モーションを設定
    virtual MoveType GetType() const = 0;

     bool IsActive() const
     {
         return m_State.active;
     }

     //時間が０の場合
     bool TimeOut()
     {
         return m_State.timer <= 0.f;
     };
     //リアクションを終了する
     void Stop()
     {
         m_State.active = false;
         m_State.timer = 0.0f;
     }
     //リアクション中の場合
     bool Play(const std::shared_ptr<CReaction>& reaction,
         MoveType type)
     {
         if (!reaction)
         {
             return false;
         }

         return reaction->IsActive() &&
             reaction->GetType() == type;
     }
protected:
    ReactionState m_State = {};
    D3DXVECTOR3* m_pPosition = nullptr;//これを戻すとエラーが
    D3DXQUATERNION* m_pQuaternion = nullptr;
};
