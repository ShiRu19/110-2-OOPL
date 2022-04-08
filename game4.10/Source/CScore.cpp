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
		// 初始score = -20，避免開局就20分
		myScore.SetInteger(-20);
		// 預設score只有1位數 (0);
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
		int newScore = myScore.GetInteger() + profit;
		myScore.SetInteger(newScore);

		// 計算score的位數
		int d = 1;
		while (true) {
			newScore = newScore / 10;
			if (newScore != 0) {
				d++;
			}
			else {
				myScore.SetDigits(d); // 重設score的位數
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