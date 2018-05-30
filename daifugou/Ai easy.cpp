#include "Ai.h"

int L0 = 0, L1 = 0, L2 = 0, L3 = 0, L4 = 0, L5 = 0, L6 = 0, L7 = 0;
int group[6];				//�l���g�A�O���g�A�y�A�ƈꖇ�J�[�h������������
double value;


int aCard[14];
int pmark[7], pmark2[7];
int step;
int Stat;		// 2:��x�� 1:�x�� -1:�n�� 0:����
int CardNum;	// �����Ă�J�[�h�̖���
int Card[15][6];	// ��D�̖���:
					// �@[1]-3  [2]-4 [3]-5  [4]-6  [5]-7  [6]-8 [7]-9
					//   [8]-10 [9]-J [10]-Q [11]-K [12]-A [13]-2
					//   [14]-�W���[�J�[�̖���

					// ----- ��D���
int FieldCard[13];			// ��D�̃J�[�h�ԍ�
int FieldNum;			// ��D�̃J�[�h����
int UseNum;			// ����܂łɏ�ɏo���ꂽ�J�[�h�̖���
int UseCard[15];		// ����܂łɏ�ɏo���ꂽ�e�J�[�h�̖���:
						// �@[1]-3  [2]-4 [3]-5  [4]-6  [5]-7  [6]-8 [7]-9
						//   [8]-10 [9]-J [10]-Q [11]-K [12]-A [13]-2
						//   [14]-�W���[�J�[�̖���
						//   [0]�ɂ�UseNum�Ɠ����l�������Ă���B

						// ----- ���v���C���[���
int PlayerNum;			// �Q�[�����̃v���C���[��(�������܂܂Ȃ�)
int PlayerCard[5];		// ���v���C���[�̎c��J�[�h����[0]�`[PlayerNum-1]

void CardGroup(int b, bool d)
{
	//1,2,3,4���J�[�h�̐������ꂼ��v�Z
	int L0, L1, L2 = 0;
	if (b == 1) { group[5] = 1; }
	else { group[5] = 0; }
	for (L0 = 1; L0 <= 13; L0++) {
		for (L1 = 1; L1 <= 4; L1++) {
			if (Card[L0][L1] == 1) {
				L2++;
			}
		}
		switch (L2)
		{
		case 4: group[4]++;
			break;
		case 3: group[3]++;
			break;
		case 2: group[2]++;
			break;
		case 1: group[1]++;
			break;
		}
		L2 = 0;
	}
	//�J�[�h���S���o���I���܂ł̃J�E���g�_�E���B
	if (d != 0)
		step = group[1] + group[2] + group[3] + group[4] + group[5];

}

void reset()
{
	for (L4 = 0; L4 <= 6; L4++) {
		pmark2[L4] = 0;
	}
	L2 = 0, L3 = 0, L4 = 0;
}

