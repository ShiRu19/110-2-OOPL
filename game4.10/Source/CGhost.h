namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CGhost
	{
	public:
		CGhost();
		void LoadBitmap(int direction, int IDB1, int IDB2);		// 載入圖形
		int  GetX1();                                           // 取得x1(左上角)
		int  GetY1();                                           // 取得y1(左上角)
		int  GetX2();                                           // 取得x2(右下角)
		int  GetY2();                                           // 取得y2(右下角)
		void SetTopLeft(int x, int y);
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
	private:
		CAnimation animation_1;                                 // 精靈動畫_上
		CAnimation animation_2;                                 // 精靈動畫_下
		CAnimation animation_3;                                 // 精靈動畫_左
		CAnimation animation_4;                                 // 精靈動畫_右
		CAnimation *animation = &animation_4;                                  // 目前方向動畫
		int x, y;
	};
}