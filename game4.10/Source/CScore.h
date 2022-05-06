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
		void setScore(int profit);      // ��������
		int  getScore();                // ���o����
	private:
		CMovingBitmap SCORE_text;       // Score��lable
		CInteger      myScore;          // �֭p������
		int           totalScore;       // �`��(integer)
	};
}