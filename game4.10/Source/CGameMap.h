namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	enum MAP_ID					// �w�q�U�ئa�Ϫ��s��
	{
		MAP_BLUE,				// 0
		MAP_PINK,				// 1
		MAP_ORANGE				// 2
	};

	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitmap();			//���J�a��
		void OnShow();				//��ܦa��
		void SetMap(int maptype);	//��ܦa��
	protected:
		CMovingBitmap wall, Food;	//�c����Ӧa�Ϫ��p�a�ϡA���O������򨧤l
		int map[31][28];			//�c���a�Ϫ��}�C
		const int X, Y;				//�j�a�ϥ��W�����y��
		const int MW, MH;			//�p�a�Ϫ�����e
	};
}