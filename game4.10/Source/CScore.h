namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CScore: Score class
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