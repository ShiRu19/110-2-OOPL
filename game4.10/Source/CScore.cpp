#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CScore.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	CScore::CScore()
	{
		myScore.SetInteger(-20);
		myScore.SetDigits(2);
	}

	void CScore::LoadBitmap() {
		SCORE_text.LoadBitmap(IDB_SCORE_TEXT, RGB(255, 255, 255));
		myScore.LoadBitmap();
	}

	void CScore::SetTopLeft() {
		SCORE_text.SetTopLeft(800, 50);
		myScore.SetTopLeft(820, 75);
	}
	
	void CScore::setScore(int profit) {
		int newScore = myScore.GetInteger() + profit;
		myScore.SetInteger(newScore);

		int d = 1;
		while (true) {
			newScore = newScore / 10;
			if (newScore != 0) {
				d++;
			}
			else {
				myScore.SetDigits(d);
				break;
			}

		}
	}

	int CScore::getScore() {
		return myScore.GetInteger();
	}

	void CScore::OnShow() {
		SCORE_text.ShowBitmap();
		myScore.ShowBitmap();
	}
}