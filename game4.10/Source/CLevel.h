namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CLevel: Level class
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