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
		animation->OnMove();
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
		animation = &animation_1;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isMovingUp = flag;
		LoadBitmap();
	}

	void CPacman::SetMovingDown(bool flag)
	{
		animation = &animation_2;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isMovingDown = flag;
	}

	void CPacman::SetMovingLeft(bool flag)
	{
		animation = &animation_3;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isMovingLeft = flag;
	}

	void CPacman::SetMovingRight(bool flag)
	{
		animation = &animation_4;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isMovingRight = flag;
		LoadBitmap();
	}

	void CPacman::LoadBitmap() {
		animation_0.AddBitmap(IDB_PACMAN_RIGHT_1, RGB(255, 255, 255));          //�R��A(�w�]�V�k)
		// UP
		animation_1.AddBitmap(IDB_PACMAN_UP_1, RGB(255, 255, 255));             //�V�W_open
		animation_1.AddBitmap(IDB_PACMAN_UP_2, RGB(255, 255, 255));             //�V�W_close
		// DOWN
		animation_2.AddBitmap(IDB_PACMAN_DOWN_1, RGB(255, 255, 255));           //�V�U_open
		animation_2.AddBitmap(IDB_PACMAN_DOWN_2, RGB(255, 255, 255));           //�V�U_close
		// LEFT
		animation_3.AddBitmap(IDB_PACMAN_LEFT_1, RGB(255, 255, 255));           //�V��_open
		animation_3.AddBitmap(IDB_PACMAN_LEFT_2, RGB(255, 255, 255));           //�V��_close
		// RIGHT
		animation_4.AddBitmap(IDB_PACMAN_RIGHT_1, RGB(255, 255, 255));          //�V�k_open
		animation_4.AddBitmap(IDB_PACMAN_RIGHT_2, RGB(255, 255, 255));          //�V�k_close
	}

	int CPacman::get_x() {
		return x;
	}

	int CPacman::get_y() {
		return y;
	}

	void CPacman::SetTopLeft() {
		animation->SetTopLeft(x, y);
	}

	void CPacman::OnShow() {
		animation->SetTopLeft(x, y);
		animation->OnShow();
	}
}