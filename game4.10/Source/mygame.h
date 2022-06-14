/*
 * mygame.h: ���ɮ��x�C��������class��interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"

#include "CGhost.h"
#include "CGameMap.h"
#include "CPacman.h"
#include "CFood.h"
#include "CScore.h"
#include "CLevel.h"
#include "CLife.h"

using namespace std;

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID 
	{							// �w�q�U�ح��Ī��s��
		AUDIO_START,			// 0
		AUDIO_EAT,				// 1
		AUDIO_DEADTH,			// 2
		AUDIO_EATGHOST			// 3
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo;								// csie��logo
		CMovingBitmap startGame;                        // start game ����
		CMovingBitmap about;                            // about ����
		CMovingBitmap about_gameContent;                // �C�����e����
		CMovingBitmap about_gameOperation;              // �C���ާ@����
		CMovingBitmap about_gameCombination;            // �C���զX�K�޻���
		CMovingBitmap back;                             // �^��D����
		CMovingBitmap label_gameContent;                // �C�����e����
		CMovingBitmap label_operation;                  // �ާ@�������
		CMovingBitmap label_combination;                // �զX�������
		bool          isAbout;                          // �O�_�babout����
		bool          label[3];                         // �ثe�I������

		double startGame_x1;
		double startGame_y1;
		double startGame_x2;
		double startGame_y2;

		double about_x1;
		double about_y1;
		double about_x2;
		double about_y2;

		double back_x1;
		double back_x2;
		double back_y1;
		double back_y2;

		double content_x1;
		double content_x2;
		double content_y1;
		double content_y2;

		double operation_x1;
		double operation_x2;
		double operation_y1;
		double operation_y2;

		double combination_x1;
		double combination_x2;
		double combination_y1;
		double combination_y2;
	};




	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CGameMap        gameMap;    // �a��
		const int       NUMMAPS;    // �a�Ϫ��`��
		const int		NUMBALLS;	// �y���`��
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		CBall			*ball;		// �y���}�C
		CMovingBitmap	corner;		// ������
		CEraser			eraser;		// ��l
		CInteger		hits_left;	// �ѤU��������
		CBouncingBall   bball;		// ���мu�����y
		CMovingBitmap   PacMan;     // ����p���F
		int             picX, picY; // PacMan�y�Ц�m
		CPacman         c_PacMan;   // ����p���F
		CGhost          *ghost;     // ���F��
		vector<CFood>   foods;      // �p���l+�j�]��
		int             initFoods;  // ��l���l�ƶq
		int             remainFoods;// ���W�Ѿl���l
		CScore          myScore;    // �`����
		CLevel          myLevel;    // ���d����
		CLife           myLife;     // �ͩR��
		int             ghostDelay; // ���F�X�o��delay�ɶ�
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
	};

}