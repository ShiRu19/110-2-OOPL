namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

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