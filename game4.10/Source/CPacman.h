namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CPacman
	{
	public:
		CPacman();
		bool HitGhost(CGhost *ghost);    						// �O�_�I�쥿�`��ghost
		bool IsAlive();                                         // �O�_����
		void SetIsAlive(bool alive);                            // �]�w�O�_����
		void LoadBitmap();										// ���J�ϧ�
		void SetTopLeft();
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��

		int  GetX1();                                           // ���ox1(���W��)
		int  GetY1();                                           // ���oy1(���W��)
		int  GetX2();                                           // ���ox2(�k�U��)
		int  GetY2();                                           // ���oy2(�k�U��)
		void SetMovingUp(bool flag);                            // �]�w�O�_���b���W����
		void SetMovingDown(bool flag);                          // �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);                          // �]�w�O�_���b��������
		void SetMovingRight(bool flag);                         // �]�w�O�_���b���k����
	private:
		//CMovingBitmap pic;                                    // ���J����
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
		int x, y;
		int move;                                               // ���ʤ�V
		bool isMovingDown;		                             	// �O�_���b���U����
		bool isMovingLeft;		                             	// �O�_���b��������
		bool isMovingRight;		                             	// �O�_���b���k����
		bool isMovingUp;		                             	// �O�_���b���W����

		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);  // �ˬd�O�_���涰
		bool is_alive;                                          // �ͩR���A
		bool gameover = false;                                  // �C������
	};
}