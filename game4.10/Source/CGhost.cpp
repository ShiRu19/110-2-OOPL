#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGhost.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CGolst: Golst class
	/////////////////////////////////////////////////////////////////////////////

	// Golst
	CGhost::CGhost() {
	}

	void CGhost::SetInitXY(int x, int y) {
		init_x = x;
		init_y = y;
		this->x = init_x;
		this->y = init_y;
	}

	void CGhost::OnMove() {
		animation->OnMove();

		if (animation == &animation_eyes) {
			x = init_x;
			y = init_y;
		}
	}

	void CGhost::LoadBitmap(int IDB[4][2]) {
		// up
		animation_1.AddBitmap(IDB[0][0], RGB(0, 0, 0));
		animation_1.AddBitmap(IDB[0][1], RGB(0, 0, 0));

		// down
		animation_2.AddBitmap(IDB[1][0], RGB(0, 0, 0));
		animation_2.AddBitmap(IDB[1][1], RGB(0, 0, 0));

		// left
		animation_3.AddBitmap(IDB[2][0], RGB(0, 0, 0));
		animation_3.AddBitmap(IDB[2][1], RGB(0, 0, 0));

		// right
		animation_4.AddBitmap(IDB[3][0], RGB(0, 0, 0));
		animation_4.AddBitmap(IDB[3][1], RGB(0, 0, 0));

		// ���װ�
		animation_avoid.AddBitmap(IDB_GHOST_BLUE_1, RGB(0, 0, 0));
		animation_avoid.AddBitmap(IDB_GHOST_BLUE_2, RGB(0, 0, 0));

		// ��í�w�� (���װ��ܥ��`��������í�w���A)
		animation_change.AddBitmap(IDB_GHOST_BLUE_1, RGB(0, 0, 0));
		animation_change.AddBitmap(IDB_GHOST_WHITE_2, RGB(0, 0, 0));

		// ����
		animation_eyes.AddBitmap(IDB_GHOST_EYES_DOWN, RGB(0, 0, 0));
	}
	
	//
	// �����������A
	// 0 => ���� to ���`��
	// 1 => ���`�� to ���װ�
	// 2 => ���װ� to ��í�w��
	// 3 => ��í�w�� to ����
	//
	void CGhost::changeMode(int mode) {
		if (mode == 0) animation = &animation_4;           // ���`��
		else if (mode == 1) animation = &animation_avoid;  // ���װ�
		else if (mode == 2) animation = &animation_change; // ��í�w��
		else if (mode == 3) animation = &animation_eyes;   // ����
	}

	bool CGhost::isNormalMode() {
		if (animation == &animation_avoid || animation == &animation_change || animation == &animation_eyes) {
			return false;
		}
		return true;
	}

	int CGhost::GetX1() {
		return x;
	}
	
	int CGhost::GetY1() {
		return y;
	}

	int CGhost::GetX2() {
		return x + animation->Width();
	}

	int CGhost::GetY2() {
		return y + animation->Height();
	}

	void CGhost::SetTopLeft(int x, int y) {
		animation->SetTopLeft(x, y);
		this->x = x;
		this->y = y;
	}

	void CGhost::OnShow() {
		// ***************************
		// * ���A�����שΤ�í�w��
		// ***************************
		if (animation == &animation_avoid || animation == &animation_change) {
			avoidTime++;
		}
		
		// ���׬�8���A���װ��ର��í�w���A
		if (avoidTime == 180) {
			changeMode(2);
		}
		// �A�g�L��3��A�q��í�w���A�^�쥿�`���A
		if (avoidTime == 230) {
			avoidTime = 0;
			changeMode(0);
		}

		// ************************************
		// * ���A�����`�� (animation_eyes)
		// ************************************
		if (animation == &animation_eyes) {
			if (x == init_x && y == init_y) {
				animation = &animation_1;
			}
		}

		animation->SetTopLeft(x,y);
		animation->OnShow();
	}
}