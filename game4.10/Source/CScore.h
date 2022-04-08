namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CScore
	{
	public:
		CScore();
		void LoadBitmap();
		void SetTopLeft();
		void OnShow();
		void setScore(int profit);      // 紀錄分數
		int  getScore();                // 取得分數
	private:
		CMovingBitmap SCORE_text;       // Score的lable
		CInteger      myScore;          // 累計的分數
		int           totalScore;       // 總分(integer)
	};
}