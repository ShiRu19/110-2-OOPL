#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGolst.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CGolst: Golst class
	/////////////////////////////////////////////////////////////////////////////

	// Golst
	CGolst::CGolst() {
		x = y = 0;
	}

	void CGolst::OnMove() {
		animation->OnMove();
	}

	void CGolst::LoadBitmap(int IDB1, int IDB2) {
		animation->AddBitmap(IDB1, RGB(0, 0, 0));
		animation->AddBitmap(IDB2, RGB(0, 0, 0));
	}

	void CGolst::SetTopLeft(int x, int y) {
		animation->SetTopLeft(x, y);
		this->x = x;
		this->y = y;
	}

	void CGolst::OnShow() {
		animation->SetTopLeft(x,y);
		animation->OnShow();
	}
}