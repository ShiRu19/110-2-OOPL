namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CGolst: Golst class
	/////////////////////////////////////////////////////////////////////////////

	class CGhost
	{
	public:
		CGhost();
		void LoadBitmap(int IDB[4][2]);		                    // ���J�ϧ�
		void changeMode(int mode);                              // �����Ҧ�(���`��/���װ�)
		bool isNormalMode();                                    // ���F�����A�O�_�����`���A
		int  GetX1();                                           // ���ox1(���W��)
		int  GetY1();                                           // ���oy1(���W��)
		int  GetX2();                                           // ���ox2(�k�U��)
		int  GetY2();                                           // ���oy2(�k�U��)
		void SetInitXY(int x, int y);                           // �]�w��l��m
		void SetTopLeft(int x, int y);
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
	private:
		CAnimation animation_1;                                 // ���F�ʵe_�W
		CAnimation animation_2;                                 // ���F�ʵe_�U
		CAnimation animation_3;                                 // ���F�ʵe_��
		CAnimation animation_4;                                 // ���F�ʵe_�k
		CAnimation animation_avoid;                             // ���׺��F�ʵe_�`�Ŧ�
		CAnimation animation_change;                            // ��í�w���F�ʵe_�`��+�զ���
		CAnimation animation_eyes;                              // ���`���F
		CAnimation *animation = &animation_4;                   // �ثe��V�ʵe

		int init_x, init_y;                                     // ��l��m
		int x, y;                                               // �ثe��m
		int avoidTime = 0;                                      // ���ת��A����ɶ�
	};
}