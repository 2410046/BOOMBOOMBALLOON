#include "CEffect.h"
#include "DirectX/CDirectX11.h"
//描画スプライト最大数
constexpr int RENDER_SPRITE_MAX = 8000;
//エフェクト管理用インスタンス最大数
constexpr int EFFECT_INSTANCE_MAX = 1000;

CEffect::CEffect()
	: m_pManager	( nullptr )
	, m_pRenderer	( nullptr )

	, m_pEffect		()
{
}

CEffect::~CEffect()
{
	//エフェクトデータの破棄
	ReleaseData();

	//エフェクトのマネージャーを破棄
	m_pManager.Reset();

	//エフェクトのレンダラーを破棄
	m_pRenderer.Reset();
}

//構築
HRESULT CEffect::Create()
{
	//エフェクトのマネージャーの作成
	m_pManager = ::EsManager::Create(RENDER_SPRITE_MAX);

	//エフェクトのレンダラーの作成
	m_pRenderer = ::EsRenderer::Create(
		CDirectX11::GetDevice(), CDirectX11::GetContext(), EFFECT_INSTANCE_MAX);

	//描画モジュールの設定
	m_pManager->SetSpriteRenderer(m_pRenderer->CreateSpriteRenderer());
	m_pManager->SetRibbonRenderer(m_pRenderer->CreateRibbonRenderer());
	m_pManager->SetRingRenderer(m_pRenderer->CreateRingRenderer());
	m_pManager->SetTrackRenderer(m_pRenderer->CreateTrackRenderer());
	m_pManager->SetModelRenderer(m_pRenderer->CreateModelRenderer());

	//テクスチャ、モデル、マテリアルローダーの設定をする。
	//ユーザーが独自に拡張できる。現在はファイルから読み込んでいる。
	m_pManager->SetTextureLoader(m_pRenderer->CreateTextureLoader());
	m_pManager->SetModelLoader(m_pRenderer->CreateModelLoader());
	m_pManager->SetMaterialLoader(m_pRenderer->CreateMaterialLoader());
	m_pManager->SetCurveLoader(::Es::MakeRefPtr<::Es::CurveLoader>());

	return S_OK;
}

//データ読み込み
HRESULT CEffect::LoadData()
{
	struct EffectList
	{
		enList listNo;				//enList列挙型を設定
		const char16_t path[256];	//ファイルの名前(パス付き)
	};

	EffectList EList[] =
	{
		//u""は、UTF-16エンコーディングの文字列リテラルで、const char16_t* に代入可能
		{ enList::DeleteA,	u"Data\\Effekseer\\deleteA.efk"	},
		{ enList::DeleteB,	u"Data\\Effekseer\\deleteB.efk"	},
		{ enList::DeleteX,	u"Data\\Effekseer\\deleteX.efk"	},
		{ enList::DeleteY,	u"Data\\Effekseer\\deleteY.efk"	},
		{ enList::AppA,		u"Data\\Effekseer\\AppA.efk"	},
		{ enList::AppB,		u"Data\\Effekseer\\AppB.efk"	},
		{ enList::AppX,		u"Data\\Effekseer\\AppX.efk"	},
		{ enList::AppY,		u"Data\\Effekseer\\AppY.efk"	},
	};
	//配列の最大要素数を算出（配列全体のサイズ／配列１つ分のサイズ）
	int list_max = sizeof(EList) / sizeof(EList[0]);
	for (int i = 0; i < list_max; i++)
	{
		int listNo = EList[i].listNo;
		//エフェクトの読み込み
		m_pEffect[listNo] =
			::EsEffect::Create( m_pManager, EList[i].path);

		if (m_pEffect[listNo] == nullptr) {
			_ASSERT_EXPR(false, L"CEffect::LoadData()");
			return E_FAIL;
		}
	}

	return S_OK;
}

