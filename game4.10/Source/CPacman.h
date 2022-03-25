namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CPacman
	{
	public:
		CPacman();
		void LoadBitmap();										// ���J�ϧ�
		void SetTopLeft();
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		int  get_x();                                           // ���ox
		int  get_y();                                           // ���oy
		void SetMovingUp(bool flag);                            // �]�w�O�_���b���W����
		void SetMovingDown(bool flag);                          // �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);                          // �]�w�O�_���b��������
		void SetMovingRight(bool flag);                         // �]�w�O�_���b���k����
	private:
		//CMovingBitmap pic;                                    // ���J����
		CAnimation animation_0;                                 // Pacman���ʵe_�R��A(�w�]�V�k)
		CAnimation animation_1;                                 // Pacman���ʵe_�V�W
		CAnimation animation_2;                                 // Pacman���ʵe_�V�U
		CAnimation animation_3;                                 // Pacman���ʵe_�V��
		CAnimation animation_4;                                 // Pacman���ʵe_�V�k
		CAnimation *animation = &animation_0;                   // ��ePacman�ʵe��V
		int x, y;
		int move;                                               // ���ʤ�V
		bool isMovingDown;		                             	// �O�_���b���U����
		bool isMovingLeft;		                             	// �O�_���b��������
		bool isMovingRight;		                             	// �O�_���b���k����
		bool isMovingUp;		                             	// �O�_���b���W����
	};
}