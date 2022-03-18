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
		x = y = 100;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CPacman::OnMove() {
		const int STEP_SIZE = 2;
		//animation.OnMove();
		if (isMovingLeft)
			x -= STEP_SIZE;
		if (isMovingRight)
			x += STEP_SIZE;
		if (isMovingUp)
			y -= STEP_SIZE;
		if (isMovingDown)
			y += STEP_SIZE;
	}

	void CPacman::SetMovingUp(bool flag)
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isMovingUp = flag;
	}

	void CPacman::SetMovingDown(bool flag)
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isMovingDown = flag;
	}

	void CPacman::SetMovingLeft(bool flag)
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isMovingLeft = flag;
	}

	void CPacman::SetMovingRight(bool flag)
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isMovingRight = flag;
	}

	void CPacman::LoadBitmapA() {
		pic.LoadBitmapA(IDB_PACMAN);
	}

	int CPacman::get_x() {
		return x;
	}

	int CPacman::get_y() {
		return y;
	}

	void CPacman::SetTopLeft() {
		pic.SetTopLeft(x, y);
	}

	void CPacman::OnShow() {
		SetTopLeft();
		pic.ShowBitmap();
	}
}