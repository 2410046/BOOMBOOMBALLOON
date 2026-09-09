#pragma once
#include "Asset/CXInput/CXInput.h"
#include "CGameObject/CSpriteObject/CFade/CFade.h"
#include <vector>
#include <unordered_map>
#include <Windows.h>

// 押した瞬間だけ true
bool KeyTrigger(int vk);

//選択肢の設定
void Selecter(
	int& No, int MaxNo, bool& StartFlag, bool VK = false);