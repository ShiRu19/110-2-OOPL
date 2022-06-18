#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CLevel.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CLevel: Level class
	/////////////////////////////////////////////////////////////////////////////

	CLevel::CLevel()
	{
		// Level�w�]��1���
		myLevel = CInteger(1);
		// �w�]��1
		myLevel.SetInteger(1);
	}

	void CLevel::LoadBitmap()
	{
		LEVEL_text.LoadBitmap(IDB_LEVEL_TEXT, RGB(255, 255, 255));
		myLevel.LoadBitmap();
	}
	
	void CLevel::setLevel(int LV)
	{
		myLevel.SetInteger(LV);

		// �p��level�����
		int d = 1;
		while (true)
		{
			LV = LV / 10;
			if (LV != 0) d++;
			else
			{
				myLevel.SetDigits(d); // ���]level�����
				break;
			}

		}
	}

	void CLevel::levelUp()
	{
		int nextLevel = myLevel.GetInteger() + 1;
		setLevel(nextLevel);
	}
	
	int CLevel::getLevel()
	{
		return myLevel.GetInteger();
	}

	void CLevel::SetTopLeft()
	{
		LEVEL_text.SetTopLeft(800, 130);
		myLevel.SetTopLeft(820, 155);
	}

	void CLevel::OnShow()
	{
		LEVEL_text.ShowBitmap();
		myLevel.ShowBitmap();
	}
}