//描画
void CEffect::Draw(
	const CCamera*pCamera)
{
	if (m_pRenderer == nullptr || m_pManager == nullptr)
		return;

	//ビュー行列を設定
	SetViewMatrix(pCamera->GetView());

	//プロジェクション行列を設定
	SetProjectionMatrix(pCamera->GetProj());

	//レイヤーパラメータ設定
	::EsManager::LayerParameter layerParameter{};
	const D3DXVECTOR3 CameraPos = pCamera->GetCamera().vPosition;
	layerParameter.ViewerPosition = ToEfkVector3(&CameraPos);
	m_pManager->SetLayerParameter(0, layerParameter);

	//エフェクトの更新処理.
	m_pManager->Update();
	//-------------------------
	// Effekseerレンダリング
	//-------------------------
	//エフェクトの描画開始処理を行う
	m_pRenderer->BeginRendering();

	//エフェクトの描画を行う
	m_pManager->Draw();

	//エフェクトの描画終了処理を行う
	m_pRenderer->EndRendering();
}
//再生
::EsHandle CEffect::Play(enList list, const D3DXVECTOR3& pos)
{
	CEffect* pE = CEffect::GetInstance();
	return pE->m_pManager->Play(pE->m_pEffect[list], pos.x, pos.y, pos.z);
}
//停止
void CEffect::Stop(::EsHandle handle)
{
	CEffect::GetInstance()->m_pManager->StopEffect(handle);
}
//全て停止
void CEffect::StopAll()
{
	CEffect::GetInstance()->m_pManager->StopAllEffects();
}
//一時停止
void CEffect::Paused(::EsHandle handle, bool paused)
{
	CEffect::GetInstance()->m_pManager->SetPaused(handle, paused);
}
//再生速度の設定
void CEffect::SetSpeed(::EsHandle handle, float speed)
{
	CEffect::GetInstance()->m_pManager->SetSpeed(handle, speed);
}
//位置を指定する
void CEffect::SetLocation(::EsHandle handle, D3DXVECTOR3 pos)
{
	CEffect::GetInstance()->m_pManager->
		SetLocation(handle, ::EsVec3(pos.x, pos.y, pos.z));
}
//回転を指定する
void CEffect::SetRotation(::EsHandle handle, D3DXVECTOR3 rot)
{
	CEffect::GetInstance()->m_pManager->
		SetRotation(handle, rot.x, rot.y, rot.z);
}
//回転を指定する（軸回転）
void CEffect::SetRotationY(::EsHandle handle, D3DXVECTOR3 vAxis, float angle)
{
	CEffect::GetInstance()->m_pManager->
		SetRotation(handle, ::EsVec3(vAxis.x, vAxis.y, vAxis.z), angle);
}
//サイズを指定する
void CEffect::SetScale(::EsHandle handle, D3DXVECTOR3 scale)
{
	CEffect::GetInstance()->m_pManager->
		SetScale(handle, scale.x, scale.y, scale.z);
}

//DirectX Vector3 を Effekseer Vector3 に変換する
::EsVec3 CEffect::ToEfkVector3(const D3DXVECTOR3* pSrcVec3Dx)
{
	return ::EsVec3(pSrcVec3Dx->x, pSrcVec3Dx->y, pSrcVec3Dx->z);
}

//Effekseer Vector3 を DirectX Vector3 に変換する
D3DXVECTOR3 CEffect::ToDxVector3(const::EsVec3* pSrcVec3Efk)
{
	return D3DXVECTOR3(pSrcVec3Efk->X, pSrcVec3Efk->Y, pSrcVec3Efk->Z);
}

//DirectX Matrix を Effekseer Matrix に変換する
::EsMatrix CEffect::ToEfkMatrix(const D3DXMATRIX* pSrcMatDx)
{
	::EsMatrix OutMatEfk;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			OutMatEfk.Values[i][j] = pSrcMatDx->m[i][j];
		}
	}
	return OutMatEfk;
}

D3DXMATRIX CEffect::ToDxMatrix(const::EsMatrix* pSrcMatEfk)
{
	D3DXMATRIX OutMatDx;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			OutMatDx.m[i][j] = pSrcMatEfk->Values[i][j];
		}
	}
	return OutMatDx;
}

//データ解放
HRESULT CEffect::ReleaseData()
{
	return S_OK;
}

//ビュー行列を設定
void CEffect::SetViewMatrix(const D3DXMATRIX& mView)
{
	::EsMatrix EsCamMat;	//カメラ行列
	EsCamMat = ToEfkMatrix(&mView);

	//カメラ行列を設定
	m_pRenderer->SetCameraMatrix(EsCamMat);
}

//プロジェクション行列を設定
void CEffect::SetProjectionMatrix(const D3DXMATRIX& mProj)
{
	::EsMatrix EsProjMat;	//プロジェクション行列
	EsProjMat = ToEfkMatrix(&mProj);

	//プロジェクション行列を設定
	m_pRenderer->SetProjectionMatrix(EsProjMat);
}