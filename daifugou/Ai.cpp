#include "Ai.h"
// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
int L0 = 0, L1 = 0, L2 = 0, L3 = 0,L4=0,L5=0,L6=0,L7=0;
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

//AiData->Card[14][5], "step"
//			b				d
void CardGroup(int b,bool d)
{
	//1,2,3,4���J�[�h�̐������ꂼ��v�Z
	int L0, L1, L2=0;
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
	if(d!=0)
		step = group[1] + group[2] + group[3] + group[4] + group[5];

}

// AiData->CardNum, AiData->Card[14][5]
//		b					c
void CardValue(int b,int c)
{
	//��D�̃J�[�h�̋����̊��Ғl���v�Z
	int L0, L1, L2=0;
	for (L0 = 1; L0 <= 13; L0++) {
		for (L1 = 1; L1 <= 4; L1++) {
			if (Card[L0][L1] == 1) {
				L2 += L0 + 2;
			}
		}
	}																			//joke�ɑ傫�����Ȃ����߁A�v�Z�ɂ���Ȃ��B
		value = (double)L2 / (b - c);
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
void FieldCardtype(int b,  int c)
{		
	L5 = 0;																	//�v���łȂ�
		for(L0=13;L0>10;L0--){												//���߂�D2,A,K�����邩�𔻒�
			for (L1=1;L1<=4;L1++){
				if (Card[L0][L1] == 1){
					L5 = L0;
					break;
				}
			}
			if (L5 > 0) { break; }
		}	

		if (L5 > 0) {															//�Q�AA�AK����������ꍇ
			switch (b) {														//�v���łȂ��Ƃ�
			case 0:																//���
				if (value <= 8) {												//���Ғl��7.5��菬�����ꍇ
					if (c == 1) {												//joke ����
						num2 = 1;
						aCard[1] = 14;											//joke �o��
						pmark[1] = 5;											//joke�̃}�[�N ���T
						break;
					}
					else if (group[4] > 0 && c == 0) {							//joke �Ȃ����
						for (L0 = 1; L0 <= 13; L0++) {							//4���J�[�h���o��
							for (L1 = 2; L1 <= 4; L1++) {
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
					else if (group[4] == 0 && c == 0) {							//�����ĂȂ��ꍇ�A4���炾���B
						for (L0 = 2; L0 < 14; L0++) {
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
				}
				else {															//���Ғl��6.5���傫���ꍇ�A
					if (group[3] > 0) {											//2��3�ȊO�̂R���g����������A�R���g��^����ɏo��
						for (L0 = 2; L0 < 14; L0++) {
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
					if (num2 == 0) {										//�Ȃ�������A����
						if (group[1] >= group[2]) {							//1���J�[�h�̂ق��������ꍇ
							if (group[1] > group[2]) {
								for (L0 = 2; L0 < L5; L0++) {
									for (L1 = 1; L1 <= 4; L1++) {
										if (Card[L0][L1] == 1) {
											L2++;
											pmark2[L1] = L1;
										}
									}
									if (L2 == 1) {
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
							if (num2 == 0) {								//�Ȃ�������A4���炾���B
								for (L0 = 2; L0 < 14; L0++) {
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
						}
						else if (group[1] <= group[2]) {												//2���J�[�h�̂ق��������ꍇ
							for (L0 = 2; L0 < L5; L0++) {					//2��3�ȊO��1���̃J�[�h�����������ŏo��
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 2) {
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
							if (num2 == 0) {								//�Ȃ�������A4���炾���B
								for (L0 = 2; L0 < 14; L0++) {
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
						}
					}
				}
				break;

			case 1:
				if (FieldCard[1] == 14) {
					num2 = 0;
					aCard[1] = 0;
					pmark[1] = 0;
					break;
				}
				else {
					if (Card[14][5] == 1) {											//��D��joke������Ƃ�
						if (value >= 8.5) {											//�����̊��Ғl��7.5�ȏ�̎�
							if (FieldCard[1] <= 6) {								//�t�B�[���h�̃J�[�h��7���
								for (L0 = 6; L0 < L5; L0++) {						//�������Ƃ��A8����o��
									for (L1 = 1; L1 <= 4; L1++) {
										if (Card[L0][L1] == 1) {
											L2++;
											pmark2[L1] = L1;
										}
									}
									if (L2 == 1) {
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
							else {
								for (L0 = FieldCard[1] + 1; L0 < L5; L0++) {
									for (L1 = 1; L1 <= 4; L1++) {
										if (Card[L0][L1] == 1) {
											L2++;
											pmark2[L1] = L1;
										}
									}
									if (L2 == 1) {
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
						}
						else {														//�����̊��Ғl��7.5�ȉ��̎�
							if (L5 == 13) {
								for (L1 = 1; L1 <= 4; L1++) {						//2�������
									if (Card[13][L1] == 1) {						//2 �o��
										num2 = 1;
										aCard[1] = 13;
										pmark[1] = L1;
										break;
									}
								}
							}
							else {													//�Q���Ȃ����
								for (L0 = 13; L0 <= 1; L0--) {						//�����̎�D�̍ŋ��J�[�h�̔ԍ�
									for (L1 = 1; L1 <= 4; L1++) {					//�Ɛ����v�Z
										if (Card[L0][L1] == 1) {					//��ɏo���ꂽ�J�[�h�̍ŋ��J�[�h
											L2++;									//�Ǝ����̍ŋ��J�[�h���ׁA����
											L6 = L0;								//�ꏏ��������A�o���i���Ŕ��ʁj
											L7 = L1;
										}
									}
									if (L2 > 0) { break; }
								}													//�Q��Ⴆ�Ƃ����
								for (L0 = 13; L0 <= 1; L0--) {						//��ɏo���ꂽ�J�[�h+�����̎�D��
									if (UseCard[L0] != 4) {							//�J�[�h���S��������A����̎�D��
										if (L6 == L0) {								//�Q���Ȃ����ƁA
											num2 = 1;
											aCard[1] = L6;
											pmark[1] = L7;
											reset();
											L6 = 0, L7 = 0;
											break;
										}
										else {										//�łȂ���΁A��������
											for (L0 = FieldCard[1] + 1; L0 < L5; L0++) {
												for (L1 = 1; L1 <= 4; L1++) {
													if (Card[L0][L1] == 1) {
														L2++;
														pmark2[L1] = L1;
													}
												}
												if (L2 == 1) {
													num2 = 1;
													aCard[1] = L0;
													for (L1 = 1; L1 <= 4; L1++) {
														if (pmark2[L1] > 0) {
															pmark[L3 + 1] = pmark2[L1];
															L3++;
														}
													}
													L6 = 0, L7 = 0;
													reset();
													break;
												}
												L6 = 0, L7 = 0;
												reset();
											}
										}
									}
								}
							}
						}
					}
					else {															//�W���[�J�[�Ȃ�����A
						for (L0 = FieldCard[1] + 1; L0 < L5; L0++) {				//�ő�̃J�[�h�ƂR�ȊO
							for (L1 = 1; L1 <= 4; L1++) {							//�K���K���o���΂���
								if (Card[L0][L1] == 1) {
									L2++;
									pmark2[L1] = L1;
								}
							}
							if (L2 == 1) {
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
						num2 = 2;
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
						for (L0 = FieldCard[1] + 1; L0 < 13; L0++) {
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
						for (L0 = FieldCard[FieldNum] + 1; L0 < 11; L0++) {
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
						for (L0 = FieldCard[FieldNum] + 1; L0 < 10; L0++) {
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

			default:
				for (L1 = 1; L1 <= 4; L1++) {
					for (L0 = FieldCard[FieldNum] + 1; L0 <= 10; L0++) {
						if (FieldNum == 5) {
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
						else if (FieldNum == 6) {
							if (Card[L0][L1] == 1 && Card[L0 + 1][L1] == 1 && Card[L0 + 2][L1] == 1 && Card[L0 + 3][L1] == 1 && Card[L0 + 4][L1] == 1 && Card[L0 + 5][L1] == 1) {
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
		else if(L5==0) {															//�Q�AA�AK�S���Ȃ��ꍇ
			switch (b) {														//�v���łȂ��Ƃ�
			case 0:																//���
				if (value <= 8) {												//���Ғl��7.5��菬�����ꍇ
					if (c == 1) {												//joke ����
						num2 = 1;
						aCard[1] = 14;											//joke �o��
						pmark[1] = 5;											//joke�̃}�[�N ���T
						break;
					}
					else if (group[4] > 0 && c == 0) {							//joke �Ȃ����
						for (L0 = 1; L0 <= 13; L0++) {							//4���J�[�h���o��
							for (L1 = 2; L1 <= 4; L1++) {
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
					else if (group[4] == 0 && c == 0) {							//�����ĂȂ��ꍇ�A4���炾���B
						for (L0 = 2; L0 < 14; L0++) {
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
				}
				else {															//���Ғl��6.5���傫���ꍇ�A
					if (group[3] > 0) {											//2��3�ȊO�̂R���g����������A�R���g��^����ɏo��
						for (L0 = 2; L0 < 14; L0++) {
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
					if (num2 == 0) {										//�Ȃ�������A����
						if (group[1] >= group[2]) {							//1���J�[�h�̂ق��������ꍇ
							if (group[1] > group[2]) {
								for (L0 = 2; L0 < L5; L0++) {
									for (L1 = 1; L1 <= 4; L1++) {
										if (Card[L0][L1] == 1) {
											L2++;
											pmark2[L1] = L1;
										}
									}
									if (L2 == 1) {
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
							if (num2 == 0) {								//�Ȃ�������A4���炾���B
								for (L0 = 2; L0 < 14; L0++) {
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
						}
						else if (group[1] <= group[2]) {												//2���J�[�h�̂ق��������ꍇ
							for (L0 = 2; L0 < L5; L0++) {					//2��3�ȊO��1���̃J�[�h�����������ŏo��
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 2) {
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
							if (num2 == 0) {								//�Ȃ�������A4���炾���B
								for (L0 = 2; L0 < 14; L0++) {
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
						}
					}
				}
				break;


			case 1:
				if (FieldCard[1] == 14) {
					num2 = 0;
					aCard[1] = 0;
					pmark[1] = 0;
					break;
				}
				else {
					if (Card[14][5] == 1) {											//��D��joke������Ƃ�
						if (value >= 8) {											//�����̊��Ғl��7.5�ȏ�̎�
							if (FieldCard[1] <= 4) {
								for (L0 = 5; L0 < 13; L0++) {
									for (L1 = 1; L1 <= 4; L1++) {
										if (Card[L0][L1] == 1) {
											L2++;
											pmark2[L1] = L1;
										}
									}
									if (L2 == 1) {
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
						}
						else {
							for (L0 = FieldCard[1] + 1; L0 < 14; L0++) {
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 1) {
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

					}
					else {														//�����̊��Ғl��7.5�ȉ��̎�
						if (L5 == 13) {
							for (L1 = 1; L1 <= 4; L1++) {						//2�������
								if (Card[13][L1] == 1) {						//2 �o��
									num2 = 1;
									aCard[1] = 13;
									pmark[1] = L1;
									break;
								}
							}
						}
						else {													//�Q���Ȃ����
							for (L0 = 13; L0 <= 1; L0--) {						//�����̎�D�̍ŋ��J�[�h�̔ԍ�
								for (L1 = 1; L1 <= 4; L1++) {					//�Ɛ����v�Z
									if (Card[L0][L1] == 1) {					//��ɏo���ꂽ�J�[�h�̍ŋ��J�[�h
										L2++;									//�Ǝ����̍ŋ��J�[�h���ׁA����
										L6 = L0;								//�ꏏ��������A�o���i���Ŕ��ʁj
										L7 = L1;
									}
								}
								if (L2 > 0) { break; }
							}													//�Q��Ⴆ�Ƃ����
							for (L0 = 13; L0 <= 1; L0--) {						//��ɏo���ꂽ�J�[�h+�����̎�D��
								if (UseCard[L0] != 4) {							//�J�[�h���S��������A����̎�D��
									if (L6 == L0) {								//�Q���Ȃ����ƁA
										num2 = 1;
										aCard[1] = L6;
										pmark[1] = L7;
										reset();
										L6 = 0, L7 = 0;
										break;
									}
									else {										//�łȂ���΁A��������
										for (L0 = FieldCard[1] + 1; L0 < 14; L0++) {
											for (L1 = 1; L1 <= 4; L1++) {
												if (Card[L0][L1] == 1) {
													L2++;
													pmark2[L1] = L1;
												}
											}
											if (L2 == 1) {
												num2 = 1;
												aCard[1] = L0;
												for (L1 = 1; L1 <= 4; L1++) {
													if (pmark2[L1] > 0) {
														pmark[L3 + 1] = pmark2[L1];
														L3++;
													}
												}
												reset();
												L6 = 0, L7 = 0;
												break;
											}
											L6 = 0, L7 = 0;
											reset();
										}
									}
								}
							}
						}
					}
				}
				break;

			case 2:																//��ԋ����J�[�h�ȊO�̃y�A���o��
				for (L0 = FieldCard[1] + 1; L0 <14; L0++) {
					for (L1 = 1; L1 <= 4; L1++) {
						if (Card[L0][L1] == 1) {
							L2++;
							pmark2[L1] = L1;
						}
					}
					if (L2 >= 2) {
						num2 = 2;
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
						for (L0 = FieldCard[FieldNum]+1 ; L0 < 11; L0++) {
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
					else if (c == 0&& group[4] > 0) {							//4���Ԃ�
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
						for (L0 = FieldCard[FieldNum]+1 ; L0 < 10; L0++) {
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
						for (L0 = FieldCard[FieldNum]+1 ; L0 < 9; L0++) {
							if (Card[L0][L1] == 1 && Card[L0 + 1][L1] == 1 && Card[L0 + 2][L1] == 1 && Card[L0 + 3][L1] == 1 && Card[L0 + 4][L1] == 1) {
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
			}
		}
}


void FieldCardtype2(int b,int c)
{																			//�v���̂Ƃ�
	for (L1 = 1; L1 <= 4; L1++) {											//���߂�D3�̔���
			if (Card[1][L1] == 1) {
				L5 = 1;
				break;
			}
		}

	if (L5 > 0) {															//�Q�AA�AK����������ꍇ
		switch (b) {														//�v���łȂ��Ƃ�
		case 0:																//���
			if (value >= 9.5) {												//���Ғl��7.5��菬�����ꍇ
				if (c == 1) {												//joke ����
					num2 = 1;
					aCard[1] = 14;											//joke �o��
					pmark[1] = 5;											//joke�̃}�[�N ���T
					break;
				}
				else if (group[4] > 0 && c == 0) {							//joke �Ȃ����
					for (L0 = 13; L0 >= 1; L0--) {							//4���J�[�h���o��
						for (L1 = 2; L1 <= 4; L1++) {
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
				else if (group[4] == 0 && c == 0) {							//�����ĂȂ��ꍇ�A4���炾���B
					for (L0 = 13; L0 > 1; L0--) {
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
			}
			else {															//���Ғl��6.5���傫���ꍇ�A
				if (group[3] > 0) {											//2��3�ȊO�̂R���g����������A�R���g��^����ɏo��
					for (L0 = 13; L0 > 1; L0--) {
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
				if (num2 == 0) {										//�Ȃ�������A����
					if (group[1] > group[2]) {							//1���J�[�h�̂ق��������ꍇ
						if (group[1] > group[2]) {
							for (L0 = 13; L0 > 1; L0--) {
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 1) {
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
						if (num2 == 0) {								//�Ȃ�������A4���炾���B
							for (L0 = 13; L0 > 1; L0--) {
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
					}
					else if (group[1] < group[2]) {
						for (L0 = 13; L0 > 1; L0--) {
							for (L1 = 1; L1 <= 4; L1++) {
								if (Card[L0][L1] == 1) {
									L2++;
									pmark2[L1] = L1;
								}
							}
							if (L2 == 2) {
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
						if (num2 == 0) {								//�Ȃ�������A4���炾���B
							for (L0 = 13; L0 > 1; L0--) {
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
					}
				}
			}
			break;

		case 1:
			if (FieldCard[1] == 14) {
				if (group[4] > 0) {
					for (L0 = 13; L0 >= 0; L0--) {
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
			else {
				if (Card[14][5] == 1) {											//��D��joke������Ƃ�
					if (value <= 9.5) {											//�����̊��Ғl��7.5�ȏ�̎�
						if (FieldCard[1] >= 9) {								//�t�B�[���h�̃J�[�h��7���
							for (L0 = 8; L0 >= 1; L0--) {						//�������Ƃ��A8����o��
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 1) {
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
						else {
							for (L0 = FieldCard[1] - 1; L0 > 0; L0--) {
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 1) {
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
					}
					else {														//�����̊��Ғl��7.5�ȉ��̎�
						if (L5 == 1) {
							for (L1 = 1; L1 <= 4; L1++) {						//2�������
								if (Card[13][L1] == 1) {						//2 �o��
									num2 = 1;
									aCard[1] = 1;
									pmark[1] = L1;
									break;
								}
							}
						}
						else if (L5 < 4 && L5>1) {													//�Q���Ȃ����
							for (L0 = 1; L0 <= 13; L0++) {						//�����̎�D�̍ŋ��J�[�h�̔ԍ�
								for (L1 = 1; L1 <= 4; L1++) {					//�Ɛ����v�Z
									if (Card[L0][L1] == 1) {					//��ɏo���ꂽ�J�[�h�̍ŋ��J�[�h
										L2++;									//�Ǝ����̍ŋ��J�[�h���ׁA����
										L6 = L0;								//�ꏏ��������A�o���i���Ŕ��ʁj
										L7 = L1;
									}
								}
								if (L2 > 0) { break; }
							}													//�Q��Ⴆ�Ƃ����
							for (L0 = 13; L0 <= 1; L0--) {						//��ɏo���ꂽ�J�[�h+�����̎�D��
								if (UseCard[L0] != 4) {							//�J�[�h���S��������A����̎�D��
									if (L6 == L0) {								//�Q���Ȃ����ƁA
										num2 = 1;
										aCard[1] = L6;
										pmark[1] = L7;
										reset();
										L6 = 0, L7 = 0;
										break;
									}
								}
							}
						}
						else {
							for (L0 = FieldCard[1] - 1; L0 > 0; L0--) {
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 1) {
									num2 = 1;
									aCard[1] = L0;
									for (L1 = 1; L1 <= 4; L1++) {
										if (pmark2[L1] > 0) {
											pmark[L3 + 1] = pmark2[L1];
											L3++;
										}
									}
									L6 = 0, L7 = 0;
									reset();
									break;
								}
								L6 = 0, L7 = 0;
								reset();
							}
						}
					}
				}
				else {															//�W���[�J�[�Ȃ�����A
					for (L0 = FieldCard[1] - 1; L0 > 0; L0--) {				//�ő�̃J�[�h�ƂR�ȊO
						for (L1 = 1; L1 <= 4; L1++) {							//�K���K���o���΂���
							if (Card[L0][L1] == 1) {
								L2++;
								pmark2[L1] = L1;
							}
						}
						if (L2 == 1) {
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
			}
			
			break;

		case 2:																//��ԋ����J�[�h�ȊO�̃y�A���o��
			for (L0 = FieldCard[1] - 1; L0 >0; L0--) {
				for (L1 = 1; L1 <= 4; L1++) {
					if (Card[L0][L1] == 1) {
						L2++;
						pmark2[L1] = L1;
					}
				}
				if (L2 >= 2) {
					num2 = 2;
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
				if (group[3] > 0) {											
					for (L0 = FieldCard[1] - 1; L0 >0; L0--) {
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
					for (L0 = FieldCard[FieldNum] - 1; L0 >=3; L0--) {
						if (Card[L0][L1] == 1 && Card[L0 - 1][L1] == 1 && Card[L0 - 2][L1] == 1) {
							num2 = FieldNum;
							for (L2 = 1; L2 <= FieldNum; L2++) {
								pmark[L2] = L1;
								aCard[L2] = L0;
								L0--;
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
				if (group[4] > 0) {							//4���Ԃ�
					for (L0 = FieldCard[1] -1; L0 >0; L0--) {
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
					for (L0 = FieldCard[FieldNum] - 1; L0 >=4; L0--) {
						if (Card[L0][L1] == 1 && Card[L0 - 1][L1] == 1 && Card[L0 - 2][L1] == 1 && Card[L0 - 3][L1] == 1) {
							num2 = FieldNum;
							for (L2 = 1; L2 <= FieldNum; L2++) {
								pmark[L2] = L1;
								aCard[L2] = L0;
								L0--;
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
					for (L0 = FieldCard[FieldNum] - 1; L0 >=FieldNum; L0--) {
						if (Card[L0][L1] == 1 && Card[L0 - 1][L1] == 1 && Card[L0 - 2][L1] == 1 && Card[L0 - 3][L1] == 1 && Card[L0 - 4][L1] == 1) {
							num2 = FieldNum;								//�����ł́A������ƃY�������B
							for (L2 = 1; L2 <= FieldNum; L2++) {			//�l�����̍��́A�ł��邾���A�Q��A���c��
								pmark[L2] = L1;								//�Ō�̌��߂�D�Ƃ��āA�g����������A
								aCard[L2] = L0;					//���肪34567���o���ꍇ�Ԃ���J�[�h��
								L0--;										//8910JQ��910JQK��2�����Ȃ�
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

	else if (L5 == 0) {															//�Q�AA�AK�S���Ȃ��ꍇ
		switch (b) {														//�v���łȂ��Ƃ�
		case 0:																//���
			if (c == 1) {													//joke ����
				num2 = 1;
				aCard[1] = 14;												//joke �o��
				pmark[1] = 5;												//joke�̃}�[�N ���T
				break;
			}
			else if (group[4] > 0 && c == 0) {							//joke �Ȃ����
						for (L0 = 13; L0 >= 1; L0--) {							//4���J�[�h���o��
							for (L1 = 2; L1 <= 4; L1++) {
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
			else if(group[4] == 0 && c == 0){
				if (group[3] > 0) {											//2��3�ȊO�̂R���g����������A�R���g��^����ɏo��
					for (L0 = 13; L0 >0; L0--) {
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
				if (num2 == 0) {										//�Ȃ�������A����
					if (group[1] > group[2]) {							//1���J�[�h�̂ق��������ꍇ
						if (group[1] > group[2]) {
							for (L0 = 13; L0 > 0; L0--) {
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 1) {
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
						if (num2 == 0) {								//�Ȃ�������A4���炾���B
							for (L0 = 13; L0 >0; L0--) {
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
					}
					else if (group[1] < group[2]) {												//2���J�[�h�̂ق��������ꍇ
						for (L0 = 13; L0 >0; L0--) {					//2��3�ȊO��1���̃J�[�h�����������ŏo��
							for (L1 = 1; L1 <= 4; L1++) {
								if (Card[L0][L1] == 1) {
									L2++;
									pmark2[L1] = L1;
								}
							}
							if (L2 == 2) {
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
						if (num2 == 0) {								//�Ȃ�������A4���炾���B
							for (L0 = 13; L0 >0; L0--) {
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
					}
				}
			}
			break;

		case 1:
			if (FieldCard[1] == 14) {
				if (group[4] > 0) {
					for (L0 = 13; L0 >= 0; L0--) {
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
			else {
				if (Card[14][5] == 1) {											//��D��joke������Ƃ�
					if (value <= 9.5) {											//�����̊��Ғl��7.5�ȏ�̎�
						if (FieldCard[1] >= 9) {								//�t�B�[���h�̃J�[�h��7���
							for (L0 = 8; L0 >= 1; L0--) {						//�������Ƃ��A8����o��
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 1) {
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
						else {
							for (L0 = FieldCard[1] - 1; L0 > 0; L0--) {
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 1) {
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
					}
					else {														//�����̊��Ғl��7.5�ȉ��̎�
						if (L5 == 1) {
							for (L1 = 1; L1 <= 4; L1++) {						//2�������
								if (Card[13][L1] == 1) {						//2 �o��
									num2 = 1;
									aCard[1] = 1;
									pmark[1] = L1;
									break;
								}
							}
						}
						else if (L5 < 4 && L5>1) {													//�Q���Ȃ����
							for (L0 = 1; L0 <= 13; L0++) {						//�����̎�D�̍ŋ��J�[�h�̔ԍ�
								for (L1 = 1; L1 <= 4; L1++) {					//�Ɛ����v�Z
									if (Card[L0][L1] == 1) {					//��ɏo���ꂽ�J�[�h�̍ŋ��J�[�h
										L2++;									//�Ǝ����̍ŋ��J�[�h���ׁA����
										L6 = L0;								//�ꏏ��������A�o���i���Ŕ��ʁj
										L7 = L1;
									}
								}
								if (L2 > 0) { break; }
							}													//�Q��Ⴆ�Ƃ����
							for (L0 = 13; L0 <= 1; L0--) {						//��ɏo���ꂽ�J�[�h+�����̎�D��
								if (UseCard[L0] != 4) {							//�J�[�h���S��������A����̎�D��
									if (L6 == L0) {								//�Q���Ȃ����ƁA
										num2 = 1;
										aCard[1] = L6;
										pmark[1] = L7;
										reset();
										L6 = 0, L7 = 0;
										break;
									}
								}
							}
						}
						else {
							for (L0 = FieldCard[1] - 1; L0 > 0; L0--) {
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 1) {
									num2 = 1;
									aCard[1] = L0;
									for (L1 = 1; L1 <= 4; L1++) {
										if (pmark2[L1] > 0) {
											pmark[L3 + 1] = pmark2[L1];
											L3++;
										}
									}
									L6 = 0, L7 = 0;
									reset();
									break;
								}
								L6 = 0, L7 = 0;
								reset();
							}
						}
					}
				}
				else {															//�W���[�J�[�Ȃ�����A
					for (L0 = FieldCard[1] - 1; L0 < 0; L0--) {				//�ő�̃J�[�h�ƂR�ȊO
						for (L1 = 1; L1 <= 4; L1++) {							//�K���K���o���΂���
							if (Card[L0][L1] == 1) {
								L2++;
								pmark2[L1] = L1;
							}
						}
						if (L2 == 1) {
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
			}
			break;

		case 2:																//��ԋ����J�[�h�ȊO�̃y�A���o��
			for (L0 = FieldCard[1] -1; L0>0; L0--) {
				for (L1 = 1; L1 <= 4; L1++) {
					if (Card[L0][L1] == 1) {
						L2++;
						pmark2[L1] = L1;
					}
				}
				if (L2 >= 2) {
					num2 = 2;
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
					for (L0 = FieldCard[1] - 1; L0 >0; L0--) {
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
					for (L0 = FieldCard[1] - 1; L0 >=3; L0--) {
						if (Card[L0][L1] == 1 && Card[L0 - 1][L1] == 1 && Card[L0 - 2][L1] == 1) {
							num2 = FieldNum;
							for (L2 = 1; L2 <= FieldNum; L2++) {
								pmark[L2] = L1;
								aCard[L2] = L0;
								L0--;
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
					for (L0 = FieldCard[1] - 1; L0 >0; L0--) {
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
					for (L0 = FieldCard[FieldNum] - 1; L0 >=4; L0--) {
						if (Card[L0][L1] == 1 && Card[L0 - 1][L1] == 1 && Card[L0 - 2][L1] == 1 && Card[L0 - 3][L1] == 1) {
							num2 = FieldNum;
							for (L2 = 1; L2 <= FieldNum; L2++) {
								pmark[L2] = L1;
								aCard[L2] = L0;
								L0--;
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
					for (L0 = FieldCard[FieldNum] - 1; L0 >=FieldNum; L0--) {
						if (Card[L0][L1] == 1 && Card[L0 + 1][L1] == 1 && Card[L0 + 2][L1] == 1 && Card[L0 + 3][L1] == 1 && Card[L0 + 4][L1] == 1) {
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
		}
	}
}


void step2_0(int b, int c) {
	L4 = 0;
	for (L0 = 13; L0 >= 1; L0--) {											//��D�Ɏc���ԋ����J�[�h
		for (L1 = 1; L1 <= 4; L1++) {										//�̔ԍ��Ɩ������������A�L�^����
			if (Card[L0][L1] == 1) {
				L4 = L0;
				pmark2[L3 + 1] = L1;
				L3++;
			}
		}
		if (L4 != 0) { break; }
	}

	switch (b) {
	case 0:
		L3 = 0;
		if (Card[14][5] == 1) {
			num2 = 1;
			aCard[1] = 14;											//joke �o��
			pmark[1] = 5;											//joke�̃}�[�N ���T
			break;
		}
		else {
			for (L0 = 1; L0 < 14; L0++) {
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
		if (FieldCard[1] == 14) {
			num2 = 0;
			aCard[1] = 0;
			pmark[1] = 0;
			break;
		}
		else {
			if (L4 == 13) {
				num2 = 1;
				aCard[1] = L4;
				for (L0 = 1; L0 <= 4; L0++) {
					if (pmark2[L0] > 0) {
						pmark[1] = pmark2[L0];
					}
				}
				break;
				reset();
			}
			else {
				for (L0 = 12; L0 <= 1; L0--) {
					if (UseCard[L0] != 4) {
						if (L4 == L0) {
							num2 = 1;
							for (L0 = 1; L0 <= L3; L0++) {
								aCard[L0] = L4;
								pmark[L0] = pmark[L0];
							}
							reset();
							L6 = 0, L7 = 0;
							break;
						}
						else {
							L3 = 0, L4 = 0;
							for (L0 = FieldCard[1] + 1; L0 < 14; L0++) {
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										L2++;
										pmark2[L1] = L1;
									}
								}
								if (L2 == 1) {
									num2 = 1;
									aCard[1] = L0;
									for (L1 = 1; L1 <= 4; L1++) {
										if (pmark2[L1] > 0) {
											pmark[L3 + 1] = pmark2[L1];
											L3++;
										}
									}
									L6 = 0, L7 = 0;
									reset();
									break;
								}
								L6 = 0, L7 = 0;
								reset();
							}
						}
						if (num2 == 0) {
							for (L0 = FieldCard[1] + 1; L0 < 14; L0++) {
								for (L1 = 1; L1 <= 4; L1++) {
									if (Card[L0][L1] == 1) {
										pmark[L1] = L1;
										num2 = FieldNum;
										aCard[1] = L0;
										break;
									}
								}
							}
							if (num2 != 0) { break; }
						}
					}
				}
			}
		}
		break;

	case 2:
		L3 = 0, L4 = 0;
		for (L0 = FieldCard[1] + 1; L0 < 14; L0++) {
			for (L1 = 1; L1 <= 4; L1++) {
				if (Card[L0][L1] == 1) {
					L2++;
					pmark2[L1] = L1;
				}
			}
			if (L2 == 2) {
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
		L3 = 0, L4 = 0;
		if (group[3] > 0) {
			if (FieldCard[1] == FieldCard[2] && FieldCard[1] == FieldCard[3]) {
				if (group[3] > 0) {											
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
		}
		break;

	case 4:
		L3 = 0, L4 = 0;
		if (group[4] > 0) {
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
		}
		break;
	}
}

void step2_1(int b, int c) {
	L4 = 0;
	for (L0 = 1; L0 <=13; L0++) {											//��D�Ɏc���ԋ����J�[�h
		for (L1 = 1; L1 <= 4; L1++) {										//�̔ԍ��Ɩ������������A�L�^����
			if (Card[L0][L1] = 1) {
				L4 = L0;
				pmark2[L3 + 1] = L1;
				L3++;
			}
		}
		if (L4 != 0) { break; }
	}


	switch (b) {
	case 0:
		if (Card[14][5] == 1) {
			num2 = 1;
			aCard[1] = 14;											//joke �o��
			pmark[1] = 5;											//joke�̃}�[�N ���T
			break;
		}
		else {
			for (L0 = 1; L0 < 14; L0++) {
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
		break;

	case 1:
		if (FieldCard[1] == 14) {
			num2 = 0;
			aCard[1] = 0;
			pmark[1] = 0;
			break;
		}
		else{
			for (L0 = 1; L0 <= 13; L0++) {
				if (UseCard[L0] != 4) {
					if (L4 == L0) {
						num2 = 1;
						for (L0 = 1; L0 <= L3; L0++) {
							aCard[L0] = L4;
							pmark[L0] = pmark[L0];
						}
						reset();
						L6 = 0, L7 = 0;
						break;
					}
					else {
						L3 = 0, L4 = 0;
						for (L0 = FieldCard[1] - 1; L0 > 0; L0--) {
							for (L1 = 1; L1 <= 4; L1++) {
								if (Card[L0][L1] == 1) {
									L2++;
									pmark2[L1] = L1;
								}
							}
							if (L2 == 1) {
								num2 = 1;
								aCard[1] = L0;
								for (L1 = 1; L1 <= 4; L1++) {
									if (pmark2[L1] > 0) {
										pmark[L3 + 1] = pmark2[L1];
										L3++;
									}
								}
								L6 = 0, L7 = 0;
								reset();
								break;
							}
							L6 = 0, L7 = 0;
							reset();
						}
					}
					if (num2 == 0) {
						for (L0 = FieldCard[1] - 1; L0 > 0; L0--) {
							for (L1 = 1; L1 <= 4; L1++) {
								if (Card[L0][L1] == 1) {
									pmark[L1] = L1;
									num2 = FieldNum;
									aCard[1] = L0;
									break;
								}
							}
						}
						if (num2 != 0) { break; }
					}
				}
			}
		}
		break;

	case 2:
		L3 = 0, L4 = 0;
		for (L0 = FieldCard[1] - 3; L0 >0; L0--) {
			for (L1 = 1; L1 <= 4; L1++) {
				if (Card[L0][L1] == 1) {
					L2++;
					pmark2[L1] = L1;
				}
			}
			if (L2 == 2) {
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
		L3 = 0, L4 = 0;
		if (group[3] > 0) {
			if (FieldCard[1] == FieldCard[2] && FieldCard[1] == FieldCard[3]) {
				for (L0 = FieldCard[1] - 3; L0 >0; L0--) {
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
		break;

	case 4:
		L3 = 0, L4 = 0;
		if (group[4] > 0) {
			if (FieldCard[1] == FieldCard[2] && FieldCard[1] == FieldCard[3] && FieldCard[1] == FieldCard[4]) {
				for (L0 = FieldCard[1] - 3; L0 > 0; L0--) {
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
		break;
	}
}

void step1_0(int b) 
{

	switch (b) {
	case 0:
		for (L0 = 1; L0 < 14; L0++) {
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
		break;

	default:
		for (L0 = FieldCard[FieldNum] + 1; L0< 14; L0++) {
			for (L1 = 1; L1 <= 4; L1++) {
				if (Card[L0][L1] == 1) {
					L2++;
					pmark2[L1] = L1;
				}
			}
			if (L2 == FieldNum) {
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

	}

}

void step1_1(int b)
{
	
	switch (b) {
	case 0:
		for (L0 = 1; L0 < 14; L0++) {
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
		break;
	
	default:
		for (L0 = FieldCard[1] - 1; L0 > 0; L0--) {
			for (L1 = 1; L1 <= 4; L1++) {
				if (Card[L0][L1] == 1) {
					L2++;
					pmark2[L1] = L1;
				}
			}
			if (L2 == FieldNum) {
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
	}

}

void AI()
{
	CardValue(CardNum, Card[14][5]);
	CardGroup(Card[14][5], 1);
	if (step > 2){
		if (kakumei == 0) {
			FieldCardtype(FieldNum, Card[14][5]);
		}
		else {
			FieldCardtype2(FieldNum, Card[14][5]);
		}
		for (L0 = 0; L0 <= 5; L0++) {
			group[L0] = 0;
		}
	}
	else if (step == 2) {
		if (kakumei == 0) { step2_0(FieldNum, Card[14][5]); }
		else { step2_1(FieldNum, Card[14][5]); }
		for (L0 = 0; L0 <= 5; L0++) {
			group[L0] = 0;
		}
	}
	else if (step == 1) {
		if (kakumei == 0) { step1_0(FieldNum); }
		else { step1_1(FieldNum); }
		for (L0 = 0; L0 <= 5; L0++) {
			group[L0] = 0;
		}
	}
}

