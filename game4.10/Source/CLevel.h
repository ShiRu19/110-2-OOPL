namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CLevel
	{
	public:
		CLevel();
		void LoadBitmap();
		void SetTopLeft();
		void OnShow();
		void setLevel(int LV);          // �������d����
		int  getLevel();                // ���o���d����
	private:
		CMovingBitmap LEVEL_text;       // LEVEL��r
		CInteger myLevel;		        // ���d����
	};
}