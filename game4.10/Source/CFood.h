namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CFood: Food class
	/////////////////////////////////////////////////////////////////////////////

	class CPacman;

	class CFood
	{
	public:
		CFood();
		CFood(int score);
		bool HitPacman(CPacman *pacman);						// 是否碰到Pacman
		bool IsAlive();											// 是否活著
		void LoadBitmap(int IDB1, int IDB2);					// 載入圖形
		void SetTopLeft(int x, int y);
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		int  GetScore();                                        // 回傳food的分數
		void SetXY(int nx, int ny);								// 設定圓心的座標
		void SetIsAlive(bool alive);							// 設定是否活著
	protected:
		CAnimation foods;			// food的圖		
		int x, y;					// food的座標
		bool is_alive;				// 是否活著
		int score;                  // food的分數
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}