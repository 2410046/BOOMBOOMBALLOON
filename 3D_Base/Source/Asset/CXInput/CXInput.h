#pragma once

#include <Windows.h>
#include <Xinput.h>
#include <array>
#pragma comment( lib, "xinput.lib" )

/********************************************************************************
*   XInputクラス.(コントローラー)
**/
class CXInput
{
public:

	//インスタンス取得(唯一のアクセス経路).
	//※関数の前にstaticを付けることでインスタンス生成しなくても使用できる.
	// padIdごとにインスタンス取得
	static CXInput* GetInstance(DWORD padId)
	{
		if (padId >= 2) return nullptr;

		if (!s_instances[padId])
			s_instances[padId] = new CXInput(padId);

		return s_instances[padId];
	}

	// すべてのインスタンスを破棄（アプリ終了時に呼ぶ）
	static void DestroyAll()
	{
		for (auto& inst : s_instances)
		{
			delete inst;
			inst = nullptr;
		}
	}
public:
	//--------------------.
	//	定数宣言.
	//--------------------.
	//トリガー入力範囲.
	static const BYTE	TRIGGER_MIN		= 0;
	static const BYTE	TRIGGER_MAX		= 255;
	//スティック入力範囲.
	static const SHORT	THUMB_MIN		=-32768;
	static const SHORT	THUMB_MAX		= 32767;
	//バイブレーション値範囲.
	static const WORD	VIBRATION_MIN	= 0;
	static const WORD	VIBRATION_MAX	= 65535;

	//キー列挙体.
	enum KEY
	{
		UP,		//方向パッド:上.
		DOWN,	//方向パッド:下.
		LEFT,	//方向パッド:左.
		RIGHT,	//方向パッド:右.
		START,	//ボタン:スタート.
		BACK,	//ボタン:バック.
		LSTICK,	//ボタン:左スティック.
		RSTICK,	//ボタン:右スティック.
		LB,		//ボタン:LB.
		RB,		//ボタン:RB.
		A,		//ボタン:A.
		B,		//ボタン:B.
		X,		//ボタン:X.
		Y,		//ボタン:Y.

		MAX,
		FIRST	= UP,
		LAST	= Y,
	};

public:
	//コンストラクタ.
	CXInput( DWORD padId );
	//デストラクタ.
	~CXInput();

	//キー入力の更新.
	bool Update();
	//終了処理.
	void EndProc();

	//--------------------------------------.
	//	キー入力の状態を細かく取得する.
	//--------------------------------------.
	//押した.
	bool IsDown( KEY key, bool Just = false );
	//離した.
	bool IsUp( KEY key );
	//押し続けている.
	bool IsRepeat( KEY key );

	//左トリガー取得.
	BYTE GetLTrigger() const {	return m_state.Gamepad.bLeftTrigger;	}
	//右トリガー取得.
	BYTE GetRTrigger() const {	return m_state.Gamepad.bRightTrigger;	}

	//左スティックX軸取得.
	SHORT GetLThumbX() const {	return m_state.Gamepad.sThumbLX;		}
	//左スティックY軸取得.
	SHORT GetLThumbY() const {	return m_state.Gamepad.sThumbLY;		}

	//右スティックX軸取得.
	SHORT GetRThumbX() const {	return m_state.Gamepad.sThumbRX;		}
	//右スティックY軸取得.
	SHORT GetRThumbY() const {	return m_state.Gamepad.sThumbRY;		}

	//振動設定.
	bool SetVibration( WORD LMotorSpd, WORD RMotorSpd );

	//接続チェック.
	bool IsConnect() const	{	return m_connect;	}
	//パッド番号取得.
	DWORD GetPadID() const	{	return m_padId;		}

	//コントローラーが接続されているか
	bool IsControllerConnected(int no);
private:
	//キー入力の更新.
	bool UpdateStatus();
	//IsDown,IsUp,IsRepeat関数内で使用する関数.
	bool IsKeyCore( WORD GamePad, const XINPUT_STATE& State );
	//KEY列挙体を対応したXINPUT_GAMEPADの値に変換.
	WORD GenerateGamePadValue( KEY key );

private:
	
	DWORD               m_padId;		//パッド番号(0~3).
	XINPUT_STATE        m_state;		//キー入力情報.
	XINPUT_STATE		m_stateOld;		//キー入力情報(キーストローク判定用).
	XINPUT_VIBRATION    m_vibration;	//振動.
	bool				m_connect;		//接続判定.
	// 静的インスタンス格納（4PAD分）
	static  std::array<CXInput*, 2> s_instances;
};
