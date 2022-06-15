#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CScore.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CScore: Score class
	/////////////////////////////////////////////////////////////////////////////

	CScore::CScore()
	{
		myScore.SetInteger(0);
		// �w�]score�u��1��� (0);
		myScore.SetDigits(1);
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
		int newScore = profit;
		myScore.SetInteger(newScore);

		// �p��score�����
		int d = 1;
		while (true) {
			newScore = newScore / 10;
			if (newScore != 0) {
				d++;
			}
			else {
				myScore.SetDigits(d); // ���]score�����
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