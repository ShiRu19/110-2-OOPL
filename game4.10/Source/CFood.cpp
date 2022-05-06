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
	// CFood: Food class
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
	}

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