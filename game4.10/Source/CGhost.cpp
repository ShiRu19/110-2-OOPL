#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGhost.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CGolst: Golst class
	/////////////////////////////////////////////////////////////////////////////

	// Golst
	CGhost::CGhost() {
		x = y = 0;
	}

	void CGhost::OnMove() {
		animation->OnMove();
	}

	void CGhost::LoadBitmap(int IDB[4][2]) {
		// up
		animation_1.AddBitmap(IDB[0][0], RGB(0, 0, 0));
		animation_1.AddBitmap(IDB[0][1], RGB(0, 0, 0));

		// down
		animation_2.AddBitmap(IDB[1][0], RGB(0, 0, 0));
		animation_2.AddBitmap(IDB[1][1], RGB(0, 0, 0));

		// left
		animation_3.AddBitmap(IDB[2][0], RGB(0, 0, 0));
		animation_3.AddBitmap(IDB[2][1], RGB(0, 0, 0));

		// right
		animation_4.AddBitmap(IDB[3][0], RGB(0, 0, 0));
		animation_4.AddBitmap(IDB[3][1], RGB(0, 0, 0));

		// 躲避鬼
		animation_avoid.AddBitmap(IDB_GHOST_BLUE_1, RGB(0, 0, 0));
		animation_avoid.AddBitmap(IDB_GHOST_BLUE_2, RGB(0, 0, 0));

		// 不穩定鬼 (躲避鬼變正常鬼間的不穩定狀態)
		animation_change.AddBitmap(IDB_GHOST_BLUE_1, RGB(0, 0, 0));
		animation_change.AddBitmap(IDB_GHOST_WHITE_2, RGB(0, 0, 0));

		// 眼睛
		animation_eyes.AddBitmap(IDB_GHOST_EYES_DOWN, RGB(0, 0, 0));
	}
	
	//
	// 切換鬼的狀態
	// 0 => 眼睛 to 正常鬼
	// 1 => 正常鬼 to 躲避鬼
	// 2 => 躲避鬼 to 不穩定鬼
	// 3 => 不穩定鬼 to 眼睛
	//
	void CGhost::changeMode(int mode) {
		if (mode == 0) animation = &animation_4;           // 正常鬼
		else if (mode == 1) animation = &animation_avoid;  // 躲避鬼
		else if (mode == 2) animation = &animation_change; // 不穩定鬼
		else if (mode == 3) animation = &animation_eyes;   // 眼睛
	}

	bool CGhost::isNormalMode() {
		if (animation == &animation_avoid || animation == &animation_change || animation == &animation_eyes) {
			return false;
		}
		return true;
	}

	int CGhost::GetX1() {
		return x;
	}
	
	int CGhost::GetY1() {
		return y;
	}

	int CGhost::GetX2() {
		return x + animation->Width();
	}

	int CGhost::GetY2() {
		return y + animation->Height();
	}

	void CGhost::SetTopLeft(int x, int y) {
		animation->SetTopLeft(x, y);
		this->x = x;
		this->y = y;
	}

	void CGhost::OnShow() {
		animation->SetTopLeft(x,y);
		animation->OnShow();
	}
}