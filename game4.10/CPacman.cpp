#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPacman.h"

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// 以下class為角色物件
	/////////////////////////////////////////////////////////////////////////////

	// PacMan
	CPacMan::CPacMan() {
		x = y = 0;
	}

	void CPacMan::OnMove() {
		
	}

	void CPacMan::LoadBitmapA() {
		pic.LoadBitmapA(IDB_PACMAN);
	}

	void CPacMan::OnShow() {
		pic.SetTopLeft(x, y);
		pic.ShowBitmap();
	}

	// Elf
	CElf::CElf() {
		x = 300;
		y = 200;
	}

	void CElf::LoadBitmapA(int IDB) {
		pic.LoadBitmapA(IDB, RGB(0, 0, 0));
	}

	void CElf::OnMove() {

	}

	void CElf::OnShow() {
		pic.SetTopLeft(x, y);
		pic.ShowBitmap();
	}
}