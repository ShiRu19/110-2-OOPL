namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CLevel
	{
	public:
		CLevel();
		void LoadBitmap();
		void SetTopLeft();
		void OnShow();
		void setLevel(int LV);          // 紀錄關卡等級
		int  getLevel();                // 取得關卡等級
	private:
		CMovingBitmap LEVEL_text;       // LEVEL文字
		CInteger myLevel;		        // 關卡等級
	};
}