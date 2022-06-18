/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
	{							// 定義各種音效的編號
		AUDIO_START,			// 0
		AUDIO_EAT,				// 1
		AUDIO_DEADTH,			// 2
		AUDIO_EATGHOST			// 3
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
		void OnMove();									// 顯示這個狀態的遊戲動畫
	private:
		CAnimation    Pacman_right;                     // Pacman 動畫(右)
		CAnimation    Pacman_left;                      // Pacman 動畫(左)
		CAnimation    ghosts[4];                        // ghost 動畫
		int           Pacman_x;                         // Pacman 位置
		bool          isPacmanRight;                    // Pacman 是否向右

		CMovingBitmap logo;								// csie的logo
		CMovingBitmap startGame;                        // start game 標籤
		CMovingBitmap about;                            // about 標籤
		CMovingBitmap about_gameContent;                // 遊戲內容說明
		CMovingBitmap about_gameOperation;              // 遊戲操作說明
		CMovingBitmap about_gameCombination;            // 遊戲組合密技說明
		CMovingBitmap back;                             // 回到主頁面
		CMovingBitmap label_gameContent;                // 遊戲內容標籤
		CMovingBitmap label_operation;                  // 操作按鍵標籤
		CMovingBitmap label_combination;                // 組合按鍵標籤
		CMovingBitmap author;                           // 作者
		bool          isAbout;                          // 是否在about頁面
		bool          label[3];                         // 目前點擊標籤
		
		double startGame_coordinate[4];                 // Start Game 文字座標
		double about_coordinate[4];                     // About 文字座標
		double back_coordinate[4];                      // back 符號座標
		double content_coordinate[4];                   // 遊戲內容 標籤座標
		double operation_coordinate[4];                 // 遊戲操作 標籤座標
		double combination_coordinate[4];               // 組合密技 標籤座標
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();			  // 設定每次重玩所需的變數
		void OnInit();  				  // 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);	  
	protected:							  
		void OnMove();					  // 移動遊戲元素
		void OnShow();					  // 顯示這個狀態的遊戲畫面
	private:
		const int       NUMMAPS;          // 地圖的總數
		const int		NUMBALLS;	      // 球的總數
		CGameMap        gameMap;          // 地圖
		CMovingBitmap   completed;        // 完成圖
		CMovingBitmap   gameover;         // 失敗圖
		CPacman         c_PacMan;         // 黃色小精靈
		CGhost          ghost[4];         // 幽靈們
		CScore          myScore;          // 總分數
		CLevel          myLevel;          // 關卡等級
		CLife           myLife;           // 生命值
		int             runningTime;      // 執行時間
		int             ghostDelay;       // 幽靈出發的delay時間
		int             stateDelay;       // 進入Over狀態前的Delay
		int             initFoods;        // 原始豆子數量
		int             remainFoods;      // 場上剩餘豆子
		bool            isCompleted;      // 通關
		bool            ctrlDown;         // 是否按下Ctrl鍵
		void            GameRestart();    // 重新開始遊戲
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnInit();
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap Restart;
		CMovingBitmap Exit;
		int counter;	                                // 倒數之計數器
	};
}