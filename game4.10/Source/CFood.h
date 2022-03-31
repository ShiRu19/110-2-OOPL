namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CFood
	{
	public:
		CFood();
		bool HitPacman(CPacman *pacman);						// 是否碰到Pacman
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void SetTopLeft(int x, int y);
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定圓心的座標
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetDelay(int d);									// 設定旋轉的速度
	protected:
		CMovingBitmap food;			// food的圖
		// CMovingBitmap bmp_center;	// 圓心的圖			
		int x, y;					// food的座標
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}