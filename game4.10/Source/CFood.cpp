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

	bool CFood::HitPacman(CPacman *pacman)
	{
		// �˴�Pacman�Һc�����x�άO�_�I��food
		return HitRectangle(pacman->GetX1(), pacman->GetY1(),
			pacman->GetX2(), pacman->GetY2());
	}

	bool CFood::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		// �ˬd�O�_���涰
		return (tx2 >= x+1 && tx1 <= (x + food.Width()-1) && ty2 >= y+1 && ty1 <= (y + food.Height()-1));
	}

	bool CFood::IsAlive()
	{
		return is_alive;
	}

	void CFood::LoadBitmap()
	{
		food.LoadBitmap(IDB_FOOD, RGB(0, 0, 0)); // ���Jfood
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
			// �p��y�V����ߪ��첾�qdx, dy
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

	void CFood::SetTopLeft(int x, int y) {
		this->x = x;
		this->y = y;
		food.SetTopLeft(x, y);
	}

	void CFood::OnShow()
	{
		if (is_alive) {
			food.SetTopLeft(x, y);
			food.ShowBitmap();
		}
	}
}