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

CGameStateInit::CGameStateInit(CGame *g): CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	isAbout = false;
	for (int i = 0; i < 3; i++) {
		label[i] = false;
	}

	logo.LoadBitmap(IDB_STARTLOGO);
	startGame.LoadBitmap(IDB_START_STARTGAME);
	about.LoadBitmap(IDB_START_ABOUT);
	about_gameContent.LoadBitmap(IDB_START_ABOUT_GAMECONTENT);
	about_gameOperation.LoadBitmap(IDB_START_ABOUT_GAMEOPERATION);
	about_gameCombination.LoadBitmap(IDB_START_ABOUT_GAMECOMBINATION);
	back.LoadBitmap(IDB_START_ABOUT_BACK);
	label_gameContent.LoadBitmap(IDB_LABEL_GAMECONTENT);
	label_operation.LoadBitmap(IDB_LABEL_OPERATION);
	label_combination.LoadBitmap(IDB_LABEL_COMBINATION);

	// LEFT
	Pacman_left.AddBitmap(IDB_PACMAN_LEFT_1, RGB(255, 255, 255));           //�V��_open
	Pacman_left.AddBitmap(IDB_PACMAN_LEFT_2, RGB(255, 255, 255));           //�V��_close
	Pacman_x = (SIZE_X - startGame.Width()) / 2 + startGame.Width();
	Pacman_left.SetTopLeft(Pacman_x, SIZE_Y * 4 / 8);
	// RIGHT
	Pacman_right.AddBitmap(IDB_PACMAN_RIGHT_1, RGB(255, 255, 255));          //�V�k_open
	Pacman_right.AddBitmap(IDB_PACMAN_RIGHT_2, RGB(255, 255, 255));          //�V�k_close
	Pacman_x = (SIZE_X - startGame.Width()) / 2;
	Pacman_right.SetTopLeft(Pacman_x, SIZE_Y * 4 / 8);
	isPacmanRight = true;

	startGame_x1 = (SIZE_X - startGame.Width()) / 2;
	startGame_y1 = SIZE_Y * 6 / 8;
	startGame_x2 = (SIZE_X - startGame.Width()) / 2 + startGame.Width();
	startGame_y2 = SIZE_Y * 6 / 8 + startGame.Height();

	about_x1 = (SIZE_X - about.Width()) / 2;
	about_y1 = SIZE_Y * 7 / 8;
	about_x2 = (SIZE_X - about.Width()) / 2 + about.Width();
	about_y2 = SIZE_Y * 7 / 8 + about.Height();

	back_x1 = 0;
	back_x2 = back.Width();
	back_y1 = 0;
	back_y2 = back.Height();

	content_x1 = 0;
	content_x2 = label_gameContent.Width();
	content_y1 = back_y2;
	content_y2 = back_y2 + label_gameContent.Height();

	operation_x1 = 0;
	operation_x2 = label_operation.Width();
	operation_y1 = content_y2;
	operation_y2 = content_y2 + label_operation.Height();

	combination_x1 = 0;
	combination_x2 = label_combination.Width();
	combination_y1 = operation_y2;
	combination_y2 = operation_y2 + label_combination.Height();
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
	double point_x = point.x;
	double point_y = point.y;
	
	if (!isAbout) {
		if (point_x >= startGame_x1 && point_x <= startGame_x2 && point_y >= startGame_y1 && point_y <= startGame_y2) {
			GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
		}
		else if (point_x >= about_x1 && point_x <= about_x2 && point_y >= about_y1 && point_y <= about_y2) {
			isAbout = true;
			label[0] = true;
		}
	}
	else {
		if (point_x >= back_x1 && point_x <= back_x2 && point_y >= back_y1 && point_y <= back_y2) {
			isAbout = false;
			for (int i = 0; i < 3; i++) {
				label[i] = false;
			}
		}
		
		if (point_x >= content_x1 && point_x <= content_x2 && point_y >= content_y1 && point_y <= content_y2) {
			isAbout = true;
			for (int i = 0; i < 3; i++) {
				label[i] = false;
			}
			label[0] = true;
		}
		
		if (point_x >= operation_x1 && point_x <= operation_x2 && point_y >= operation_y1 && point_y <= operation_y2) {
			isAbout = true;
			for (int i = 0; i < 3; i++) {
				label[i] = false;
			}
			label[1] = true;
		}
		
		if (point_x >= combination_x1 && point_x <= combination_x2 && point_y >= combination_y1 && point_y <= combination_y2) {
			isAbout = true;
			for (int i = 0; i < 3; i++) {
				label[i] = false;
			}
			label[2] = true;
		}
	}
}

