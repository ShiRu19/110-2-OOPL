#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CPacman.h"
#include "CFood.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CFood::CFood()
	{
		is_alive = true;
		x = y = 0;
	}

	CFood::CFood(int score)
	{
		is_alive = true;
		x = y = 0;
		this->score = score;
	}

	bool CFood::HitPacman(CPacman *pacman)
	{
		// 檢測Pacman所構成的矩形是否碰到food
		return HitRectangle(pacman->GetX1(), pacman->GetY1(),
			pacman->GetX2(), pacman->GetY2());
	}

	bool CFood::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		// 檢查是否有交集
		return (tx2 >= x+1 && tx1 <= (x + foods.Width()-1) && ty2 >= y+1 && ty1 <= (y + foods.Height()-1));
	}

	bool CFood::IsAlive()
	{
		return is_alive;
	}

	void CFood::LoadBitmap(int IDB1, int IDB2)
	{
		foods.AddBitmap(IDB1, RGB(0, 0, 0));
		foods.AddBitmap(IDB2, RGB(0, 0, 0));
	}

	void CFood::OnMove()
	{
		if (!is_alive)
			return;
		/*
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// 計算球向對於圓心的位移量dx, dy
			//
			const int STEPS = 18;
			static const int DIFFX[] = { 35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
			static const int DIFFY[] = { 0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];
		}*/
	}

	/*
	void CFood::SetDelay(int d)
	{
		delay = d;
	}
	*/

	void CFood::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CFood::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	int CFood::GetScore() {
		return this->score;
	}

	void CFood::SetTopLeft(int x, int y) {
		foods.SetTopLeft(x, y);
		this->x = x;
		this->y = y;
	}
	
	void CFood::OnShow()
	{
		if (is_alive) {
			foods.SetTopLeft(x,y);
			foods.OnMove();
			foods.OnShow();
		}
	}
	
}