#include "CSelectText.h"
#if 1
// 押した瞬間だけ
bool KeyTrigger(int vk)
{
	static std::unordered_map<int, bool> prev = {};
	bool pressed = (GetAsyncKeyState(vk) & 0x8000) != 0;
	bool triggered = pressed && !prev[vk];
	prev[vk] = pressed;
	return triggered;
}
//選択肢の設定
void Selecter(int& No, int MaxNo, bool& StartFlag, bool VK)
{
	// 選択不可 or 既に決定済みなら処理しない
	if (MaxNo <= 0 || StartFlag) return;
	// パッド取得（プレイヤー0）
	CXInput* pPad = CXInput::GetInstance(0);
	// 入力状態
	bool MovePrev = false;
	bool MoveNext = false;
	// 入力方向切り替え（フラグに応じて操作方向変更）
		if (VK)
		{
			// 左右入力（横移動）
			MovePrev = KeyTrigger(VK_LEFT) || pPad->IsDown(CXInput::KEY::LEFT, true);
			MoveNext = KeyTrigger(VK_RIGHT) || pPad->IsDown(CXInput::KEY::RIGHT, true);
		}
		else
		{
			// 上下入力（縦移動）
			MovePrev = KeyTrigger(VK_UP) || pPad->IsDown(CXInput::KEY::UP, true);
			MoveNext = KeyTrigger(VK_DOWN) || pPad->IsDown(CXInput::KEY::DOWN, true);
		}

   //if (pPad->Update())
   //{

	   // 左（または上）入力：前の要素へ（ループ）
		if (MovePrev)
		{
			No = (No - 1 + MaxNo) % MaxNo;
		}
		// 右（または下）入力：次の要素へ（ループ）
		if (MoveNext)
		{
			No = (No + 1) % MaxNo;
		}

		// Bボタンで決定
		if (KeyTrigger(VK_RETURN) || pPad->IsDown(CXInput::KEY::B, true))
		{
			StartFlag = true;
		}
	//}
#else
void Selecter(int& No, int MaxNo, bool& StartFlag, bool VK)
{
	// 選択不可 or 既に決定済みなら処理しない
		if (MaxNo <= 0 || StartFlag) return;
		// パッド取得（プレイヤー0）
		CXInput* pPad = CXInput::GetInstance(0);
		// 入力状態
		bool MovePrev = false;
		bool MoveNext = false;
		// 入力方向切り替え（フラグに応じて操作方向変更）
		if (VK == true)
		{
			// 左右入力（横移動）
			MovePrev = pPad->IsDown(CXInput::KEY::LEFT, true);
			MoveNext = pPad->IsDown(CXInput::KEY::RIGHT, true);
		}
		else
		{
			// 上下入力（縦移動）
			MovePrev = pPad->IsDown(CXInput::KEY::UP, true);
			MoveNext = pPad->IsDown(CXInput::KEY::DOWN, true);
		}

		if (pPad->Update())
		{
			// 左（または上）入力：前の要素へ（ループ）
			if (MovePrev)
			{
				No = (No - 1 + MaxNo) % MaxNo;
			}
			// 右（または下）入力：次の要素へ（ループ）
			if (MoveNext)
			{
				No = (No + 1) % MaxNo;
			}

			// Bボタンで決定
			if (pPad->IsDown(CXInput::KEY::B, true))
			{
				StartFlag = true;
			}
		}
#endif
}



