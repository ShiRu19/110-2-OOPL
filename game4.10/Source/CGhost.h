namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CGhost
	{
	public:
		CGhost();
		void LoadBitmap(int IDB[4][2]);		                    // ���J�ϧ�
		void changeMode(int mode);                              // �����Ҧ�(���`��/���װ�)
		bool CGhost::isNormalMode();
		int  GetX1();                                           // ���ox1(���W��)
		int  GetY1();                                           // ���oy1(���W��)
		int  GetX2();                                           // ���ox2(�k�U��)
		int  GetY2();                                           // ���oy2(�k�U��)
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
		CAnimation animation_eyes;
		CAnimation *animation = &animation_4;                   // �ثe��V�ʵe
		int x, y;
	};
}