//	AiData->FieldNum, AiData->Card[14][5]
//			b					c					
void FieldCardtype(int b, int c)
{																			
											
		switch (b) {														
		case 0:												
				if (c == 1) {												
					num2 = 1;
					aCard[1] = 14;											
					pmark[1] = 5;											
					break;
				}
				else {
					for (L0 = 1; L0 <= 13; L0++) {
						for (L1 = 1; L1 <= 4; L1++) {
							if (Card[L0][L1] == 1) {
								L2++;
								pmark2[L1] = L1;
							}
						}
						if (L2 >0) {
							num2 = L2;
							for (L1 = 1; L1 <= 4; L1++) {
								aCard[L1] = L0;
								if (pmark2[L1] > 0) {
									pmark[L3 + 1] = pmark2[L1];
									L3++;
								}
							}
							reset();
							break;
						}
						reset();
					}
				}
		case 1:
			if (FieldCard[1] == 14)
			{
				num2 = 0;
				break;
			}
			else {
				for (L0 = FieldCard[1] + 1; L0 < 14; L0++) {
					for (L1 = 1; L1 <= 4; L1++) {
						if (Card[L0][L1] == 1) {
							L2++;
							pmark2[L1] = L1;
						}
					}
					if (L2 >= 1) {
						num2 = 1;
						aCard[1] = L0;
						for (L1 = 1; L1 <= 4; L1++) {
							if (pmark2[L1] > 0) {
								pmark[L3 + 1] = pmark2[L1];
								L3++;
							}
						}
						reset();
						break;
					}
					reset();
				}
			}
			break;
		case 2:																//��ԋ����J�[�h�ȊO�̃y�A���o��
			for (L0 = FieldCard[1] + 1; L0 < 14; L0++) {
				for (L1 = 1; L1 <= 4; L1++) {
					if (Card[L0][L1] == 1) {
						L2++;
						pmark2[L1] = L1;
					}
				}
				if (L2 >= 2) {
					num2 = L2;
					for (L4 = 1; L4 < 3; L4++) {
						aCard[L4] = L0;
					}
					for (L1 = 1; L1 <= 4; L1++) {
						if (pmark2[L1] > 0) {
							pmark[L3 + 1] = pmark2[L1];
							L3++;
						}
					}
					reset();
					break;
				}
				reset();
			}
			break;

		case 3:
			if (FieldCard[1] == FieldCard[2] && FieldCard[1] == FieldCard[3]) {
				if (group[3] > 0) {											//2��3�ȊO�̂R���g����������A�R���g��^����ɏo��
					for (L0 = FieldCard[1] + 1; L0 < 14; L0++) {
						for (L1 = 1; L1 <= 4; L1++) {
							if (Card[L0][L1] == 1) {
								L2++;
								pmark2[L1] = L1;
							}
						}
						if (L2 == 3) {
							num2 = L2;
							for (L1 = 1; L1 <= 4; L1++) {
								aCard[L1] = L0;
								if (pmark2[L1] > 0) {
									pmark[L3 + 1] = pmark2[L1];
									L3++;
								}
							}
							reset();
							break;
						}
						reset();
					}
				}
			}
			else if (FieldCard[1] == FieldCard[2] - 1 && FieldCard[1] == FieldCard[3] - 2) {
				for (L1 = 1; L1 <= 4; L1++) {
					for (L0 = FieldCard[FieldNum] + 1; L0 < 14; L0++) {
						if (Card[L0][L1] == 1 && Card[L0 + 1][L1] == 1 && Card[L0 + 2][L1] == 1) {
							num2 = FieldNum;
							for (L2 = 1; L2 <= FieldNum; L2++) {
								pmark[L2] = L1;
								aCard[L2] = L0;
								L0++;
							}
							break;
						}
					}
					if (pmark[1] > 0) { break; }
				}
				L2 = 0;
			}
			break;

		case 4:
			if (FieldCard[1] == FieldCard[2] && FieldCard[1] == FieldCard[3] && FieldCard[1] == FieldCard[4]) {
				if (c == 1) {												//joke ����
					num2 = 1;
					aCard[1] = 14;											//joke �o��
					pmark[1] = 5;											//joke�̃}�[�N ���T
					break;
				}
				else if (c == 0 && group[4] > 0) {							//4���Ԃ�
					for (L0 = FieldCard[1] + 1; L0 < 14; L0++) {
						for (L1 = 1; L1 <= 4; L1++) {
							if (Card[L0][L1] == 1) {
								L2++;
								pmark2[L1] = L1;
							}
						}
						if (L2 == 4) {
							num2 = L2;
							for (L1 = 1; L1 <= 4; L1++) {
								aCard[L1] = L0;
								if (pmark2[L1] > 0) {
									pmark[L3 + 1] = pmark2[L1];
									L3++;
								}
							}
							reset();
							break;
						}
						reset();
					}
				}
			}
			else if (FieldCard[1] == FieldCard[2] - 1 && FieldCard[1] == FieldCard[3] - 2 && FieldCard[1] == FieldCard[4] - 3) {
				for (L1 = 1; L1 <= 4; L1++) {
					for (L0 = FieldCard[FieldNum] + 1; L0 < 14; L0++) {
						if (Card[L0][L1] == 1 && Card[L0 + 1][L1] == 1 && Card[L0 + 2][L1] == 1 && Card[L0 + 3][L1] == 1) {
							num2 = FieldNum;
							for (L2 = 1; L2 <= FieldNum; L2++) {
								pmark[L2] = L1;
								aCard[L2] = L0;
								L0++;
							}
							break;
						}
					}
					if (pmark[1] > 0) { break; }
				}
				L2 = 0;
			}
			break;

		default:															//5���ȏ�̊K�i�̏ꍇ
			if (FieldNum == 5) {
				for (L1 = 1; L1 <= 4; L1++) {
					for (L0 = FieldCard[FieldNum] + 1; L0 <=11; L0++) {
						if (Card[L0][L1] == 1 && Card[L0 + 1][L1] == 1 && Card[L0 + 2][L1] == 1 && Card[L0 + 3][L1] == 1 && Card[L0 + 4][L1] == 1) {
							num2 = FieldNum;								//�����ł́A������ƃY�������B
							for (L2 = 1; L2 <= FieldNum; L2++) {			//�l�����̍��́A�ł��邾���A�Q��A���c��
								pmark[L2] = L1;								//�Ō�̌��߂�D�Ƃ��āA�g����������A
								aCard[L2] = L0;					//���肪34567���o���ꍇ�Ԃ���J�[�h��
								L0++;										//8910JQ��910JQK��2�����Ȃ�
							}
							break;
						}
					}
					if (pmark[1] > 0) { break; }
				}
				L2 = 0;
			}
			break;
		}
	}




