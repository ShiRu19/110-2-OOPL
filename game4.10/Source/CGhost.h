namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CGolst: Golst class
	/////////////////////////////////////////////////////////////////////////////

	class CGhost
	{
	public:
		CGhost();
		~CGhost();
		void LoadBitmap(int IDB[4][2]);		                    // ���J�ϧ�
		void changeMode(int mode);                              // �����Ҧ�(���`��/���װ�)
		bool isNormalMode();                                    // ���F�����A�O�_�����`���A
		int  GetX1();                                           // ���ox1(���W��)
		int  GetY1();                                           // ���oy1(���W��)
		int  GetX2();                                           // ���ox2(�k�U��)
		int  GetY2();                                           // ���oy2(�k�U��)
		void SetInitXY(int x, int y);                           // �]�w��l��m(��a)
		void SetInitTargetXY(int x, int y);                     // �]�w��l�ؼЦ�m
		void SetTopLeft(int x, int y);

		void GoToDestination(int des_x, int des_y);             // ���ʨ���w�ت��a�����|
		double GetDistance(int x1, int x2, int y1, int y2);     // ���o�U�@�B��ت��a�����u�Z��

		void SetMap(int **map);                                 // ��l�Ʀa��
		int FindMapIndex_X(int x);                              // ���o�y�Цb�x�}����m(X�b)
		int FindMapIndex_Y(int y);                              // ���o�y�Цb�x�}����m(Y�b)
		void GetMapIndex();                                     // ���o���W���Υk�U���b�a�Ϫ��y��

		void restart();                                         // Pacman���`�Τ������d�ɡA�^���a
		void OnMove(int pacman_x, int pacman_y);				// ����
		void OnShow();											// �N�ϧζK��e��
	private:
		CAnimation animation_1;                                 // ���F�ʵe_�W
		CAnimation animation_2;                                 // ���F�ʵe_�U
		CAnimation animation_3;                                 // ���F�ʵe_��
		CAnimation animation_4;                                 // ���F�ʵe_�k
		CAnimation animation_avoid;                             // ���׺��F�ʵe_�`�Ŧ�
		CAnimation animation_change;                            // ��í�w���F�ʵe_�`��+�զ���
		CAnimation animation_eyes;                              // ���`���F
		CAnimation *animation;                                  // �ثe��V�ʵe

		int init_x, init_y;                                     // ��l��m(��a)
		int x, y;                                               // �ثe��m
		bool isGoOut = false;                                   // ���O�_���}��a
		int init_target_x, init_target_y;                       // ��l�ؼЦ�m
		int avoidTime = 0;                                      // ���ת��A����ɶ�
		int direction = 0;                                      // �樫��V
		bool stop;                                              // Pacman���`�ɼȰ��ʧ@
		double turnUp(int des_x, int des_y);                    // �P�_�O�_�i�V�W���A�æ^�ǤU�@�B�Z���ت��a���Z��
		double turnDown(int des_x, int des_y);                  // �P�_�O�_�i�V�U���A�æ^�ǤU�@�B�Z���ت��a���Z��
		double turnLeft(int des_x, int des_y);                  // �P�_�O�_�i�V�����A�æ^�ǤU�@�B�Z���ت��a���Z��
		double turnRight(int des_x, int des_y);                 // �P�_�O�_�i�V�k���A�æ^�ǤU�@�B�Z���ت��a���Z��

		int map[31][27];                                              // �C���a��
		int MapIndex_X1;                                        // Pacman���W�����a�Ϫ��y��(X�b)
		int MapIndex_Y1;                                        // Pacman���W�����a�Ϫ��y��(Y�b)
		int MapIndex_X2;                                        // Pacman�k�U�����a�Ϫ��y��(X�b)
		int MapIndex_Y2;                                        // Pacman�k�U�����a�Ϫ��y��(Y�b)
	};
}