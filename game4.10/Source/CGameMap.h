namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CGameMap: Map class
	/////////////////////////////////////////////////////////////////////////////

	class CFood;
	class CPacman;

	enum MAP_ID					// �w�q�U�ئa�Ϫ��s��
	{
		MAP_1,				// 0
		MAP_2,				// 1
		MAP_3,				// 2
		MAP_END             // 3
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
		void nextMap();					// ������U�@�i�a��
		void lastMap();                 // ������̫�@�i�a��
	protected:
		const int NUMMAPS;              // �`�a�ϼ�
		void setFoods(int map_info[31][28]); // �t�m�a�ϤW���l����m
		CMovingBitmap *walls;       	// ����C��
		CMovingBitmap *currentWall;     // �ثe����C��
		vector<CFood *> allFoods;       // �p���land�j�]��
		int **map;						// �c���a�Ϫ��}�C
		const int X, Y;					// �j�a�ϥ��W�����y��
		const int MW, MH;				// �p�a�Ϫ�����e
		int foodCount;					// �p���l�ƶq
		int MapType;		        	// �a������
		int *gameMaps;                  // �a�϶���
		int currentLevel = 0;           // �ثe�a��
	};
}