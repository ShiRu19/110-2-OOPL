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
		CMovingBitmap pic;                                      // ���J����
		int x, y;
		bool isMovingDown;		                             	// �O�_���b���U����
		bool isMovingLeft;		                             	// �O�_���b��������
		bool isMovingRight;		                             	// �O�_���b���k����
		bool isMovingUp;		                             	// �O�_���b���W����
	};
}