void FieldCardtype2(int b, int c)
{																			//�v���̂Ƃ�
																			//�Q�AA�AK����������ꍇ
	switch (b) {														//�v���łȂ��Ƃ�
	case 0:
		if (c == 1) {												//joke ����
			num2 = 1;
			aCard[1] = 14;											//joke �o��
			pmark[1] = 5;											//joke�̃}�[�N ���T
			break;
		}
		else {
			for (L0 = 13; L0 >= 1; L0--) {
				for (L1 = 1; L1 <= 4; L1++) {
					if (Card[L0][L1] == 1) {
						L2++;
						pmark2[L1] = L1;
					}
				}
				if (L2 > 0) {
					num2 = L2;
					for (L1 = 1; L1 <= 4; L1++) {
						aCard[L1] = L0;
						if (pmark2[L1] > 0) {
							pmark[L3 + 1] = pmark2[L1];
							L3++;
						}
					}
					reset();
					break;
				}
				reset();
			}
		}
		break;

	case 1:
		if (FieldCard[1] == 14)
		{
			num2 = 0;
			break;
		}
		for (L0 = FieldCard[1] - 1; L0 >= 1; L0--) {
			for (L1 = 1; L1 <= 4; L1++) {
				if (Card[L0][L1] == 1) {
					L2++;
					pmark2[L1] = L1;
				}
			}
			if (L2 >= 1) {
				num2 = 1;
				aCard[1] = L0;
				for (L1 = 1; L1 <= 4; L1++) {
					if (pmark2[L1] > 0) {
						pmark[L3 + 1] = pmark2[L1];
						L3++;
					}
				}
				reset();
				break;
			}
			reset();
		}
		break;


	case 2:																//��ԋ����J�[�h�ȊO�̃y�A���o��
		for (L0 = FieldCard[1] - 1; L0 >= 1; L0--) {
			for (L1 = 1; L1 <= 4; L1++) {
				if (Card[L0][L1] == 1) {
					L2++;
					pmark2[L1] = L1;
				}
			}
			if (L2 >= 2) {
				num2 = L2;
				for (L4 = 1; L4 < 3; L4++) {
					aCard[L4] = L0;
				}
				for (L1 = 1; L1 <= 4; L1++) {
					if (pmark2[L1] > 0) {
						pmark[L3 + 1] = pmark2[L1];
						L3++;
					}
				}
				reset();
				break;
			}
			reset();
		}
		break;

	case 3:
		if (FieldCard[1] == FieldCard[2] && FieldCard[1] == FieldCard[3]) {
			if (group[3] > 0) {											//2��3�ȊO�̂R���g����������A�R���g��^����ɏo��
				for (L0 = FieldCard[1] - 1; L0 >= 1; L0--) {
					for (L1 = 1; L1 <= 4; L1++) {
						if (Card[L0][L1] == 1) {
							L2++;
							pmark2[L1] = L1;
						}
					}
					if (L2 == 3) {
						num2 = L2;
						for (L1 = 1; L1 <= 4; L1++) {
							aCard[L1] = L0;
							if (pmark2[L1] > 0) {
								pmark[L3 + 1] = pmark2[L1];
								L3++;
							}
						}
						reset();
						break;
					}
					reset();
				}
			}
		}
		else if (FieldCard[1] == FieldCard[2] + 1 && FieldCard[1] == FieldCard[3] + 2) {
			for (L1 = 1; L1 <= 4; L1++) {
				for (L0 = FieldCard[1] - 1; L0 >= 3; L0--) {
					if (Card[L0][L1] == 1 && Card[L0 - 1][L1] == 1 && Card[L0 - 2][L1] == 1) {
						num2 = FieldNum;
						for (L2 = 1; L2 <= FieldNum; L2++) {
							aCard[L2] = L0;
							pmark[L2] = L1;
							L0--;
							break;
						}
					}
				}
				if (pmark[1] > 0) { break; }
			}
			L2 = 0;
		}
		break;

	case 4:
		if (FieldCard[1] == FieldCard[2] && FieldCard[1] == FieldCard[3] && FieldCard[1] == FieldCard[4]) {
			if (group[4] > 0) {							//4���Ԃ�
				for (L0 = FieldCard[1] - 1; L0 >= 1; L0--) {
					for (L1 = 1; L1 <= 4; L1++) {
						if (Card[L0][L1] == 1) {
							L2++;
							pmark2[L1] = L1;
						}
					}
					if (L2 == 4) {
						num2 = L2;
						for (L1 = 1; L1 <= 4; L1++) {
							aCard[L1] = L0;
							if (pmark2[L1] > 0) {
								pmark[L3 + 1] = pmark2[L1];
								L3++;
							}
						}
						reset();
						break;
					}
					reset();
				}
			}
		}
		else if (FieldCard[1] == FieldCard[2] + 1 && FieldCard[1] == FieldCard[3] + 2 && FieldCard[1] == FieldCard[4] + 3) {
			for (L1 = 1; L1 <= 4; L1++) {
				for (L0 = FieldCard[1] - 1; L0 >= FieldNum; L0--) {
					if (Card[L0][L1] == 1 && Card[L0 - 1][L1] == 1 && Card[L0 - 2][L1] == 1 && Card[L0 - 3][L1] == 1) {
						num2 = FieldNum;
						pmark[1] = L1;
						for (L2 = 1; L2 <= FieldNum; L2++) {
							aCard[L2] = L0;
							pmark[L2] = L1;
							L0--;
							break;
						}
					}
				}
				if (pmark[1] > 0) { break; }
			}
			L2 = 0;
		}
		break;

	default:															//5���ȏ�̊K�i�̏ꍇ
		if (FieldNum == 5) {
			for (L1 = 1; L1 <= 4; L1++) {
				for (L0 = FieldCard[1] - 1; L0 > FieldNum; L0--) {
					if (Card[L0][L1] == 1 && Card[L0 - 1][L1] == 1 && Card[L0 - 2][L1] == 1 && Card[L0 - 3][L1] == 1 && Card[L0 - 4][L1] == 1) {
						num2 = FieldNum;								//�����ł́A�Y���������B
						pmark[1] = L1;									//�l�����̍��́A�ł��邾���A�Q��A���c����
						for (L2 = 1; L2 <= FieldNum; L2++) {			//�Ō�̌��߂�D�Ƃ��āA�g����������A
							aCard[L2] = L0;					//���肪34567���o���ꍇ�Ԃ���J�[�h��
							pmark[L2] = L1;								//8910JQ��910JQK��2�����Ȃ�
							L0--;
							break;
						}
					}
				}
				if (pmark[1] > 0) { break; }
			}
			L2 = 0;
		}
		break;
	}
}


void AI()
{
	CardGroup(Card[14][5], 1);
	if (kakumei == 0) {
		FieldCardtype(FieldNum, Card[14][5]);
	}
	else {
		FieldCardtype2(FieldNum, Card[14][5]);
	}
	
}
