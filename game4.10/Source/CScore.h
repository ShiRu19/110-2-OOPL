namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CScore
	{
	public:
		CScore();
		void setScore(int profit);      // ��������
		int  getScore();                // ���o����
	private:
		int myScore;					// �֭p����
	};
}