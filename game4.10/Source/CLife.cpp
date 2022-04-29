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
		// Life�w�]��1���
		myLife = CInteger(1);
		// �w�]��4
		myLife.SetInteger(4);
	}

	void CLife::LoadBitmap() {
		for (int i = 0; i < 4; i++) {
			Pacman_icon[i].LoadBitmap(IDB_PACMAN_RIGHT_1, RGB(125, 125, 125));
		}
		Life_multi.LoadBitmap(IDB_LIFEMULTI, RGB(0, 0, 0));
		myLife.LoadBitmap();
	}

	void CLife::OnShow() {
		for (int i = 0; i < myLife.GetInteger(); i++) {
			Pacman_icon[i].ShowBitmap();
		}
		Life_multi.ShowBitmap();
		myLife.ShowBitmap();
	}

	void CLife::SetTopLeft() {
		for (int i = 0; i < 4; i++) {
			Pacman_icon[i].SetTopLeft(800 + 25*i, 360);
		}
		Life_multi.SetTopLeft(800, 400);
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