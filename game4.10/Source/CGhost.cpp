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

	void CGhost::LoadBitmap(int IDB1, int IDB2) {
		animation->AddBitmap(IDB1, RGB(0, 0, 0));
		animation->AddBitmap(IDB2, RGB(0, 0, 0));
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