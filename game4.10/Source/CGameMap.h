namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CGameMap: Map class
	/////////////////////////////////////////////////////////////////////////////

	class CFood;
	class CPacman;

	enum MAP_ID					// �w�q�U�ئa�Ϫ��s��
	{
		MAP_BLUE,				// 0
		MAP_GREEN,				// 1
		MAP_RED					// 2
	};

	using namespace std;

	class CGameMap
	{
	public:
		CGameMap();
		~CGameMap();
		void LoadBitmap();				// ���J�a��
		void OnShow();					// ��ܦa��
		void SetMap(int maptype);		// ��ܦa��
		int  getFoodCount();			// ���o�p���l�ƶq
		vector<CFood *>* getAllFoods();	// ���o�Ҧ��p���l
		int **GetMap();					// ���o�a��
	protected:
		CMovingBitmap wall;	        	// ���
		vector<CFood *> allFoods;       // �p���land�j�]��
		int **map;						// �c���a�Ϫ��}�C
		const int X, Y;					// �j�a�ϥ��W�����y��
		const int MW, MH;				// �p�a�Ϫ�����e
		int foodCount;					// �p���l�ƶq
		int MapType;					// �a������
	};
}