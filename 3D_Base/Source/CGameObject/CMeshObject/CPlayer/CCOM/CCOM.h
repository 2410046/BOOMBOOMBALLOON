#pragma once
class CCom
{
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
};