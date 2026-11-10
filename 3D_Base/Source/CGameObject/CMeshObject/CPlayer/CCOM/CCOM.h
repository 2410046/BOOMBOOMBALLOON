#pragma once
class CCom
{
private:
    enum MOVE_ACTION
    {
        Approach,
        Boost,
        Shot,
        Escape,
    };
public:
    void Update();

private:
    void Decision();
    //移動
    void Move();
    //攻撃
    void Attack();
    //回避
    void Avoid();
private:
    int m_TargetID;
    D3DXVECTOR3 m_Direction;
    int m_Move;
};