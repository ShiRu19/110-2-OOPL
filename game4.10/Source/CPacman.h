namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CPacman
	{
	public:
		CPacman();
		void LoadBitmap();										// 載入圖形
		void SetTopLeft();
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		int  get_x();                                           // 取得x
		int  get_y();                                           // 取得y
		void SetMovingUp(bool flag);                            // 設定是否正在往上移動
		void SetMovingDown(bool flag);                          // 設定是否正在往下移動
		void SetMovingLeft(bool flag);                          // 設定是否正在往左移動
		void SetMovingRight(bool flag);                         // 設定是否正在往右移動
	private:
		CMovingBitmap pic;                                      // 載入角色
		int x, y;
		bool isMovingDown;		                             	// 是否正在往下移動
		bool isMovingLeft;		                             	// 是否正在往左移動
		bool isMovingRight;		                             	// 是否正在往右移動
		bool isMovingUp;		                             	// 是否正在往上移動
	};
}