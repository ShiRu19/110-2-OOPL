namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �H�Uclass���C���U�Ө���
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
