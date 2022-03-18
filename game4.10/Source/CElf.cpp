#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CElf.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CElf: Elf class
	/////////////////////////////////////////////////////////////////////////////

	// Elf
	CElf::CElf() {
		x = y = 0;
	}

	void CElf::OnMove() {

	}

	void CElf::LoadBitmapA(int IDB) {
		pic.LoadBitmapA(IDB, RGB(0, 0, 0));
	}

	void CElf::SetTopLeft(int x, int y) {
		pic.SetTopLeft(x, y);
	}

	void CElf::OnShow() {
		//pic.SetTopLeft(x, y);
		pic.ShowBitmap();
	}
}