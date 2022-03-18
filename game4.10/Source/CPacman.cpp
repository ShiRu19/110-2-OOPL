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
		pic.LoadBitmapA(IDB_PACMAN_1);
	}

	void CPacman::OnShow() {
		pic.SetTopLeft(x, y);
		pic.ShowBitmap();
	}
}