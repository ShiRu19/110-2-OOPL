namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CFood;
	class CPacman;

	enum MAP_ID					// 定義各種地圖的編號
	{
		MAP_BLUE,				// 0
		MAP_PINK,				// 1
		MAP_ORANGE				// 2
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
		vector<CFood>* getAllFoods();	// 取得所有小豆子
		int **GetMap();					// 取得地圖
	protected:
		CMovingBitmap wall, Food;		// 構成整個地圖的小地圖，分別有牆壁跟豆子
		vector<CFood> allFoods;
		int **map;						// 構成地圖的陣列
		const int X, Y;					// 大地圖左上角的座標
		const int MW, MH;				// 小地圖的長跟寬
		int foodCount;					// 小豆子數量
	};
}