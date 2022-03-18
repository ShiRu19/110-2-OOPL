namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CElf
	{
	public:
		CElf();
		void LoadBitmap(int IDB);										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
	private:
		CMovingBitmap pic;                                      // 載入角色
		int x, y;
	};
}