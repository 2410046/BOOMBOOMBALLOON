#pragma once
#include "Camera/CCamera.h"		
#include "Asset/SoundManager/CSoundManager.h"
#include "Asset/CAssetManager/CAssetManager.h"

/**************************************************
*	ゲームオブジェクトクラス.
*	ゲーム内オブジェクトの基底クラス
**/
class CGameObject
{
public:
	//コンストラクタ
	CGameObject();
	//デストラクタ
	virtual ~CGameObject() {};
	//更新関数
	virtual void Update() = 0;
	//描画関数
	virtual void Draw(const CCamera*pCamera) = 0;
	//座標取得
	const D3DXVECTOR3& GetPosition() const
	{
		return m_vPosition;
	}
	//座標を設定
	void SetPosition( float x, float y, float z )
	{
		m_vPosition.x = x;
		m_vPosition.y = y;
		m_vPosition.z = z;
	};
	//座標を設定
	void SetPosition(const D3DXVECTOR3& pos) 
	{
		m_vPosition = pos;
	}
	// 回転角度を取得
	const D3DXVECTOR3& GetRotation() const
	{
		return m_vRotation;
	}
	// 回転角度を設定
	void SetRotation( float x, float y, float z )
	{
		m_vRotation.x = x;
		m_vRotation.y = y;
		m_vRotation.z = z;
	};
	// 回転角度を設定
	void SetRotation(const D3DXVECTOR3& rot) 
	{
		m_vRotation = rot;
	}
	//拡縮を取得
	const D3DXVECTOR3& GetScale() const
	{
		return m_vScale;
	}
	//拡縮を設定
	void SetScale( float x, float y, float z )
	{
		m_vScale.x = x;
		m_vScale.y = y;
		m_vScale.z = z;
	}
	//拡縮を設定
	void SetScale(float xyz) 
	{
		m_vScale = D3DXVECTOR3(xyz, xyz, xyz);
	}
	//クオータニオンを取得
	D3DXQUATERNION GetQuaternion() const 
	{
		return m_vQuaternion; 
	};
	//クオータニオンを設定
	void SetQuaternion(D3DXQUATERNION Quaternion) 
	{
		m_vQuaternion = Quaternion;
	}
	//IDを取得
	int  GetID()const { return m_ID; }
	//IDを設定
	void SetID( int id ) { m_ID = id; }
	// ワールド変換行列を取得
	const D3DXMATRIX& GetWorldMatrix() const;

protected:
	D3DXVECTOR3    m_vPosition;    // 座標
	D3DXVECTOR3    m_vRotation;    // 回転角度
	D3DXVECTOR3    m_vScale;       // 拡大縮小率
	D3DXQUATERNION m_vQuaternion;  // クォータニオン

	int            m_ID;           // ID
	float          m_Count;        // カウント

	mutable D3DXMATRIX m_WorldTrans; // ワールド変換行列

};