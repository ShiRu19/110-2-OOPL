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