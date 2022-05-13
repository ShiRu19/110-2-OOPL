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

	void CGhost::SetInitTargetXY(int x, int y) {
		init_target_x = x;
		init_target_y = y;
	}

	void CGhost::SetMap(int **map) {
		this->map = map;
	}

	void CGhost::OnMove(int pacman_x, int pacman_y) {
		animation->OnMove();

		if (animation == &animation_eyes) {
			if (x == init_x && y == init_y) {
				animation = &animation_1;
				isGoOut = false;
				return;
			}
			GoToDestination(init_x, init_y);
		}
		else if (animation == &animation_avoid) {
			return;
		}
		else {
			if (isGoOut) {
				GoToDestination(pacman_x, pacman_y);
			}
			else {
				if (x == init_target_x && y == init_target_y) {
					isGoOut = true;
					return;
				}
				GoToDestination(init_target_x, init_target_y);
			}
		}
	}

	void CGhost::GoToDestination(int des_x, int des_y) {
		GetMapIndex();                // 取得四個點的陣列位置
		
		double distance;              // 下一步到目的地的距離
		double minDistance = INT_MAX; // 在所有方向到目的地的距離中取最短距離
		
		// ********************
		// direction 代號表示：
		// 0 => 無方向
		// 1 => 向上
		// 2 => 向下
		// 3 => 向左
		// 4 => 向右
		// ********************
		
		// 若前一步為向上或向下，則先判斷上下方向
		if (eyesDirection == 1 || eyesDirection == 2) {
			// 向上
			distance = turnUp(des_x, des_y);
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 1; // 1 為向上
			}

			// 向下
			distance = turnDown(des_x, des_y);
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 2; // 2 為向下
			}

			// 向左
			distance = turnLeft(des_x, des_y);
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 3; // 3 為向左
			}

			// 向右
			distance = turnRight(des_x, des_y);
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 4; // 4 為向右
			}
		}
		// 若前一步為向左或向右，則先判斷左右方向
		else {
			// 向左
			distance = turnLeft(des_x, des_y);
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 3; // 3 為向左
			}

			// 向右
			distance = turnRight(des_x, des_y);
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 4; // 4 為向右
			}

			// 向上
			distance = turnUp(des_x, des_y);
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 1; // 1 為向上
			}

			// 向下
			distance = turnDown(des_x, des_y);
			if (distance < minDistance) {
				minDistance = distance;
				eyesDirection = 2; // 2 為向下
			}
		}

		const int STEP_SIZE = 2;
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

	double CGhost::turnUp(int des_x, int des_y) {
		int next_x, next_y;           // 下一步的座標位置
		double distance = INT_MAX;
		bool canTurn = false;

		if (animation == &animation_eyes || !isGoOut) {
			// 狀態為眼睛時，可進入基地
			// 或尚未從基地出去的鬼才可待在基地
			if (map[MapIndex_Y2 - 1][MapIndex_X1] != 1 && map[MapIndex_Y2 - 1][MapIndex_X2] != 1) {
				canTurn = true;
			}
		}
		else {
			// 狀態不為眼睛時，不可進入基地
			if (map[MapIndex_Y2 - 1][MapIndex_X1] == 0 && map[MapIndex_Y2 - 1][MapIndex_X2] == 0) {
				canTurn = true;
			}
		}

		// 向上可以走
		if (canTurn) {
			if (eyesDirection != 2) {
				next_x = MAP_START + BITMAP_SIZE * (MapIndex_X1);
				next_y = MAP_START + BITMAP_SIZE * (MapIndex_Y1 - 1);
				distance = GetDistance(des_x, next_x, des_y, next_y);
			}
		}

		return distance;
	}

	double CGhost::turnDown(int des_x, int des_y) {
		int next_x, next_y;           // 下一步的座標位置
		double distance = INT_MAX;
		bool canTurn = false;

		if (animation == &animation_eyes || !isGoOut) {
			// 狀態為眼睛時，可進入基地
			// 或尚未從基地出去的鬼才可待在基地
			if (map[MapIndex_Y1 + 1][MapIndex_X1] != 1 && map[MapIndex_Y1 + 1][MapIndex_X2] != 1) {
				canTurn = true;
			}
		}
		else {
			// 狀態不為眼睛時，不可進入基地
			if (map[MapIndex_Y1 + 1][MapIndex_X1] == 0 && map[MapIndex_Y1 + 1][MapIndex_X2] == 0) {
				canTurn = true;
			}
		}

		// 向下可以走
		if (canTurn) {
			if (eyesDirection != 1) {
				next_x = MAP_START + BITMAP_SIZE * (MapIndex_X1);
				next_y = MAP_START + BITMAP_SIZE * (MapIndex_Y1 + 1);
				distance = GetDistance(des_x, next_x, des_y, next_y);
			}
		}

		return distance;
	}

	double CGhost::turnLeft(int des_x, int des_y) {
		int next_x, next_y;           // 下一步的座標位置
		double distance = INT_MAX;
		bool canTurn = false;

		if (animation == &animation_eyes || !isGoOut) {
			// 狀態為眼睛時，可進入基地
			// 或尚未從基地出去的鬼才可待在基地
			if (map[MapIndex_Y1][MapIndex_X2 - 1] != 1 && map[MapIndex_Y2][MapIndex_X2 - 1] != 1) {
				canTurn = true;
			}
		}
		else {
			// 狀態不為眼睛時，不可進入基地
			if (map[MapIndex_Y1][MapIndex_X2 - 1] == 0 && map[MapIndex_Y2][MapIndex_X2 - 1] == 0) {
				canTurn = true;
			}
		}

		// 向左可以走
		if (canTurn) {
			if (eyesDirection != 4) {
				next_x = MAP_START + BITMAP_SIZE * (MapIndex_X1 - 1);
				next_y = MAP_START + BITMAP_SIZE * (MapIndex_Y1);
				distance = GetDistance(des_x, next_x, des_y, next_y);
			}
		}

		return distance;
	}

	double CGhost::turnRight(int des_x, int des_y) {
		int next_x, next_y;           // 下一步的座標位置
		double distance = INT_MAX;
		bool canTurn = false;

		if (animation == &animation_eyes || !isGoOut) {
			// 狀態為眼睛時，可進入基地
			// 或尚未從基地出去的鬼才可待在基地
			if (map[MapIndex_Y1][MapIndex_X1 + 1] != 1 && map[MapIndex_Y2][MapIndex_X1 + 1] != 1) {
				canTurn = true;
			}
		}
		else {
			// 狀態不為眼睛時，不可進入基地
			if (map[MapIndex_Y1][MapIndex_X1 + 1] == 0 && map[MapIndex_Y2][MapIndex_X1 + 1] == 0) {
				canTurn = true;
			}
		}

		// 向右可以走
		if (canTurn) {
			if (eyesDirection != 3) {
				next_x = MAP_START + BITMAP_SIZE * (MapIndex_X1 + 1);
				next_y = MAP_START + BITMAP_SIZE * (MapIndex_Y1);
				distance = GetDistance(des_x, next_x, des_y, next_y);
			}
		}

		return distance;
	}

	double CGhost::GetDistance(int x1, int x2, int y1, int y2) {
		int distance_x = x1 - x2;
		int distance_y = y1 - y2;
		return sqrt(distance_x * distance_x + distance_y * distance_y);
	}

	// 找座標在map陣列上的位置(X)
	int CGhost::FindMapIndex_X(int x)
	{
		return (x - MAP_START) / BITMAP_SIZE;
	}
	// 找座標在map陣列上的位置(Y)
	int CGhost::FindMapIndex_Y(int y)
	{
		return (y - MAP_START) / BITMAP_SIZE;
	}

	// 找Ghost四個點的陣列位置
	void CGhost::GetMapIndex() {
		MapIndex_X1 = FindMapIndex_X(x);         // 左
		MapIndex_X2 = FindMapIndex_X(x + 22);    // 右
		MapIndex_Y1 = FindMapIndex_Y(y);         // 上
		MapIndex_Y2 = FindMapIndex_Y(y + 22);    // 下
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

		// 躲避鬼
		animation_avoid.AddBitmap(IDB_GHOST_BLUE_1, RGB(0, 0, 0));
		animation_avoid.AddBitmap(IDB_GHOST_BLUE_2, RGB(0, 0, 0));

		// 不穩定鬼 (躲避鬼變正常鬼間的不穩定狀態)
		animation_change.AddBitmap(IDB_GHOST_BLUE_1, RGB(0, 0, 0));
		animation_change.AddBitmap(IDB_GHOST_WHITE_2, RGB(0, 0, 0));

		// 眼睛
		animation_eyes.AddBitmap(IDB_GHOST_EYES_DOWN, RGB(0, 0, 0));
	}
	
	//
	// 切換鬼的狀態
	// 0 => 眼睛 to 正常鬼
	// 1 => 正常鬼 to 躲避鬼
	// 2 => 躲避鬼 to 不穩定鬼
	// 3 => 不穩定鬼 to 眼睛
	//
	void CGhost::changeMode(int mode) {
		if (mode == 0) animation = &animation_4;           // 正常鬼
		else if (mode == 1) animation = &animation_avoid;  // 躲避鬼
		else if (mode == 2) animation = &animation_change; // 不穩定鬼
		else if (mode == 3) animation = &animation_eyes;   // 眼睛
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

	void CGhost::restart()
	{
		animation = &animation_1;
		y = init_y;
		x = init_x;
	}

	void CGhost::OnShow() {
		// ***************************
		// * 當狀態為躲避或不穩定時
		// ***************************
		if (animation == &animation_avoid || animation == &animation_change) {
			avoidTime++;
		}
		
		// 躲避約8秒後，躲避鬼轉為不穩定狀態
		if (avoidTime == 180) {
			changeMode(2);
		}
		// 再經過約3秒，從不穩定狀態回到正常狀態
		if (avoidTime == 230) {
			avoidTime = 0;
			changeMode(0);
		}

		// ************************************
		// * 當狀態為死亡時 (animation_eyes)
		// ************************************
		//if (animation == &animation_eyes) {
		//	if (x == init_x && y == init_y) {
		//
		//		animation = &animation_1;
		//	}
		//}

		animation->SetTopLeft(x,y);
		animation->OnShow();
	}
}