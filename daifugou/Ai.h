	// ----- ��D���
extern	int Stat ;		// 2:��x�� 1:�x�� -1:�n�� 0:����
extern	int CardNum ;	// �����Ă�J�[�h�̖���
extern	int Card[15][6] ;	// ��D�̖���:
					// �@[1]-3  [2]-4 [3]-5  [4]-6  [5]-7  [6]-8 [7]-9
					//   [8]-10 [9]-J [10]-Q [11]-K [12]-A [13]-2
					//   [14]-�W���[�J�[�̖���

	// ----- ��D���
extern	int FieldCard[13] ;			// ��D�̃J�[�h�ԍ�
extern	int FieldNum ;			// ��D�̃J�[�h����
extern	int UseNum ;			// ����܂łɏ�ɏo���ꂽ�J�[�h�̖���
extern	int UseCard[15] ;		// ����܂łɏ�ɏo���ꂽ�e�J�[�h�̖���:
							// �@[1]-3  [2]-4 [3]-5  [4]-6  [5]-7  [6]-8 [7]-9
							//   [8]-10 [9]-J [10]-Q [11]-K [12]-A [13]-2
							//   [14]-�W���[�J�[�̖���
							//   [0]�ɂ�UseNum�Ɠ����l�������Ă���B

	// ----- ���v���C���[���
extern	int PlayerNum ;			// �Q�[�����̃v���C���[��(�������܂܂Ȃ�)
extern	int PlayerCard[5] ;		// ���v���C���[�̎c��J�[�h����[0]�`[PlayerNum-1]

extern void AI() ;

extern int player[3];
extern bool kakumei;
extern int card[55];
extern int w, h;
extern int type, num;
extern int Size[15], type1[15];
extern int types1, num2, num3, pass1;
extern int Size2[14], type2[14], type3[14], Size3[14];
extern int no;
extern bool clockwise;
extern int UseCard2[15];
extern int end;
extern void swap(int a, int b);
extern int pmark[7];
extern int aCard[14];
extern int Del1[55], Del2[55], Del[5], Del3[5], Del4[13];
extern int b;
