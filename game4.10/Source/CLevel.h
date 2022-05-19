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
		void setLevel(int LV);          // 紀錄關卡等級
		void levelUp();                 // 關卡升級
		int  getLevel();                // 取得關卡等級
	private:
		CMovingBitmap LEVEL_text;       // LEVEL文字
		CInteger myLevel;		        // 關卡等級
	};
}