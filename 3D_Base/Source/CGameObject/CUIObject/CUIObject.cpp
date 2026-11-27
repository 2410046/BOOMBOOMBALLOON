#include "CUIObject.h"
#include <algorithm>

//コンストラクタ
CUIObject::CUIObject()
	: m_pSprite		( nullptr )
	, m_PatternNo	()
	, m_Alpha		( 1.f )
	, m_Patten		( 0 )
	, m_NumberCount	( 0 )
{
}
//デストラクタ
CUIObject::~CUIObject()
{
	//スプライトを切り離す
	DetachSprite();
}
//更新関数
void CUIObject::Update()
{
	// スプライトが接続されていない場合は更新しない
	if( m_pSprite == nullptr ){
		return;
	}
}
//描画関数
void CUIObject::Draw()
{
	// スプライトが接続されていない場合は描画しない
	if( m_pSprite == nullptr ){
		return;
	}

	//描画直前で座標や回転情報などを設定
	m_pSprite->SetPosition( m_vPosition );
	m_pSprite->SetRotation( m_vRotation );
	m_pSprite->SetScale( m_vScale );
	m_pSprite->SetAlpha(m_Alpha);
	
	//パターン番号を設定
	m_pSprite->SetPatternNo( m_PatternNo.x, m_PatternNo.y );

	// スプライトを描画
	m_pSprite->Render();
}
// カメラ付き描画処理
void CUIObject::Draw(
	const CCamera* pCamera)
{
	Draw();
}
//--------------------------------------
// 数字を描画
// value      : 表示する数値
// Space      : 数字同士の間隔
// digitCount : 表示する桁数
//--------------------------------------
void CUIObject::Number(int value, float Space, int digitCount)
{
	// スプライトの最大パターン数を取得
	const POINTS PatternMax = m_pSprite->GetPatternMax();
	// 数値を指定した桁数の文字列に変換
	char buf[16];
	char format[16];

	// 指定した桁数に合わせて先頭を0で埋める書式を作成
	sprintf_s(format, "%%0%dd", digitCount);
	sprintf_s(buf, format, value);

	// 数字を1桁ずつ取り出して描画
	for (int i = 0; i < digitCount; ++i)
	{
		// 文字列から数字を取得
		int digit = buf[i] - '0';

       // 数字に対応するスプライトのパターン番号を計算
		m_PatternNo.x = digit % PatternMax.x;
		m_PatternNo.y = m_Patten + (digit / PatternMax.x);
		//パターン番号を設定
		m_pSprite->SetPatternNo(m_PatternNo.x, m_PatternNo.y);
		
		// 描画位置を桁数に応じてずらす
		D3DXVECTOR3 pos = m_vPosition;
		pos.x += i * Space;

		// スプライトの拡縮と座標を設定
		m_pSprite->SetScale(m_vScale);
		m_pSprite->SetPosition(pos);

		// 描画
		m_pSprite->Render();
	}
}    
//--------------------------------------
//数字のカウントアニメーション
// TargetScore      : 目標数値
// DisplayScore     : 表示数値
//--------------------------------------
void CUIObject::CountUp(
	int targetScore, int& displayScore)
{
	// 表示スコアを更新する間隔
	constexpr int   Update_Interval = 5;    

	// 表示スコアの更新間隔をカウント
	m_NumberCount++;
	// 一定フレーム経過したら表示スコアを更新
	if (m_NumberCount >= Update_Interval)
	{
		// 更新カウンタをリセット
		m_NumberCount = 0;
		// 最終スコアと表示スコアの差を取得
		int diff = targetScore - displayScore;

		// 差分をもとに1ずつ増減させる
		int step = std::clamp(diff, -1, 1);

		// 表示スコアを更新
		displayScore += step;
	}
}

