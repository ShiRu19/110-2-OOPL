namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 以下class為遊戲各個角色
	/////////////////////////////////////////////////////////////////////////////

	class CPacMan {
	public:
		CPacMan();
		void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap pic;
		int x, y;
	};

	class CElf {
	public:
		CElf();
		void LoadBitmap(int IDB);
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap pic;
		int x, y;
	};
}
