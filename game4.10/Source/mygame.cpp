/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	logo.LoadBitmap(IDB_BACKGROUND);
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
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
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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

void CGameStateRun::OnMove()							// ���ʹC������
{
	//
	// �P�_Pacman�O�_�I��food
	//
	vector<CFood *>* allFoods = gameMap.getAllFoods();
	for (int i = 0; i < gameMap.getFoodCount(); i++) {
		if ((*allFoods->at(i)).IsAlive() && (*allFoods->at(i)).HitPacman(&c_PacMan)) {
			(*allFoods->at(i)).SetIsAlive(false);
			remainFoods--;
			myScore.setScore(myScore.getScore() + (*allFoods->at(i)).GetScore()); // �o��

			// �p�G�O�I��j�]��
			if ((*allFoods->at(i)).GetScore() == 50) {
				// ghost�ন���װ��Ҧ�
				for (int i = 0; i < 4; i++) {
					ghost[i].changeMode(1);
				}
			}
		}
	}
	
	//
	// �P�_Pacman�O�_�I��ghost
	//
	for (int i = 0; i < 4; i++) {
		// �Y�I�쥿�`���APacman���`
		if (ghost[i].isNormalMode()) {
			if (c_PacMan.IsAlive() && c_PacMan.HitGhost(&ghost[i])) {
				c_PacMan.SetIsAlive(false); // Pacman���`
				initFoods = remainFoods;
			}
		}
		// �Y�I����װ��Τ�í�w���APacman�o��
		else if (ghost[i].isNormalMode() != true) {
			if (c_PacMan.IsAlive() && c_PacMan.HitGhost(&ghost[i])) {
				ghost[i].changeMode(3); // ���ܲ������A
				myScore.setScore(myScore.getScore() + 10); // �o��
			}
		}
	}

	if (!c_PacMan.IsAlive()) {
		if (c_PacMan.GetDelay() == 28) {
			for (int i = 0; i < 4; i++) {
				ghost[i].restart(); // ���s�}�l
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				ghost[i].changeMode(4); // �R��
			}
		}
	}

	//
	// ��s�ثe�ͩR��
	// 
	myLife.setLife(c_PacMan.GetLife());

	//
	// ��s�ثe���d
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
	// ����PacMan
	//
	if(c_PacMan.IsAlive())
		c_PacMan.OnMove();

	//
	// ����ghosts
	//
	double eat_rate = (initFoods - remainFoods - 0.0) / initFoods;

	// ���W�X�o
	ghost[0].OnMove(c_PacMan.GetX1(), c_PacMan.GetY1());

	// ���Y��10�����l�ɥX�o
	if (eat_rate >= 0.03) ghost[1].OnMove(c_PacMan.GetX1(), c_PacMan.GetY1());
	else ghost[1].OnMove(-1, -1);

	// ���Y��30�����l�ɥX�o
	if (eat_rate >= 0.1) ghost[2].OnMove(c_PacMan.GetX1(), c_PacMan.GetY1());
	else ghost[2].OnMove(-1, -1);

	// ���Y��40�����l�ɥX�o
	if (eat_rate >= 0.13) ghost[3].OnMove(c_PacMan.GetX1(), c_PacMan.GetY1());
	else ghost[3].OnMove(-1, -1);
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	//ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	//background.LoadBitmap(IDB_BACKGROUND);					// ���J�I�����ϧ�
	//background.SetTopLeft(50, 50);
	//background.ShowBitmap();
	//
	// ��������Loading�ʧ@�A�����i��
	//
	//ShowInitProgress(50);
	//Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	// help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�			
	// CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	// CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	// CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
	//
	
	// ���J�a��
	gameMap.SetMap(MAP_BLUE);
	gameMap.LoadBitmap();

	// ���JPacMan
	c_PacMan.LoadBitmap();
	c_PacMan.SetInitXY(14, 17);
	c_PacMan.SetMap(gameMap.GetMap());

	// ���J���l��
	remainFoods = gameMap.getFoodCount();

	// ���JScore��r
	myScore.LoadBitmap();

	// ���JLevel��r
	myLevel.LoadBitmap();

	// ���JLife�ϥ�
	myLife.LoadBitmap();

	// ���J red ghost
	int red[4][2] = {
		{ IDB_GHOST_RED_DOWN_1, IDB_GHOST_RED_DOWN_2 },
		{ IDB_GHOST_RED_DOWN_1, IDB_GHOST_RED_DOWN_2 },
		{ IDB_GHOST_RED_LEFT_1, IDB_GHOST_RED_LEFT_2 },
		{ IDB_GHOST_RED_RIGHT_1, IDB_GHOST_RED_RIGHT_2 } };
	ghost[0].LoadBitmap(red);
	ghost[0].SetInitXY(MAP_START + 12 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[0].SetInitTargetXY(MAP_START + 14 * BITMAP_SIZE, MAP_START + 11 * BITMAP_SIZE);
	ghost[0].SetMap(gameMap.GetMap());

	// ���J blue ghost
	int blue[4][2] = {
		{ IDB_GHOST_BLUE_DOWN_1, IDB_GHOST_BLUE_DOWN_2 },
		{ IDB_GHOST_BLUE_DOWN_1, IDB_GHOST_BLUE_DOWN_2 },
		{ IDB_GHOST_BLUE_LEFT_1, IDB_GHOST_BLUE_LEFT_2 },
		{ IDB_GHOST_BLUE_RIGHT_1, IDB_GHOST_BLUE_RIGHT_2 } };
	ghost[1].LoadBitmap(blue);
	ghost[1].SetInitXY(MAP_START + 13 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[1].SetInitTargetXY(MAP_START + 14 * BITMAP_SIZE, MAP_START + 11 * BITMAP_SIZE);
	ghost[1].SetMap(gameMap.GetMap());

	// ���J pink ghost
	int pink[4][2] = {
		{ IDB_GHOST_PINK_DOWN_1, IDB_GHOST_PINK_DOWN_2 },
		{ IDB_GHOST_PINK_DOWN_1, IDB_GHOST_PINK_DOWN_2 },
		{ IDB_GHOST_PINK_LEFT_1, IDB_GHOST_PINK_LEFT_2 },
		{ IDB_GHOST_PINK_RIGHT_1, IDB_GHOST_PINK_RIGHT_2 } };
	ghost[2].LoadBitmap(pink);
	ghost[2].SetInitXY(MAP_START + 14 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[2].SetInitTargetXY(MAP_START + 13 * BITMAP_SIZE, MAP_START + 11 * BITMAP_SIZE);
	ghost[2].SetMap(gameMap.GetMap());

	// ���J orange ghost
	int orange[4][2] = {
		{ IDB_GHOST_ORANGE_DOWN_1, IDB_GHOST_ORANGE_DOWN_2 },
		{ IDB_GHOST_ORANGE_DOWN_1, IDB_GHOST_ORANGE_DOWN_2 },
		{ IDB_GHOST_ORANGE_LEFT_1, IDB_GHOST_ORANGE_LEFT_2 },
		{ IDB_GHOST_ORANGE_RIGHT_1, IDB_GHOST_ORANGE_RIGHT_2 } };
	ghost[3].LoadBitmap(orange);
	ghost[3].SetInitXY(MAP_START + 15 * BITMAP_SIZE, MAP_START + 14 * BITMAP_SIZE);
	ghost[3].SetInitTargetXY(MAP_START + 13 * BITMAP_SIZE, MAP_START + 11 * BITMAP_SIZE);
	ghost[3].SetMap(gameMap.GetMap());
	
	// �]�m��m
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
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_ENTER = 0xD;  // keyboard Enter
	const char KEY_CTRL  = 0x11; // keyboard Ctrl
	const char KEY_SHIFT = 0x10; // keyboard Shift

	if (nChar == KEY_UP)
		c_PacMan.SetMovingUp(true);
	if (nChar == KEY_DOWN)
		c_PacMan.SetMovingDown(true);
	if (nChar == KEY_LEFT)
		c_PacMan.SetMovingLeft(true);
	if (nChar == KEY_RIGHT)
		c_PacMan.SetMovingRight(true);

	// �զX�� - ���ܤU�@��
	if (nChar == KEY_ENTER) {
		if (myLevel.getLevel() < NUMMAPS) {
			c_PacMan.restart();
			for (int i = 0; i < 4; i++) {
				ghost[i].restart();
			}
			remainFoods = 0;
		}
	}
	
	// �զX�� - ���̫ܳ����d
	if (nChar == KEY_CTRL) {
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
	}
	
	// �զX�� - �ର�k�װ��Ҧ�
	if (nChar == KEY_SHIFT) {
		for (int i = 0; i < 4; i++) {
			ghost[i].changeMode(1);
		}
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//eraser.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	// ��ܦa��
	gameMap.OnShow();
	
	// ���Pacman
	c_PacMan.OnShow();
	
	// �ഫ���A
	if (c_PacMan.IsGameover()) {
		GotoGameState(GAME_STATE_OVER);
	}

	if (isCompleted) {
		GotoGameState(GAME_STATE_OVER);
	}

	// ���Ghost
	for (int i = 0; i < 4; i++) {
		ghost[i].OnShow();
	}

	// ��ܤ���
	myScore.OnShow();

	// ������d����
	myLevel.OnShow();

	// ��ܥͩR��
	myLife.OnShow();
}
}
