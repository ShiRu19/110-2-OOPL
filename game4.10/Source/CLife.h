namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CLife: Life class
	/////////////////////////////////////////////////////////////////////////////

	class CLife
	{
	public:
		CLife();
		void LoadBitmap();
		void SetTopLeft();
		void OnShow();
		void setLife(int life);         // 紀錄生命數量
		int  getLife();                 // 取得生命數量
	private:
		CMovingBitmap Pacman_icon[4];   // Pacman圖片顯示
		CMovingBitmap Life_multi;       // Life的 X 號
		CInteger myLife;                // 生命數量
	};
}