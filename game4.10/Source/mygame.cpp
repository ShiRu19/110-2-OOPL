/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "cstdlib"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(28), NUMMAPS(3)
{
	ghostDelay = 0;
	remainFoods = 299;
	initFoods = 299;
	isCompleted = false;
}

CGameStateRun::~CGameStateRun()
{
	
}

void CGameStateRun::OnBeginState()
{
	
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//
	// 判斷Pacman是否碰到food
	//
	vector<CFood *>* allFoods = gameMap.getAllFoods();
	for (int i = 0; i < gameMap.getFoodCount(); i++) {
		if ((*allFoods->at(i)).IsAlive() && (*allFoods->at(i)).HitPacman(&c_PacMan)) {
			(*allFoods->at(i)).SetIsAlive(false);
			remainFoods--;
			myScore.setScore(myScore.getScore() + (*allFoods->at(i)).GetScore()); // 得分

			// 如果是碰到大魔豆
			if ((*allFoods->at(i)).GetScore() == 50) {
				// ghost轉成躲避鬼模式
				for (int i = 0; i < 4; i++) {
					ghost[i].changeMode(1);
				}
			}
		}
	}
	
	//
	// 判斷Pacman是否碰到ghost
	//
	for (int i = 0; i < 4; i++) {
		// 若碰到正常鬼，Pacman死亡
		if (ghost[i].isNormalMode()) {
			if (c_PacMan.IsAlive() && c_PacMan.HitGhost(&ghost[i])) {
				c_PacMan.SetIsAlive(false); // Pacman死亡
				initFoods = remainFoods;
			}
		}
		// 若碰到躲避鬼或不穩定鬼，Pacman得分
		else if (ghost[i].isNormalMode() != true) {
			if (c_PacMan.IsAlive() && c_PacMan.HitGhost(&ghost[i])) {
				ghost[i].changeMode(3); // 鬼變眼睛狀態
				myScore.setScore(myScore.getScore() + 10); // 得分
			}
		}
	}

	if (!c_PacMan.IsAlive()) {
		if (c_PacMan.GetDelay() == 28) {
			for (int i = 0; i < 4; i++) {
				ghost[i].restart(); // 重新開始
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				ghost[i].changeMode(4); // 靜止
			}
		}
	}

	//
	// 更新目前生命值
	// 
	myLife.setLife(c_PacMan.GetLife());

	//
	// 更新目前關卡
	// 
	if (remainFoods == 0 && myLevel.getLevel() != 3) {
		gameMap.nextMap();
		myLevel.levelUp();
		myScore.setScore(myScore.getScore() - 10);
		c_PacMan.restart();
		c_PacMan.SetMap(gameMap.GetMap());
		for (int i = 0; i < 4; i++) {
			ghost[i].restart();
			ghost[i].SetMap(gameMap.GetMap());
		}
		
		remainFoods = gameMap.getFoodCount();
		initFoods = remainFoods;
	}
	else if (remainFoods == 0 && myLevel.getLevel() == 3) {
		isCompleted = true;
	}

	//
	// 移動PacMan
	//
	if(c_PacMan.IsAlive())
		c_PacMan.OnMove();

	//
	// 移動ghosts
	//
	double eat_rate = (initFoods - remainFoods - 0.0) / initFoods;

	// 馬上出發
	ghost[0].OnMove(c_PacMan.GetX1(), c_PacMan.GetY1());

	// 約吃到10顆豆子時出發
	if (eat_rate >= 0.03) ghost[1].OnMove(c_PacMan.GetX1(), c_PacMan.GetY1());
	else ghost[1].OnMove(-1, -1);

	// 約吃到30顆豆子時出發
	if (eat_rate >= 0.1) ghost[2].OnMove(c_PacMan.GetX1(), c_PacMan.GetY1());
	else ghost[2].OnMove(-1, -1);

	// 約吃到40顆豆子時出發
	if (eat_rate >= 0.13) ghost[3].OnMove(c_PacMan.GetX1(), c_PacMan.GetY1());
	else ghost[3].OnMove(-1, -1);
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	//ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
	//background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
	//background.SetTopLeft(50, 50);
	//background.ShowBitmap();
	//
	// 完成部分Loading動作，提高進度
	//
	//ShowInitProgress(50);
	//Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	// help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形			
	// CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	// CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	// CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
	//
	
	// 載入地圖
	gameMap.SetMap(MAP_BLUE);
	gameMap.LoadBitmap();

	// 載入PacMan
	c_PacMan.LoadBitmap();
	c_PacMan.SetInitXY(14, 17);
	c_PacMan.SetMap(gameMap.GetMap());

	// 載入豆子數
	remainFoods = gameMap.getFoodCount();

	// 載入Score文字
	myScore.LoadBitmap();

	// 載入Level文字
	myLevel.LoadBitmap();

	// 載入Life圖示
	myLife.LoadBitmap();

	// 載入 red ghost
	int red[4][2] = {
		{ IDB_GHOST_RED_DOWN_1, IDB_GHOST_RED_DOWN_2 },
		{ IDB_GHOST_RED_DOWN_1, IDB_GHOST_RED_DOWN_2 },
		{ IDB_GHOST_RED_LEFT_1, IDB_GHOST_RED_LEFT_2 },
		{ IDB_GHOST_RED_RIGHT_1, IDB_GHOST_RED_RIGHT_2 } };
	ghost[0].LoadBitmap(red);
	ghost[0].SetInitXY(MAP_START + 12 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[0].SetInitTargetXY(MAP_START + 14 * BITMAP_SIZE, MAP_START + 11 * BITMAP_SIZE);
	ghost[0].SetMap(gameMap.GetMap());

	// 載入 blue ghost
	int blue[4][2] = {
		{ IDB_GHOST_BLUE_DOWN_1, IDB_GHOST_BLUE_DOWN_2 },
		{ IDB_GHOST_BLUE_DOWN_1, IDB_GHOST_BLUE_DOWN_2 },
		{ IDB_GHOST_BLUE_LEFT_1, IDB_GHOST_BLUE_LEFT_2 },
		{ IDB_GHOST_BLUE_RIGHT_1, IDB_GHOST_BLUE_RIGHT_2 } };
	ghost[1].LoadBitmap(blue);
	ghost[1].SetInitXY(MAP_START + 13 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[1].SetInitTargetXY(MAP_START + 14 * BITMAP_SIZE, MAP_START + 11 * BITMAP_SIZE);
	ghost[1].SetMap(gameMap.GetMap());

	// 載入 pink ghost
	int pink[4][2] = {
		{ IDB_GHOST_PINK_DOWN_1, IDB_GHOST_PINK_DOWN_2 },
		{ IDB_GHOST_PINK_DOWN_1, IDB_GHOST_PINK_DOWN_2 },
		{ IDB_GHOST_PINK_LEFT_1, IDB_GHOST_PINK_LEFT_2 },
		{ IDB_GHOST_PINK_RIGHT_1, IDB_GHOST_PINK_RIGHT_2 } };
	ghost[2].LoadBitmap(pink);
	ghost[2].SetInitXY(MAP_START + 14 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[2].SetInitTargetXY(MAP_START + 13 * BITMAP_SIZE, MAP_START + 11 * BITMAP_SIZE);
	ghost[2].SetMap(gameMap.GetMap());

	// 載入 orange ghost
	int orange[4][2] = {
		{ IDB_GHOST_ORANGE_DOWN_1, IDB_GHOST_ORANGE_DOWN_2 },
		{ IDB_GHOST_ORANGE_DOWN_1, IDB_GHOST_ORANGE_DOWN_2 },
		{ IDB_GHOST_ORANGE_LEFT_1, IDB_GHOST_ORANGE_LEFT_2 },
		{ IDB_GHOST_ORANGE_RIGHT_1, IDB_GHOST_ORANGE_RIGHT_2 } };
	ghost[3].LoadBitmap(orange);
	ghost[3].SetInitXY(MAP_START + 15 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[3].SetInitTargetXY(MAP_START + 13 * BITMAP_SIZE, MAP_START + 11 * BITMAP_SIZE);
	ghost[3].SetMap(gameMap.GetMap());
	
	// 設置位置
	c_PacMan.SetTopLeft();
	myScore.SetTopLeft();
	myLevel.SetTopLeft();
	myLife.SetTopLeft();

	ghost[0].SetTopLeft(MAP_START + 12 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[1].SetTopLeft(MAP_START + 13 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[2].SetTopLeft(MAP_START + 14 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[3].SetTopLeft(MAP_START + 15 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_ENTER = 0xD;  // keyboard Enter
	const char KEY_CTRL  = 0x11; // keyboard Ctrl
	const char KEY_E     = 0x45; // keyboard E
	const char KEY_M     = 0x4D; // keyboard M


	if (nChar == KEY_UP)
		c_PacMan.SetMovingUp(true);
	if (nChar == KEY_DOWN)
		c_PacMan.SetMovingDown(true);
	if (nChar == KEY_LEFT)
		c_PacMan.SetMovingLeft(true);
	if (nChar == KEY_RIGHT)
		c_PacMan.SetMovingRight(true);

	// 組合鍵 - 跳至下一關
	if (nChar == KEY_ENTER) {
		if (myLevel.getLevel() < NUMMAPS) {
			c_PacMan.restart();
			for (int i = 0; i < 4; i++) {
				ghost[i].restart();
			}
			remainFoods = 0;
		}
		ctrlDown = false;
	}

	if (nChar == KEY_CTRL) ctrlDown = true;
	else if (nChar != KEY_E && nChar != KEY_M && nChar != KEY_ENTER) {
		ctrlDown = false;
	}
	
	// 組合鍵 - 跳至最後關卡
	if (ctrlDown && nChar == KEY_E) {
		c_PacMan.restart();
		ghost[0].SetTopLeft(MAP_START + 4 * BITMAP_SIZE, MAP_START + 5 * BITMAP_SIZE);
		ghost[1].SetTopLeft(MAP_START + 4 * BITMAP_SIZE, MAP_START + 20 * BITMAP_SIZE);
		ghost[2].SetTopLeft(MAP_START + 18 * BITMAP_SIZE, MAP_START + 28 * BITMAP_SIZE);
		ghost[3].SetTopLeft(MAP_START + 26 * BITMAP_SIZE, MAP_START + 26 * BITMAP_SIZE);
		remainFoods = 0;
		gameMap.lastMap();
		myLevel.setLevel(3);
		myScore.setScore(7790);
		c_PacMan.SetLife(0);
		myLife.setLife(0);
		c_PacMan.SetMap(gameMap.GetMap());
		for (int i = 0; i < 4; i++) {
			ghost[i].SetMap(gameMap.GetMap());
		}
		remainFoods = gameMap.getFoodCount();
		ctrlDown = false;
	}
	
	// 組合鍵 - 轉為逃避鬼模式
	if (ctrlDown && nChar == KEY_M) {
		for (int i = 0; i < 4; i++) {
			ghost[i].changeMode(1);
		}
		ctrlDown = false;
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	/*
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(false);
	*/
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	// 顯示地圖
	gameMap.OnShow();
	
	// 顯示Pacman
	c_PacMan.OnShow();
	
	// 轉換狀態
	if (c_PacMan.IsGameover()) {
		GotoGameState(GAME_STATE_OVER);
	}

	if (isCompleted) {
		GotoGameState(GAME_STATE_OVER);
	}

	// 顯示Ghost
	for (int i = 0; i < 4; i++) {
		ghost[i].OnShow();
	}

	// 顯示分數
	myScore.OnShow();

	// 顯示關卡等級
	myLevel.OnShow();

	// 顯示生命值
	myLife.OnShow();
}
}
