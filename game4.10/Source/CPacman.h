namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CPacman: Pacman class
	/////////////////////////////////////////////////////////////////////////////

	class CLife;
	class CGhost;

	class CPacman
	{
	public:
		CPacman();
		~CPacman();
		bool HitGhost(CGhost *ghost);    						// �O�_�I�쥿�`��ghost
		bool IsAlive();                                         // �O�_����
		void restart();                                         // ���h�ͩR�Τ������d�ɦ^��_�l�I
		bool IsGameover();                                      // �C���O�_���� (�ͩR��<0��)
		void SetIsAlive(bool alive);                            // �]�w�O�_����
		void LoadBitmap();										// ���J�ϧ�
		void SetTopLeft();
		void OnMove();								         	// ����
		void OnShow();											// �N�ϧζK��e��
		int  GetLife();                                         // �ثe�ͩR��
		
		void SetInitXY(int x, int y);                           // �]�w��l��m
		int  GetX1();                                           // ���ox1(���W��)
		int  GetY1();                                           // ���oy1(���W��)
		int  GetX2();                                           // ���ox2(�k�U��)
		int  GetY2();                                           // ���oy2(�k�U��)
		void GetMapIndex();                                     // ���o���W���Υk�U���b�a�Ϫ��y��

		void SetMovingUp(bool flag);                            // �]�w�O�_���b���W����
		void SetMovingDown(bool flag);                          // �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);                          // �]�w�O�_���b��������
		void SetMovingRight(bool flag);                         // �]�w�O�_���b���k����

		void SetMap(int **map);                                 // ��l�Ʀa��
		int FindMapIndex_X(int x);                              // ���o�y�Цb�x�}����m(X�b)
		int FindMapIndex_Y(int y);                              // ���o�y�Цb�x�}����m(Y�b)
	private:
		CAnimation animation_stop_1;                            // Pacman���ʵe_�R��A(�w�]�V�W)
		CAnimation animation_stop_2;                            // Pacman���ʵe_�R��A(�w�]�V�U)
		CAnimation animation_stop_3;                            // Pacman���ʵe_�R��A(�w�]�V��)
		CAnimation animation_stop_4;                            // Pacman���ʵe_�R��A(�w�]�V�k)
		CAnimation animation_1;                                 // Pacman���ʵe_�V�W
		CAnimation animation_2;                                 // Pacman���ʵe_�V�U
		CAnimation animation_3;                                 // Pacman���ʵe_�V��
		CAnimation animation_4;                                 // Pacman���ʵe_�V�k
		CAnimation animation_die;                               // Pacman���ʵe_���`
		CAnimation *animation = &animation_stop_4;              // ��ePacman�ʵe��V(�w�]�V�k)
		
		int  delay = 0;                                         // ���ݪ��A����
		int  myLife = 4;

		int init_X, init_Y;                                     // Pacman��l��m
		int x, y;                                               // Pacman�ثe��m
		int move;                                               // ���ʤ�V
		bool isMovingDown;		                             	// �O�_���b���U����
		bool isMovingLeft;		                             	// �O�_���b��������
		bool isMovingRight;		                             	// �O�_���b���k����
		bool isMovingUp;		                             	// �O�_���b���W����
		bool isStop = false;                                    // �O�_���𰱤��

		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);  // �ˬd�O�_���涰
		bool is_alive;                                          // �ͩR���A
		bool is_gameover = false;                               // �C������
		
		int **map;                                              // �C���a��
		int MapIndex_X1;                                        // Pacman���W�����a�Ϫ��y��(X�b)
		int MapIndex_Y1;                                        // Pacman���W�����a�Ϫ��y��(Y�b)
		int MapIndex_X2;                                        // Pacman�k�U�����a�Ϫ��y��(X�b)
		int MapIndex_Y2;                                        // Pacman�k�U�����a�Ϫ��y��(Y�b)
		int wall_pixel;                                         // �����m
	};
}