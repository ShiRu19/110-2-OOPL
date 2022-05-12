#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include "audio.h"
#include "gamelib.h"
#include "CGhost.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CGolst: Golst class
	/////////////////////////////////////////////////////////////////////////////

	// Golst
	CGhost::CGhost() {
	}

	void CGhost::SetInitXY(int x, int y) {
		init_x = x;
		init_y = y;
		this->x = init_x;
		this->y = init_y;
	}

	void CGhost::SetMap(int **map) {
		this->map = map;
	}

	void CGhost::OnMove() {
		animation->OnMove();

		if (animation == &animation_eyes) {
			GoHome();
		}
	}

	void CGhost::GoHome() {
		if (x == init_x && y == init_y) {
			return;
		}

		GetMapIndex();
		
		double distance;              // �U�@�B�� home ���Z��
		double minDistance = INT_MAX; // �b�Ҧ���V�� home ���Z�������̵u�Z��
		
		// ********************
		// direction �N����ܡG
		// 0 => �L��V
		// 1 => �V�W
		// 2 => �V�U
		// 3 => �V��
		// 4 => �V�k
		// ********************
		
		// �Y�e�@�B���V�W�ΦV�U�A�h���P�_�W�U��V
		if (eyesDirection == 1 || eyesDirection == 2) {
			// �V�W
			distance = turnUp();
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 1; // 1 ���V�W
			}

			// �V�U
			distance = turnDown();
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 2; // 2 ���V�U
			}

			// �V��
			distance = turnLeft();
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 3; // 3 ���V��
			}

			// �V�k
			distance = turnRight();
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 4; // 4 ���V�k
			}
		}
		// �Y�e�@�B���V���ΦV�k�A�h���P�_���k��V
		else {
			// �V��
			distance = turnLeft();
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 3; // 3 ���V��
			}

			// �V�k
			distance = turnRight();
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 4; // 4 ���V�k
			}

			// �V�W
			distance = turnUp();
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 1; // 1 ���V�W
			}

			// �V�U
			distance = turnDown();
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 2; // 2 ���V�U
			}
		}

		const int STEP_SIZE = 3;
		switch (eyesDirection) {
			case 0:
				break;
			case 1:
				y -= STEP_SIZE;
				break;
			case 2:
				y += STEP_SIZE;
				break;
			case 3:
				x -= STEP_SIZE;
				break;
			case 4:
				x += STEP_SIZE;
				break;
		}
	}

	double CGhost::turnUp() {
		int next_x, next_y;           // �U�@�B���y�Ц�m
		double distance = INT_MAX;

		// �V�W�i�H��
		if (map[MapIndex_Y2 - 1][MapIndex_X1] != 1 && map[MapIndex_Y2 - 1][MapIndex_X2] != 1) {
			if (eyesDirection != 2) {
				next_x = MAP_START + BITMAP_SIZE * (MapIndex_X1);
				next_y = MAP_START + BITMAP_SIZE * (MapIndex_Y1 - 1);
				distance = GetDistance(init_x, next_x, init_y, next_y);
			}
		}

		return distance;
	}

	double CGhost::turnDown() {
		int next_x, next_y;           // �U�@�B���y�Ц�m
		double distance = INT_MAX;

		// �V�U�i�H��
		if (map[MapIndex_Y1 + 1][MapIndex_X1] != 1 && map[MapIndex_Y1 + 1][MapIndex_X2] != 1) {
			if (eyesDirection != 1) {
				next_x = MAP_START + BITMAP_SIZE * (MapIndex_X1);
				next_y = MAP_START + BITMAP_SIZE * (MapIndex_Y1 + 1);
				distance = GetDistance(init_x, next_x, init_y, next_y);
			}
		}

		return distance;
	}

	double CGhost::turnLeft() {
		int next_x, next_y;           // �U�@�B���y�Ц�m
		double distance = INT_MAX;

		// �V���i�H��
		if (map[MapIndex_Y1][MapIndex_X2 - 1] != 1 && map[MapIndex_Y2][MapIndex_X2 - 1] != 1) {
			if (eyesDirection != 4) {
				next_x = MAP_START + BITMAP_SIZE * (MapIndex_X1 - 1);
				next_y = MAP_START + BITMAP_SIZE * (MapIndex_Y1);
				distance = GetDistance(init_x, next_x, init_y, next_y);
			}
		}

		return distance;
	}

	double CGhost::turnRight() {
		int next_x, next_y;           // �U�@�B���y�Ц�m
		double distance = INT_MAX;

		// �V�k�i�H��
		if (map[MapIndex_Y1][MapIndex_X1 + 1] != 1 && map[MapIndex_Y2][MapIndex_X1 + 1] != 1) {
			if (eyesDirection != 3) {
				next_x = MAP_START + BITMAP_SIZE * (MapIndex_X1 + 1);
				next_y = MAP_START + BITMAP_SIZE * (MapIndex_Y1);
				distance = GetDistance(init_x, next_x, init_y, next_y);
			}
		}

		return distance;
	}

	double CGhost::GetDistance(int x1, int x2, int y1, int y2) {
		int distance_x = x1 - x2;
		int distance_y = y1 - y2;
		return sqrt(distance_x * distance_x + distance_y * distance_y);
	}

	// ��y�Цbmap�}�C�W����m(X)
	int CGhost::FindMapIndex_X(int x)
	{
		return (x - MAP_START) / BITMAP_SIZE;
	}
	// ��y�Цbmap�}�C�W����m(Y)
	int CGhost::FindMapIndex_Y(int y)
	{
		return (y - MAP_START) / BITMAP_SIZE;
	}

	// ��Ghost�|���I���}�C��m
	void CGhost::GetMapIndex() {
		MapIndex_X1 = FindMapIndex_X(x);         // ��
		MapIndex_X2 = FindMapIndex_X(x + 22);    // �k
		MapIndex_Y1 = FindMapIndex_Y(y);         // �W
		MapIndex_Y2 = FindMapIndex_Y(y + 22);    // �U
	}

	void CGhost::LoadBitmap(int IDB[4][2]) {
		// up
		animation_1.AddBitmap(IDB[0][0], RGB(0, 0, 0));
		animation_1.AddBitmap(IDB[0][1], RGB(0, 0, 0));

		// down
		animation_2.AddBitmap(IDB[1][0], RGB(0, 0, 0));
		animation_2.AddBitmap(IDB[1][1], RGB(0, 0, 0));

		// left
		animation_3.AddBitmap(IDB[2][0], RGB(0, 0, 0));
		animation_3.AddBitmap(IDB[2][1], RGB(0, 0, 0));

		// right
		animation_4.AddBitmap(IDB[3][0], RGB(0, 0, 0));
		animation_4.AddBitmap(IDB[3][1], RGB(0, 0, 0));

		// ���װ�
		animation_avoid.AddBitmap(IDB_GHOST_BLUE_1, RGB(0, 0, 0));
		animation_avoid.AddBitmap(IDB_GHOST_BLUE_2, RGB(0, 0, 0));

		// ��í�w�� (���װ��ܥ��`��������í�w���A)
		animation_change.AddBitmap(IDB_GHOST_BLUE_1, RGB(0, 0, 0));
		animation_change.AddBitmap(IDB_GHOST_WHITE_2, RGB(0, 0, 0));

		// ����
		animation_eyes.AddBitmap(IDB_GHOST_EYES_DOWN, RGB(0, 0, 0));
	}
	
	//
	// �����������A
	// 0 => ���� to ���`��
	// 1 => ���`�� to ���װ�
	// 2 => ���װ� to ��í�w��
	// 3 => ��í�w�� to ����
	//
	void CGhost::changeMode(int mode) {
		if (mode == 0) animation = &animation_4;           // ���`��
		else if (mode == 1) animation = &animation_avoid;  // ���װ�
		else if (mode == 2) animation = &animation_change; // ��í�w��
		else if (mode == 3) animation = &animation_eyes;   // ����
	}

	bool CGhost::isNormalMode() {
		if (animation == &animation_avoid || animation == &animation_change || animation == &animation_eyes) {
			return false;
		}
		return true;
	}

	int CGhost::GetX1() {
		return x;
	}
	
	int CGhost::GetY1() {
		return y;
	}

	int CGhost::GetX2() {
		return x + animation->Width();
	}

	int CGhost::GetY2() {
		return y + animation->Height();
	}

	void CGhost::SetTopLeft(int x, int y) {
		animation->SetTopLeft(x, y);
		this->x = x;
		this->y = y;
	}

	void CGhost::OnShow() {
		// ***************************
		// * ���A�����שΤ�í�w��
		// ***************************
		if (animation == &animation_avoid || animation == &animation_change) {
			avoidTime++;
		}
		
		// ���׬�8���A���װ��ର��í�w���A
		if (avoidTime == 180) {
			changeMode(2);
		}
		// �A�g�L��3��A�q��í�w���A�^�쥿�`���A
		if (avoidTime == 230) {
			avoidTime = 0;
			changeMode(0);
		}

		// ************************************
		// * ���A�����`�� (animation_eyes)
		// ************************************
		if (animation == &animation_eyes) {
			if (x == init_x && y == init_y) {
				animation = &animation_1;
			}
		}

		animation->SetTopLeft(x,y);
		animation->OnShow();
	}
}