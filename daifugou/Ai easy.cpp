#include "Ai.h"

int L0 = 0, L1 = 0, L2 = 0, L3 = 0, L4 = 0, L5 = 0, L6 = 0, L7 = 0;
int group[6];				//四枚組、三枚組、ペアと一枚カード枚数を初期化
double value;


int aCard[14];
int pmark[7], pmark2[7];
int step;
int Stat;		// 2:大富豪 1:富豪 -1:貧民 0:平民
int CardNum;	// 持ってるカードの枚数
int Card[15][6];	// 手札の枚数:
					// 　[1]-3  [2]-4 [3]-5  [4]-6  [5]-7  [6]-8 [7]-9
					//   [8]-10 [9]-J [10]-Q [11]-K [12]-A [13]-2
					//   [14]-ジョーカーの枚数

					// ----- 場札情報
int FieldCard[13];			// 場札のカード番号
int FieldNum;			// 場札のカード枚数
int UseNum;			// これまでに場に出されたカードの枚数
int UseCard[15];		// これまでに場に出された各カードの枚数:
						// 　[1]-3  [2]-4 [3]-5  [4]-6  [5]-7  [6]-8 [7]-9
						//   [8]-10 [9]-J [10]-Q [11]-K [12]-A [13]-2
						//   [14]-ジョーカーの枚数
						//   [0]にはUseNumと同じ値が入っている。

						// ----- 他プレイヤー情報
int PlayerNum;			// ゲーム中のプレイヤー数(自分を含まない)
int PlayerCard[5];		// 他プレイヤーの残りカード枚数[0]～[PlayerNum-1]

void CardGroup(int b, bool d)
{
	//1,2,3,4枚カードの数をそれぞれ計算
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
	//カードが全部出し終わるまでのカウントダウン。
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
		case 2:																//一番強いカード以外のペアを出す
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
				if (group[3] > 0) {											//2と3以外の３枚組があったら、３枚組を真っ先に出す
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
				if (c == 1) {												//joke 持ち
					num2 = 1;
					aCard[1] = 14;											//joke 出す
					pmark[1] = 5;											//jokeのマーク が５
					break;
				}
				else if (c == 0 && group[4] > 0) {							//4枚返し
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

		default:															//5枚以上の階段の場合
			if (FieldNum == 5) {
				for (L1 = 1; L1 <= 4; L1++) {
					for (L0 = FieldCard[FieldNum] + 1; L0 <=11; L0++) {
						if (Card[L0][L1] == 1 && Card[L0 + 1][L1] == 1 && Card[L0 + 2][L1] == 1 && Card[L0 + 3][L1] == 1 && Card[L0 + 4][L1] == 1) {
							num2 = FieldNum;								//ここでは、ちょっとズルした。
							for (L2 = 1; L2 <= FieldNum; L2++) {			//僕だちの作戦は、できるだけ、２とAを残し
								pmark[L2] = L1;								//最後の決める札として、使いたいから、
								aCard[L2] = L0;					//相手が34567を出す場合返せるカードは
								L0++;										//8910JQと910JQKの2つしかない
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
{																			//革命のとき
																			//２、A、Kいずれを持つ場合
	switch (b) {														//革命でないとき
	case 0:
		if (c == 1) {												//joke 持ち
			num2 = 1;
			aCard[1] = 14;											//joke 出す
			pmark[1] = 5;											//jokeのマーク が５
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


	case 2:																//一番強いカード以外のペアを出す
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
			if (group[3] > 0) {											//2と3以外の３枚組があったら、３枚組を真っ先に出す
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
			if (group[4] > 0) {							//4枚返し
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

	default:															//5枚以上の階段の場合
		if (FieldNum == 5) {
			for (L1 = 1; L1 <= 4; L1++) {
				for (L0 = FieldCard[1] - 1; L0 > FieldNum; L0--) {
					if (Card[L0][L1] == 1 && Card[L0 - 1][L1] == 1 && Card[L0 - 2][L1] == 1 && Card[L0 - 3][L1] == 1 && Card[L0 - 4][L1] == 1) {
						num2 = FieldNum;								//ここでは、ズルをした。
						pmark[1] = L1;									//僕だちの作戦は、できるだけ、２とAを残して
						for (L2 = 1; L2 <= FieldNum; L2++) {			//最後の決める札として、使いたいから、
							aCard[L2] = L0;					//相手が34567を出す場合返せるカードは
							pmark[L2] = L1;								//8910JQと910JQKの2つしかない
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
