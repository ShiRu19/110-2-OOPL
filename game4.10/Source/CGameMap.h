namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CGameMap: Map class
	/////////////////////////////////////////////////////////////////////////////

	class CFood;
	class CPacman;

	enum MAP_ID					// 定義各種地圖的編號
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
		void LoadBitmap();				// 載入地圖
		void OnShow();					// 顯示地圖
		void SetMap(int maptype);		// 選擇地圖
		int  getFoodCount();			// 取得小豆子數量
		vector<CFood *>* getAllFoods();	// 取得所有小豆子
		int **GetMap();					// 取得地圖
	protected:
		CMovingBitmap wall;	        	// 牆壁
		vector<CFood *> allFoods;       // 小豆子and大魔豆
		int **map;						// 構成地圖的陣列
		const int X, Y;					// 大地圖左上角的座標
		const int MW, MH;				// 小地圖的長跟寬
		int foodCount;					// 小豆子數量
		int MapType;					// 地圖類型
	};
}