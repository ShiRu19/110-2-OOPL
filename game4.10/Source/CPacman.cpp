#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGhost.h"
#include "CLife.h"
#include "CPacman.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CPacman: Pacman class
	/////////////////////////////////////////////////////////////////////////////

	// Pacman
	CPacman::CPacman() {
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		is_alive = true;
	}

	CPacman::~CPacman() {
		for (int i = 0; i < 31; i++)
		{
			delete[] map[i];
		}
		delete[] map;
	}

	void CPacman::SetInitXY(int x, int y) {
		init_X = MAP_START + x * BITMAP_SIZE;									// 設定Pacman起始的Y座標
		init_Y = MAP_START + y * BITMAP_SIZE;									// 設定Pacman起始的X座標
		this->x = init_X;
		this->y = init_Y;
	}

	void CPacman::LoadBitmap()
	{
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

	void CPacman::OnMove() {
		if (!is_alive)
			return;

		const int STEP_SIZE = 2;
		animation->OnMove();
		isStop = false;
		GetMapIndex();

		if (isMovingUp)
		{
			if (y - wall_pixel > STEP_SIZE) {
				y -= STEP_SIZE;
			}
			else {
				y = wall_pixel;
				isStop = true;
			}
		}
		else if (isMovingDown)
		{
			if (wall_pixel - y > STEP_SIZE) {
				y += STEP_SIZE;
			}
			else {
				y = wall_pixel;
				isStop = true;
			}
		}
		else if (isMovingLeft)
		{
			if (map[MapIndex_Y1][MapIndex_X1] == 4 && x == MAP_START + BITMAP_SIZE * (0)) {
				x = MAP_START + BITMAP_SIZE * (27);
				SetMovingLeft(true);
				return;
			}

			if (x - wall_pixel > STEP_SIZE) {
				x -= STEP_SIZE;
			}
			else {
				x = wall_pixel;
				isStop = true;
			}
		}
		else if (isMovingRight)
		{
			if (map[MapIndex_Y1][MapIndex_X1] == 4 && x == MAP_START + BITMAP_SIZE * (27)) {
				x = MAP_START + BITMAP_SIZE * (0);
				SetMovingRight(true);
				return;
			}

			if (wall_pixel - x > STEP_SIZE) {
				x += STEP_SIZE;
			}
			else {
				x = wall_pixel;
				isStop = true;
			}
		}
	}

	// 找座標在map陣列上的位置(X)
	int CPacman::FindMapIndex_X(int x)
	{
		return (x - MAP_START) / BITMAP_SIZE;
	}
	// 找座標在map陣列上的位置(Y)
	int CPacman::FindMapIndex_Y(int y)
	{
		return (y - MAP_START) / BITMAP_SIZE;
	}

	// 找Pacman四個點的陣列位置
	void CPacman::GetMapIndex() {
		MapIndex_X1 = FindMapIndex_X(x);         // 左
		MapIndex_X2 = FindMapIndex_X(x + 22);    // 右
		MapIndex_Y1 = FindMapIndex_Y(y);         // 上
		MapIndex_Y2 = FindMapIndex_Y(y + 22);    // 下
	}

	// 向上移動
	void CPacman::SetMovingUp(bool flag)
	{
		GetMapIndex();
		if (map[MapIndex_Y1 - 1][MapIndex_X1] != 1 && map[MapIndex_Y1 - 1][MapIndex_X2] != 1) {
			animation = &animation_1;
			isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
			isMovingUp = flag;

			// 計算向上終點牆的位置
			wall_pixel = 0;
			while (true)
			{
				if (map[MapIndex_Y1][MapIndex_X1] == 1)
				{
					wall_pixel = MAP_START + BITMAP_SIZE * (MapIndex_Y1 + 1);
					break;
				}
				else
					MapIndex_Y1--;
			}
		}
	}

	// 向下移動
	void CPacman::SetMovingDown(bool flag)
	{
		GetMapIndex();
		if (map[MapIndex_Y2 + 1][MapIndex_X1] != 1 && map[MapIndex_Y2 + 1][MapIndex_X2] != 1 && map[MapIndex_Y2 + 1][MapIndex_X1] != 2 && map[MapIndex_Y2 + 1][MapIndex_X2] != 2) {
			animation = &animation_2;
			isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
			isMovingDown = flag;

			// 計算向下終點牆的位置
			wall_pixel = 0;
			while (true)
			{
				if (map[MapIndex_Y1][MapIndex_X1] == 1)
				{
					wall_pixel = MAP_START + BITMAP_SIZE * (MapIndex_Y1 - 1);
					break;
				}
				else
					MapIndex_Y1++;
			}
		}
	}

	// 向左移動
	void CPacman::SetMovingLeft(bool flag)
	{
		GetMapIndex();
		if (map[MapIndex_Y1][MapIndex_X1-1] != 1 && map[MapIndex_Y2][MapIndex_X1-1] != 1) {
			animation = &animation_3;
			isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
			isMovingLeft = flag;

			// 計算向左終點牆的位置
			wall_pixel = 0;
			while (true)
			{
				if (map[MapIndex_Y1][MapIndex_X1] == 1)
				{
					wall_pixel = MAP_START + BITMAP_SIZE * (MapIndex_X1 + 1);
					break;
				}
				else
					MapIndex_X1--;
			}
		}
	}

	// 向右移動
	void CPacman::SetMovingRight(bool flag)
	{
		GetMapIndex();
		if (map[MapIndex_Y1][MapIndex_X2 + 1] != 1 && map[MapIndex_Y2][MapIndex_X2 + 1] != 1) {
			animation = &animation_4;
			isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
			isMovingRight = flag;

			// 計算向右終點牆的位置
			wall_pixel = 0;
			while (true)
			{
				if (map[MapIndex_Y1][MapIndex_X1] == 1)
				{
					wall_pixel = MAP_START + BITMAP_SIZE * (MapIndex_X1 - 1);
					break;
				}
				else
					MapIndex_X1++;
			}
		}
	}

	// 檢查Pacman所構成的矩形是否碰到ghost
	bool CPacman::HitGhost(CGhost *ghost)
	{
		return HitRectangle(ghost->GetX1(), ghost->GetY1(),
			ghost->GetX2(), ghost->GetY2());
	}

	bool CPacman::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		// 檢查是否有交集
		return (tx2 >= x && tx1 <= (x + animation->Width()) && ty2 >= y && ty1 <= (y + animation->Height()));
	}

	void CPacman::SetMap(int **map) {
		this->map = map;
	}

	void CPacman::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	bool CPacman::IsAlive()
	{
		return is_alive;
	}

	int CPacman::GetLife()
	{
		return myLife;
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

	void CPacman::restart()
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		animation = &animation_stop_4;
		y = init_Y;
		x = init_X;
		is_alive = true;
	}

	bool CPacman::IsGameover()
	{
		if (myLife < 0) {
			return true;
		}
		return false;
	}

	void CPacman::SetTopLeft() {
		animation->SetTopLeft(x, y);
	}

	void CPacman::OnShow()
	{
		if (is_alive)
		{
			if (isStop) {
				if (isMovingUp) {
					isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					animation = &animation_stop_1; // 向上停止
				}
				else if (isMovingDown) {
					isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					animation = &animation_stop_2; // 向下停止
				}
				else if (isMovingLeft) {
					isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					animation = &animation_stop_3; // 向左停止
				}
				else if (isMovingRight) {
					isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					animation = &animation_stop_4; // 向右停止
				}
			}

			animation->SetTopLeft(x, y);
			animation->OnShow();
		}
		else {
			animation = &animation_die;
			delay++; // 死亡動畫時間
			animation->SetTopLeft(x, y);
			animation->OnMove();
			animation->OnShow();
		}
		
		// 死亡動畫結束
		if (delay == 29) {
			myLife--;
			if (myLife > -1) restart();
			delay = 0;
			animation->OnMove();
			animation->OnShow();
		}
	}
}