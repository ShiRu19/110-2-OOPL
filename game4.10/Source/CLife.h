namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 硂class矗ㄑ魁ネ㏑
	// 来碞э糶Θ祘Α
	/////////////////////////////////////////////////////////////////////////////

	class CLife
	{
	public:
		CLife();
		void LoadBitmap();
		void SetTopLeft();
		void OnShow();
		void setLife(int life);         // 魁ネ㏑计秖
		int  getLife();                 // 眔ネ㏑计秖
	private:
		CMovingBitmap LIFE_multi;       // Life X 腹
		CInteger myLife;                // ネ㏑计秖
	};
}