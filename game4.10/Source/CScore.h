namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
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