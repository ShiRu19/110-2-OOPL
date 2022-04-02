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
		myScore = 0;
	}
	
	void CScore::setScore(int profit) {
		myScore += profit;
	}

	int CScore::getScore() {
		return myScore;
	}
}