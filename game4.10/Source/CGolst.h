namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CGolst
	{
	public:
		CGolst();
		void LoadBitmap(int IDB);										// ���J�ϧ�
		void CGolst::SetTopLeft(int x, int y);
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
	private:
		CMovingBitmap pic;                                      // ���J����
		int x, y;
	};
}