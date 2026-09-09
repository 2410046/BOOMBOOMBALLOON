#pragma once
#include "CCamera.h"
#include "Singleton.h"
//警告についてのコード分析を無効にする。4005:再定義
#pragma warning(disable:4005)

//---------------------------------------
// Effekseer関係ヘッダ、ライブラリ
//---------------------------------------
#include "Effekseer.h"
#include "EffekseerRendererDX11.h"

#ifdef _DEBUG
	#pragma comment(lib,"Effekseerd.lib")
	#pragma comment(lib,"EffekseerRendererDX11d.lib")
#else//#ifdef _DEBUG
	#pragma comment(lib,"Effekseer.lib")
	#pragma comment(lib,"EffekseerRendererDX11.lib")
#endif//#ifdef _DEBUG

//エイリアスを用意
//※コードが横に長くなって読みづらいため
namespace {
	namespace Es = ::Effekseer;
	using EsManagerRef	= ::Es::ManagerRef;
	using EsManager		= ::Es::Manager;
	using EsEffectRef	= ::Es::EffectRef;
	using EsEffect		= ::Es::Effect;
	using EsVec3		= ::Es::Vector3D;
	using EsMatrix		= ::Es::Matrix44;
	using EsHandle		= ::Es::Handle;
	using EsRendererRef = ::EffekseerRendererDX11::RendererRef;
	using EsRenderer	= ::EffekseerRendererDX11::Renderer;
};

/**************************************************
*	フリーソフト Effekseerのデータを使うためのクラス
*	singleton(シングルトン：デザインパターンの１つ)で作成
**/
class CEffect
	: public Singleton<CEffect>
{
public:
	////エフェクト種類列挙型
	enum enList
	{
		DeleteA,			//音符Aで使用
		DeleteB,			//音符Bで使用
		DeleteX,			//音符Xで使用
		DeleteY,			//音符Yで使用
		AppA,
		AppB,
		AppX,
		AppY,
		Max				//最大数

	};
private:
	friend class Singleton<CEffect>;
	CEffect();
public:
	~CEffect();
	//構築
	HRESULT Create();
	//データ読み込み
	HRESULT LoadData();
	void Draw(const CCamera* pCamera);

	//-----------------------------------
	// 変換系
	//-----------------------------------
	//ベクター
	::EsVec3 ToEfkVector3(const D3DXVECTOR3* pSrcVec3Dx);
	D3DXVECTOR3 ToDxVector3(const ::EsVec3* pSrcVec3Efk);
	//行列
	::EsMatrix ToEfkMatrix(const D3DXMATRIX* pSrcMatDx);
	D3DXMATRIX ToDxMatrix(const ::EsMatrix* pSrcMatEfk);

	//-----------------------------------
	// 制御系
	//-----------------------------------
	//再生
	static ::EsHandle Play(enList listNo, const D3DXVECTOR3& pos);
	//停止
	static void Stop(::EsHandle handle);
	//全て停止
	static void StopAll();
	//一時停止
	static void Paused(::EsHandle handle, bool paused);
	//再生速度の設定
	static void SetSpeed(::EsHandle handle, float speed);
	//位置を指定する
	static void SetLocation(::EsHandle handle, D3DXVECTOR3 pos);
	//回転を指定する
	static void SetRotation(::EsHandle handle, D3DXVECTOR3 rot);
	//回転を指定する（軸回転）
	static void SetRotationY(::EsHandle handle, D3DXVECTOR3 vAxis, float angle);
	//サイズを指定する
	static void SetScale(::EsHandle handle, D3DXVECTOR3 scale);
private:
	//データ解放
	HRESULT ReleaseData();

	//ビュー行列を設定
	void SetViewMatrix(const D3DXMATRIX& mView);
	//プロジェクション行列を設定
	void SetProjectionMatrix(const D3DXMATRIX& mProj);

private:
	//エフェクトを動作させるために必要
	::EsManagerRef		m_pManager;
	::EsRendererRef		m_pRenderer;
	//エフェクトの種類ごとに必要
	::EsEffectRef		m_pEffect[enList::Max];
	//エフェクトの種類ごとに必要
	//std::unordered_map<std::string, ::EsEffectRef> m_pEffect;
};

