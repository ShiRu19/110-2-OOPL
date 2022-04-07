#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CLevel.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CLevel::CLevel()
	{
		myLevel = 0;
	}

	void CLevel::LoadBitmap() {
		LEVEL_text.LoadBitmap(IDB_LEVEL_TEXT, RGB(255, 255, 255));
	}

	void CLevel::OnShow() {
		LEVEL_text.ShowBitmap();
	}

	void CLevel::SetTopLeft() {
		LEVEL_text.SetTopLeft(800, 130);
	}
	
	void CLevel::setLevel(int LV) {
		myLevel += LV;
	}

	int CLevel::getLevel() {
		return myLevel;
	}
}