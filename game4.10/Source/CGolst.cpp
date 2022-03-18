#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGolst.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CElf: Elf class
	/////////////////////////////////////////////////////////////////////////////

	// Elf
	CGolst::CGolst() {
		x = y = 0;
	}

	void CGolst::OnMove() {

	}

	void CGolst::LoadBitmapA(int IDB) {
		pic.LoadBitmapA(IDB, RGB(0, 0, 0));
	}

	void CGolst::SetTopLeft(int x, int y) {
		pic.SetTopLeft(x, y);
	}

	void CGolst::OnShow() {
		//pic.SetTopLeft(x, y);
		pic.ShowBitmap();
	}
}