namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CLife;
	class CGhost;

	class CPacman
	{
	public:
		CPacman();
		bool HitGhost(CGhost *ghost);    						// 是否碰到正常的ghost
		bool IsAlive();                                         // 是否活著
		bool IsGameover();                                      // 遊戲是否結束 (生命值<0時)
		void SetIsAlive(bool alive);                            // 設定是否活著
		void LoadBitmap();										// 載入圖形
		void SetTopLeft();
		void OnMove();								         	// 移動
		void OnShow();											// 將圖形貼到畫面
		int  GetLife();                                         // 目前生命值
		
		void SetInitXY(int x, int y);                           // 設定初始位置
		int  GetX1();                                           // 取得x1(左上角)
		int  GetY1();                                           // 取得y1(左上角)
		int  GetX2();                                           // 取得x2(右下角)
		int  GetY2();                                           // 取得y2(右下角)
		void GetMapIndex();                                     // 取得左上角及右下角在地圖的座標

		void SetMovingUp(bool flag);                            // 設定是否正在往上移動
		void SetMovingDown(bool flag);                          // 設定是否正在往下移動
		void SetMovingLeft(bool flag);                          // 設定是否正在往左移動
		void SetMovingRight(bool flag);                         // 設定是否正在往右移動

		void SetMap(int **map);                                 // 初始化地圖
		int FindMapIndex_X(int x);                              // 取得座標在矩陣的位置(X軸)
		int FindMapIndex_Y(int y);                              // 取得座標在矩陣的位置(Y軸)
	private:
		//CMovingBitmap pic;                                    // 載入角色
		CAnimation animation_stop_1;                            // Pacman的動畫_靜止狀態(預設向上)
		CAnimation animation_stop_2;                            // Pacman的動畫_靜止狀態(預設向下)
		CAnimation animation_stop_3;                            // Pacman的動畫_靜止狀態(預設向左)
		CAnimation animation_stop_4;                            // Pacman的動畫_靜止狀態(預設向右)
		CAnimation animation_1;                                 // Pacman的動畫_向上
		CAnimation animation_2;                                 // Pacman的動畫_向下
		CAnimation animation_3;                                 // Pacman的動畫_向左
		CAnimation animation_4;                                 // Pacman的動畫_向右
		CAnimation animation_die;                               // Pacman的動畫_死亡
		CAnimation *animation = &animation_stop_4;              // 當前Pacman動畫方向(預設向右)

		void restart();                                         // 失去生命時，關卡重來
		int  delay = 0;                                         // 等待狀態結束
		int  myLife = 4;

		int init_X, init_Y;                                     // Pacman初始位置
		int x, y;                                               // Pacman目前位置
		int move;                                               // 移動方向
		bool isMovingDown;		                             	// 是否正在往下移動
		bool isMovingLeft;		                             	// 是否正在往左移動
		bool isMovingRight;		                             	// 是否正在往右移動
		bool isMovingUp;		                             	// 是否正在往上移動
		bool isStop = false;                                    // 是否撞牆停止移動

		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);  // 檢查是否有交集
		bool is_alive;                                          // 生命狀態
		bool is_gameover = false;                               // 遊戲結束
		
		int **map;                                              // 遊戲地圖
		int MapIndex_X1;                                        // Pacman左上角位於地圖的座標(X軸)
		int MapIndex_Y1;                                        // Pacman左上角位於地圖的座標(Y軸)
		int MapIndex_X2;                                        // Pacman右下角位於地圖的座標(X軸)
		int MapIndex_Y2;                                        // Pacman右下角位於地圖的座標(Y軸)
		int wall_pixel;                                         // 牆壁位置
	};
}