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
		MAP_RED,				// 2
		MAP_RED_END             // 3
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
		void nextMap();					// 切換到下一張地圖
		void lastMap();                 // 切換到最後一張地圖
	protected:
		const int NUMMAPS;              // 總地圖數
		void setFoods(int map_info[31][28]); // 配置地圖上豆子的位置
		CMovingBitmap *walls;       	// 牆壁顏色
		CMovingBitmap *currentWall;     // 目前牆壁顏色
		vector<CFood *> allFoods;       // 小豆子and大魔豆
		int **map;						// 構成地圖的陣列
		const int X, Y;					// 大地圖左上角的座標
		const int MW, MH;				// 小地圖的長跟寬
		int foodCount;					// 小豆子數量
		int MapType;		        	// 地圖類型
		int *gameMaps;                  // 地圖順序
		int currentLevel = 0;           // 目前地圖
	};

}