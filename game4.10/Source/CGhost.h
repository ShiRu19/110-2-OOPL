namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CGhost
	{
	public:
		CGhost();
		void LoadBitmap(int direction, int IDB1, int IDB2);										// ���J�ϧ�
		void CGhost::SetTopLeft(int x, int y);
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
	private:
		CAnimation animation_1;                                 // ���F�ʵe_�W
		CAnimation animation_2;                                 // ���F�ʵe_�U
		CAnimation animation_3;                                 // ���F�ʵe_��
		CAnimation animation_4;                                 // ���F�ʵe_�k
		CAnimation *animation = &animation_4;                                  // �ثe��V�ʵe
		int x, y;
	};
}