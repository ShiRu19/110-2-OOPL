#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGhost.h"
#include "CLife.h"
#include "CPacman.h"

namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// CPacman: Pacman class
	/////////////////////////////////////////////////////////////////////////////

	// Pacman
	CPacman::CPacman() 
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		is_alive = true;
	}

	CPacman::~CPacman() {}

	void CPacman::GameRestart()
	{
		restart();
		myLife = 4;
		delay = 0;
		is_gameover = false;
	}

	void CPacman::SetInitXY(int x, int y)
	{
		init_X = MAP_START + x * BITMAP_SIZE;									// �]�wPacman�_�l��Y�y��
		init_Y = MAP_START + y * BITMAP_SIZE;									// �]�wPacman�_�l��X�y��
		this->x = init_X;
		this->y = init_Y;
	}

	void CPacman::LoadBitmap()
	{
		// STOP
		animation_stop_1.AddBitmap(IDB_PACMAN_UP_1, RGB(255, 255, 255));        //�R��A(�w�]�V�W)
		animation_stop_2.AddBitmap(IDB_PACMAN_DOWN_1, RGB(255, 255, 255));      //�R��A(�w�]�V�U)
		animation_stop_3.AddBitmap(IDB_PACMAN_LEFT_1, RGB(255, 255, 255));      //�R��A(�w�]�V��)
		animation_stop_4.AddBitmap(IDB_PACMAN_RIGHT_1, RGB(255, 255, 255));     //�R��A(�w�]�V�k)

		// DIE
		animation_die.AddBitmap(IDB_PACMAN_UP_1, RGB(255, 255, 255));           //���`(�V�W)
		animation_die.AddBitmap(IDB_PACMAN_DIE_1, RGB(255, 255, 255));
		animation_die.AddBitmap(IDB_PACMAN_DIE_2, RGB(255, 255, 255));
		animation_die.AddBitmap(IDB_PACMAN_DIE_3, RGB(255, 255, 255));
		animation_die.AddBitmap(IDB_PACMAN_DIE_4, RGB(255, 255, 255));
		animation_die.AddBitmap(IDB_PACMAN_DIE_BLACK, RGB(255, 255, 255));      //���µ���

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

	void CPacman::OnMove() 
	{
		if (!is_alive)
			return;

		const int STEP_SIZE = 2;
		animation->OnMove();
		isStop = false;
		GetMapIndex();

		if (lastKey == 0) SetMovingUp(true);
		else if (lastKey == 1) SetMovingDown(true);
		else if (lastKey == 2) SetMovingLeft(true);
		else if (lastKey == 3) SetMovingRight(true);

		if (isMovingUp)
		{
			if (y - wall_pixel > STEP_SIZE)
			{
				y -= STEP_SIZE;
			}
			else
			{
				y = wall_pixel;
				isStop = true;
			}
		}
		else if (isMovingDown)
		{
			if (wall_pixel - y > STEP_SIZE) 
			{
				y += STEP_SIZE;
			}
			else 
			{
				y = wall_pixel;
				isStop = true;
			}
		}
		else if (isMovingLeft)
		{
			if (x < MAP_START + BITMAP_SIZE * (0) + 5)
			{
				x = MAP_START + BITMAP_SIZE * (27);
				SetMovingLeft(true);
				return;
			}

			if (x - wall_pixel > STEP_SIZE) 
			{
				x -= STEP_SIZE;
			}
			else
			{
				x = wall_pixel;
				isStop = true;
			}
		}
		else if (isMovingRight)
		{
			if (x > MAP_START + BITMAP_SIZE * (27) - 5) 
			{
				x = MAP_START + BITMAP_SIZE * (0);
				SetMovingRight(true);
				return;
			}

			if (wall_pixel - x > STEP_SIZE) 
			{
				x += STEP_SIZE;
			}
			else 
			{
				x = wall_pixel;
				isStop = true;
			}
		}
	}

	// ��y�Цbmap�}�C�W����m(X)
	int CPacman::FindMapIndex_X(int x)
	{
		return (x - MAP_START) / BITMAP_SIZE;
	}
	// ��y�Цbmap�}�C�W����m(Y)
	int CPacman::FindMapIndex_Y(int y)
	{
		return (y - MAP_START) / BITMAP_SIZE;
	}

	// ��Pacman�|���I���}�C��m
	void CPacman::GetMapIndex() 
	{
		MapIndex_X1 = FindMapIndex_X(x);         // ��
		MapIndex_X2 = FindMapIndex_X(x + 22);    // �k
		MapIndex_Y1 = FindMapIndex_Y(y);         // �W
		MapIndex_Y2 = FindMapIndex_Y(y + 22);    // �U
	}

	// �V�W����
	void CPacman::SetMovingUp(bool flag)
	{
		GetMapIndex();
		if (map[MapIndex_Y1 - 1][MapIndex_X1] != 1 && map[MapIndex_Y1 - 1][MapIndex_X2] != 1) 
		{
			animation = &animation_1;
			isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
			isMovingUp = flag;

			// �p��V�W���I�𪺦�m
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

	// �V�U����
	void CPacman::SetMovingDown(bool flag)
	{
		GetMapIndex();
		if (map[MapIndex_Y2 + 1][MapIndex_X1] != 1 && map[MapIndex_Y2 + 1][MapIndex_X2] != 1 && map[MapIndex_Y2 + 1][MapIndex_X1] != 2 && map[MapIndex_Y2 + 1][MapIndex_X2] != 2) 
		{
			animation = &animation_2;
			isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
			isMovingDown = flag;
			// �p��V�U���I�𪺦�m
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

	// �V������
	void CPacman::SetMovingLeft(bool flag)
	{
		GetMapIndex();
		if (map[MapIndex_Y1][MapIndex_X1-1] != 1 && map[MapIndex_Y2][MapIndex_X1-1] != 1) 
		{
			animation = &animation_3;
			isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
			isMovingLeft = flag;
			// �p��V�����I�𪺦�m
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

	// �V�k����
	void CPacman::SetMovingRight(bool flag)
	{
		GetMapIndex();
		if (map[MapIndex_Y1][MapIndex_X2 + 1] != 1 && map[MapIndex_Y2][MapIndex_X2 + 1] != 1)
		{
			animation = &animation_4;
			isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
			isMovingRight = flag;

			// �p��V�k���I�𪺦�m
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

	// �ˬdPacman�Һc�����x�άO�_�I��ghost
	bool CPacman::HitGhost(CGhost *ghost)
	{
		int adjust = 2;
		return HitRectangle(ghost->GetX1() + adjust, ghost->GetY1() + adjust,
			ghost->GetX2() - adjust, ghost->GetY2() - adjust);
	}

	bool CPacman::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int adjust = 2;
		// �ˬd�O�_���涰
		return (tx2 >= x + adjust && tx1 <= (x + animation->Width() - adjust) && ty2 >= y + adjust && ty1 <= (y + animation->Height() - adjust));
	}

	void CPacman::SetMap(int **m)
	{
		for (int i = 0; i < 31; i++)
		{
			for (int j = 0; j < 28; j++) {
				map[i][j] = m[i][j];
			}
		}
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
		SetLastKey(-1);
		animation = &animation_stop_4;
		y = init_Y;
		x = init_X;
		is_alive = true;
	}

	int CPacman::GetDelay() {
		return delay;
	}

	void CPacman::SetLife(int life) {
		myLife = life;
	}

	bool CPacman::IsGameover()
	{
		if (myLife < 0) {
			return true;
		}
		return false;
	}

	void CPacman::SetTopLeft() 
	{
		animation->SetTopLeft(x, y);
	}

	void CPacman::OnShow()
	{
		if (is_alive)
		{
			if (isStop) 
			{
				if (isMovingUp) 
				{
					isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					animation = &animation_stop_1; // �V�W����
				}
				else if (isMovingDown) 
				{
					isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					animation = &animation_stop_2; // �V�U����
				}
				else if (isMovingLeft) 
				{
					isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					animation = &animation_stop_3; // �V������
				}
				else if (isMovingRight) 
				{
					isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					animation = &animation_stop_4; // �V�k����
				}
			}

			animation->SetTopLeft(x, y);
			animation->OnShow();
		}
		else {
			animation = &animation_die;
			delay++; // ���`�ʵe�ɶ�
			animation->SetTopLeft(x, y);
			animation->OnMove();
			animation->OnShow();
		}
		
		// ���`�ʵe����
		if (delay == 29) 
		{
			myLife--;
			if (myLife > -1) restart();
			delay = 0;
			animation->OnMove();
			animation->OnShow();
		}
	}
	void CPacman::SetLastKey(int key)
	{
		//
		// 0: �W, 1: �U, 2: ��,3: �k
		//
		lastKey = key;
	}
}