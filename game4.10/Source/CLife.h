namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѭ����ͩR��
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CLife
	{
	public:
		CLife();
		void LoadBitmap();
		void SetTopLeft();
		void OnShow();
		void setLife(int life);         // �����ͩR�ƶq
		int  getLife();                 // ���o�ͩR�ƶq
	private:
		CMovingBitmap Pacman_icon[4];   // Pacman�Ϥ����
		CMovingBitmap Life_multi;       // Life�� X ��
		CInteger myLife;                // �ͩR�ƶq
	};
}