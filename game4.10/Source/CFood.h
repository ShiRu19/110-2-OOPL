namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CFood: Food class
	/////////////////////////////////////////////////////////////////////////////

	class CPacman;

	class CFood
	{
	public:
		CFood();
		CFood(int score);
		bool HitPacman(CPacman *pacman);						// �O�_�I��Pacman
		bool IsAlive();											// �O�_����
		void LoadBitmap(int IDB1, int IDB2);					// ���J�ϧ�
		void SetTopLeft(int x, int y);
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		int  GetScore();                                        // �^��food������
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
	protected:
		CAnimation foods;			// food����		
		int x, y;					// food���y��
		bool is_alive;				// �O�_����
		int score;                  // food������
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}