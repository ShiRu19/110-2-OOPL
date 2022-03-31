namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CFood
	{
	public:
		CFood();
		bool HitPacman(CPacman *pacman);						// �O�_�I��Pacman
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void SetTopLeft(int x, int y);
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void SetDelay(int d);									// �]�w���઺�t��
	protected:
		CMovingBitmap food;			// food����
		// CMovingBitmap bmp_center;	// ��ߪ���			
		int x, y;					// food���y��
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}