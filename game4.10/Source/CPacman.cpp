#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CPacman.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CPacman: Pacman class
	/////////////////////////////////////////////////////////////////////////////

	// Pacman
	CPacman::CPacman() {
		x = y = 0;
	}

	void CPacman::OnMove() {

	}

	void CPacman::LoadBitmapA() {
		pic.LoadBitmapA(IDB_PACMAN);
	}

	void CPacman::OnShow() {
		pic.ShowBitmap();
	}

	void CPacman::SetTopLeft(int x, int y) {
		pic.SetTopLeft(x, y);
	}
}