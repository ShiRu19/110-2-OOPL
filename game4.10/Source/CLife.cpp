#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CLife.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CLife::CLife()
	{
		// Life預設為1位數
		myLife = CInteger(1);
		// 預設為4
		myLife.SetInteger(4);
	}

	void CLife::LoadBitmap() {
		LIFE_multi.LoadBitmap(IDB_LIFEMULTI, RGB(0, 0, 0));
		myLife.LoadBitmap();
	}

	void CLife::OnShow() {
		LIFE_multi.ShowBitmap();
		myLife.ShowBitmap();
	}

	void CLife::SetTopLeft() {
		LIFE_multi.SetTopLeft(800, 400);
		myLife.SetTopLeft(830, 400);
	}
	
	void CLife::setLife(int life) {
		myLife.SetDigits(1);
		myLife.SetInteger(life);
	}
	
	int CLife::getLife() {
		return myLife.GetInteger();
	}
	
}