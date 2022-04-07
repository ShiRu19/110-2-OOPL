#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGhost.h"
#include "CPacman.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CPacman: Pacman class
	/////////////////////////////////////////////////////////////////////////////

	// Pacman
	CPacman::CPacman() {
		y = MAP_START + 17 * BITMAP_SIZE;									// 設定Pacman起始的X座標
		x = MAP_START + 14 * BITMAP_SIZE;									// 設定Pacman起始的Y座標
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		is_alive = true;
	}

	void CPacman::OnMove(int **map) {
		if (!is_alive)
			return;

		const int STEP_SIZE = 2;
		animation->OnMove();
		if (isMovingLeft)
		{
			int MapIndex_Y = CPacman::FindMapIndex_Y();
			int MapIndex_X = CPacman::FindMapIndex_X();
			int wall_pixel = 0;
			while (true)
			{
				if (map[MapIndex_Y][MapIndex_X] == 1)
				{
					wall_pixel = MAP_START + BITMAP_SIZE * (MapIndex_X + 1);
					break;
				}
				else
				{
					MapIndex_X--;
				}
			}
			if (x - wall_pixel>STEP_SIZE)
			{
				x -= STEP_SIZE;
			}
			else
			{
				x = wall_pixel;
			}
		}
		if (isMovingRight)
		{
			int MapIndex_Y = CPacman::FindMapIndex_Y();
			int MapIndex_X = CPacman::FindMapIndex_X();
			int wall_pixel = 0;
			while (true)
			{
				if (map[MapIndex_Y][MapIndex_X] == 1)
				{
					wall_pixel = MAP_START + BITMAP_SIZE * (MapIndex_X - 1);
					break;
				}
				else
				{
					MapIndex_X++;
				}
			}
			if (wall_pixel-x>STEP_SIZE)
			{
				x += STEP_SIZE;
			}
			else
			{
				x = wall_pixel;
			}
		}
		if (isMovingUp)
		{
			int MapIndex_Y = CPacman::FindMapIndex_Y();
			int MapIndex_X = CPacman::FindMapIndex_X();
			int wall_pixel = 0;
			while (true)
			{
				if (map[MapIndex_Y][MapIndex_X] == 1)
				{
					wall_pixel = MAP_START + BITMAP_SIZE * (MapIndex_Y + 1);
					break;
				}
				else
				{
					MapIndex_Y--;
				}
			}
			if (y - wall_pixel> STEP_SIZE)
			{
				y -= STEP_SIZE;
			}
			else
			{
				y = wall_pixel;
			}
		}
		if (isMovingDown)
		{
			int MapIndex_Y = CPacman::FindMapIndex_Y();
			int MapIndex_X = CPacman::FindMapIndex_X();
			int wall_pixel = 0;
			while (true)
			{
				if (map[MapIndex_Y][MapIndex_X] == 1)
				{
					wall_pixel = MAP_START + BITMAP_SIZE * (MapIndex_Y - 1);
					break;
				}
				else
				{
					MapIndex_Y++;
				}
			}
			if (wall_pixel-y > STEP_SIZE)
			{
				y += STEP_SIZE;
			}
			else
			{
				y = wall_pixel;
			}
		}
	}

	void CPacman::SetMovingUp(bool flag)
	{
		animation = &animation_1;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isMovingUp = flag;
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
	}

	void CPacman::LoadBitmap() {
		// STOP
		animation_stop_1.AddBitmap(IDB_PACMAN_UP_1, RGB(255, 255, 255));        //靜止狀態(預設向上)
		animation_stop_2.AddBitmap(IDB_PACMAN_DOWN_1, RGB(255, 255, 255));      //靜止狀態(預設向下)
		animation_stop_3.AddBitmap(IDB_PACMAN_LEFT_1, RGB(255, 255, 255));      //靜止狀態(預設向左)
		animation_stop_4.AddBitmap(IDB_PACMAN_RIGHT_1, RGB(255, 255, 255));     //靜止狀態(預設向右)

		// DIE
		animation_die.AddBitmap(IDB_PACMAN_UP_1, RGB(255, 255, 255));           //死亡(向上)
		animation_die.AddBitmap(IDB_PACMAN_DIE_1, RGB(255, 255, 255));
		animation_die.AddBitmap(IDB_PACMAN_DIE_2, RGB(255, 255, 255));
		animation_die.AddBitmap(IDB_PACMAN_DIE_3, RGB(255, 255, 255));
		animation_die.AddBitmap(IDB_PACMAN_DIE_4, RGB(255, 255, 255));
		animation_die.AddBitmap(IDB_PACMAN_DIE_BLACK, RGB(255, 255, 255));      //全黑結束

		// UP
		animation_1.AddBitmap(IDB_PACMAN_UP_1, RGB(255, 255, 255));             //向上_open
		animation_1.AddBitmap(IDB_PACMAN_UP_2, RGB(255, 255, 255));             //向上_close
		// DOWN
		animation_2.AddBitmap(IDB_PACMAN_DOWN_1, RGB(255, 255, 255));           //向下_open
		animation_2.AddBitmap(IDB_PACMAN_DOWN_2, RGB(255, 255, 255));           //向下_close
		// LEFT
		animation_3.AddBitmap(IDB_PACMAN_LEFT_1, RGB(255, 255, 255));           //向左_open
		animation_3.AddBitmap(IDB_PACMAN_LEFT_2, RGB(255, 255, 255));           //向左_close
		// RIGHT
		animation_4.AddBitmap(IDB_PACMAN_RIGHT_1, RGB(255, 255, 255));          //向右_open
		animation_4.AddBitmap(IDB_PACMAN_RIGHT_2, RGB(255, 255, 255));          //向右_close
	}

	// 檢查Pacman所構成的矩形是否碰到ghost
	bool CPacman::HitGhost(CGhost *ghost) {
		return HitRectangle(ghost->GetX1(), ghost->GetY1(),
			ghost->GetX2(), ghost->GetY2());
	}

	bool CPacman::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		// 檢查是否有交集
		return (tx2 >= x && tx1 <= (x + animation->Width()) && ty2 >= y && ty1 <= (y + animation->Height()));
	}

	void CPacman::SetIsAlive(bool alive) {
		is_alive = alive;
	}

	bool CPacman::IsAlive()
	{
		return is_alive;
	}

	int CPacman::GetX1()
	{
		return x;
	}

	int CPacman::GetY1()
	{
		return y;
	}

	int CPacman::GetX2()
	{
		return x + animation->Width();
	}

	int CPacman::GetY2()
	{
		return y + animation->Height();
	}

	void CPacman::SetTopLeft() {
		animation->SetTopLeft(x, y);
	}

	void CPacman::OnShow() {
		if (is_alive) {
			if (isMovingUp && y <= 0) {
				isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
				animation = &animation_stop_1;
			}
			else if (isMovingDown && y >= 900-animation->Height()) {
				isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
				animation = &animation_stop_2;
			}
			else if (isMovingLeft && x <= 0) {
				isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
				animation = &animation_stop_3;
			}
			else if (isMovingRight && x >= 1440-animation->Width()) {
				isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
				animation = &animation_stop_4;
			}

			animation->SetTopLeft(x, y);
			animation->OnShow();
		}
		else {
			animation = &animation_die;
			animation->SetTopLeft(x, y);
			animation->OnMove();
			animation->OnShow();
		}
	}

	int CPacman::FindMapIndex_X()
	{
		return (x - MAP_START) / BITMAP_SIZE;
	}
	int CPacman::FindMapIndex_Y()
	{
		return (y - MAP_START) / BITMAP_SIZE;
	}
}