void CGameStateInit::OnMove()
{
	if (!isAbout) {
		if (isPacmanRight) {
			Pacman_right.OnMove();
			if (Pacman_x <= (SIZE_X - startGame.Width()) / 2 + startGame.Width()) {
				Pacman_x += 2;
				Pacman_right.SetTopLeft(Pacman_x, SIZE_Y * 4 / 8);
			}
			else {
				isPacmanRight = false;
			}
		}
		else {
			Pacman_left.OnMove();
			if (Pacman_x >= (SIZE_X - startGame.Width()) / 2) {
				Pacman_x -= 2;
				Pacman_left.SetTopLeft(Pacman_x, SIZE_Y * 4 / 8);
			}
			else {
				isPacmanRight = true;
			}
		}
	}
}

void CGameStateInit::OnShow()
{
	if (!isAbout) {
		// �K�Wlogo
		logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y * 2 / 8);
		logo.ShowBitmap();

		// ��� Pacman
		if (isPacmanRight) {
			Pacman_right.OnShow();
			Pacman_left.SetTopLeft((SIZE_X - startGame.Width()) / 2 + startGame.Width(), SIZE_Y * 4 / 8);
		}
		else {
			Pacman_left.OnShow();
			Pacman_right.SetTopLeft((SIZE_X - startGame.Width()) / 2, SIZE_Y * 4 / 8);
		}
		

		// �K�W��r
		startGame.SetTopLeft((SIZE_X - startGame.Width()) / 2, SIZE_Y * 6 / 8);
		startGame.ShowBitmap();
		about.SetTopLeft((SIZE_X - about.Width()) / 2, SIZE_Y * 7 / 8);
		about.ShowBitmap();
	}
	else {
		// �K�W��r
		about.SetTopLeft((SIZE_X - about.Width()) / 2, SIZE_Y / 10);
		about.ShowBitmap();

		// �K�W��^��
		back.SetTopLeft(0, 0);
		back.ShowBitmap();

		// �K�W����
		label_gameContent.SetTopLeft(0, back.Height());
		label_gameContent.ShowBitmap();
		label_operation.SetTopLeft(0, back.Height() + label_gameContent.Height());
		label_operation.ShowBitmap();
		label_combination.SetTopLeft(0, back.Height() + label_gameContent.Height() + label_operation.Height());
		label_combination.ShowBitmap();
		
		// �K�W������r
		if (label[0]) {
			about_gameContent.SetTopLeft((SIZE_X - about_gameContent.Width()) / 2, SIZE_Y * 2 / 10);
			about_gameContent.ShowBitmap();
		}
		else if (label[1]) {
			about_gameOperation.SetTopLeft((SIZE_X - about_gameOperation.Width()) / 2, SIZE_Y * 2 / 10);
			about_gameOperation.ShowBitmap();
		}
		else if (label[2]) {
			about_gameCombination.SetTopLeft((SIZE_X - about_gameCombination.Width()) / 2, SIZE_Y * 2 / 10);
			about_gameCombination.ShowBitmap();
		}
	}

	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	// CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	// CFont f,*fp;
	// f.CreatePointFont(300,"Times New Roman");	// ���� font f; 160���16 point���r
	// fp = pDC->SelectObject(&f);					// ��� font f
	// pDC->SetBkColor(RGB(0,0,0));
	// pDC->SetTextColor(RGB(255,255,0));
	// int mid_y = SIZE_Y / 2;
	
	// string pacman_word = "Pacmac!";
	// int pacman_word_width = (SIZE_X - logo.Width()) / 2 + 10;
	// pDC->TextOut(pacman_word_width, mid_y, "Pacman!");
	// // pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	// /*if (ENABLE_GAME_PAUSE)
	// 	pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	// // pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");*/
	// pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	// CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
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
	runningTime = 0;
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	CAudio::Instance()->Play(AUDIO_START);				// ���� START
	//hits_left.SetInteger(0);
	//hits_left.SetTopLeft(590, 0);
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	runningTime++;

	if (runningTime < 120) {
		myScore.setScore(0);
		return;
	}
	
	//
	// �P�_Pacman�O�_�I��food
	//
	vector<CFood *>* allFoods = gameMap.getAllFoods();
	for (int i = 0; i < gameMap.getFoodCount(); i++) 
	{
		if ((*allFoods->at(i)).IsAlive() && (*allFoods->at(i)).HitPacman(&c_PacMan))
		{
			(*allFoods->at(i)).SetIsAlive(false);
			remainFoods--;
			myScore.setScore(myScore.getScore() + (*allFoods->at(i)).GetScore()); // �o��
			// �p�G�O�I��j�]��
			if ((*allFoods->at(i)).GetScore() == 50) 
			{
				// ����Y��j�]��������
				CAudio::Instance()->Stop(AUDIO_EAT);
				CAudio::Instance()->Play(AUDIO_EATGHOST);
				// ghost�ন���װ��Ҧ�
				for (int i = 0; i < 4; i++) 
				{
					ghost[i].changeMode(1);
				}
			}
			else
			{
				CAudio::Instance()->Play(AUDIO_EAT);				// ����Y���l������
			}
		}
	}
	
	//
	// �P�_Pacman�O�_�I��ghost
	//
	for (int i = 0; i < 4; i++) 
	{
		// �Y�I�쥿�`���APacman���`
		if (ghost[i].isNormalMode()) 
		{
			if (c_PacMan.IsAlive() && c_PacMan.HitGhost(&ghost[i])) 
			{
				c_PacMan.SetIsAlive(false); // Pacman���`
				c_PacMan.SetLastKey(0);
				CAudio::Instance()->Play(AUDIO_DEADTH);
				initFoods = remainFoods;
			}
		}
		// �Y�I����װ��Τ�í�w���APacman�o��
		else if (ghost[i].isNormalMode() != true)
		{
			if (c_PacMan.IsAlive() && c_PacMan.HitGhost(&ghost[i])) 
			{
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
		runningTime = 0;
		CAudio::Instance()->Play(AUDIO_START);				// ���� START
		return;
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
	// ���JAUDIO
	CAudio::Instance()->Load(AUDIO_START,  "sounds\\pacman_beginning.wav");		// ���J�s��0(�C���}�l)���n��pacman_beginning.wav
	CAudio::Instance()->Load(AUDIO_EAT,  "sounds\\pacman_chomp.wav");			// ���J�s��1(�Y���l)���n��pacman_chomp.wav
	CAudio::Instance()->Load(AUDIO_DEADTH,  "sounds\\pacman_death.wav");		// ���J�s��2(�I�찭���`)���n��pacman_death.wav
	CAudio::Instance()->Load(AUDIO_EATGHOST, "sounds\\pacman_eatghost.wav");	// ���J�s��3(�I��j���l)���n��pacman_eatghost.wav
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
	//
	// ���J�a��
	gameMap.SetMap(MAP_1);
	gameMap.LoadBitmap();

	//bitMap.LoadBitmap(IDB_MAP1);
	//bitMap.LoadBitmap(IDB_MAP2);
	//bitMap.LoadBitmap(IDB_MAP3);
	//bitMap.SetTopLeft(MAP_START, MAP_START);

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
	int red[4][2] = 
	{
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

	completed.LoadBitmap(IDB_OVER_COMPLETED);
	gameover.LoadBitmap(IDB_OVER_GAMEOVER);
	completed.SetTopLeft(MAP_START + 12 * BITMAP_SIZE, MAP_START + 17 * BITMAP_SIZE);
	gameover.SetTopLeft(MAP_START + 12 * BITMAP_SIZE, MAP_START + 17 * BITMAP_SIZE);
	overDelay = 0;
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_ENTER = 0xD;  // keyboard Enter
	const char KEY_CTRL  = 0x11; // keyboard Ctrl
	const char KEY_E     = 0x45; // keyboard E
	const char KEY_M     = 0x4D; // keyboard M


	//c_PacMan.SetLastKey(nChar);
	
	if (nChar == KEY_UP)
		c_PacMan.SetLastKey(0);
	if (nChar == KEY_DOWN)
		c_PacMan.SetLastKey(1);
	if (nChar == KEY_LEFT)
		c_PacMan.SetLastKey(2);
	if (nChar == KEY_RIGHT)
		c_PacMan.SetLastKey(3);

	if (nChar == KEY_ENTER) 
	{
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
	
	// �զX�� - ���̫ܳ����d
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
	
	// �զX�� - �ର�k�װ��Ҧ�
	if (ctrlDown && nChar == KEY_M) {
		for (int i = 0; i < 4; i++) {
			ghost[i].changeMode(1);
		}
		ctrlDown = false;
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	//bitMap.ShowBitmap();
	// ��ܦa��
	gameMap.OnShow();
	//completed.ShowBitmap();

	// �ഫ���A
	if (c_PacMan.IsGameover()) {
		gameover.ShowBitmap();
		overDelay++;
		// �C�������� delay �@�q�ɶ���i�Jover state
		if (overDelay == 40) {
			GotoGameState(GAME_STATE_OVER);
		}
	}
	else {
		// ���Pacman
		c_PacMan.OnShow();

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
