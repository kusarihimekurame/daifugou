#include "Ai.h"
// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
int L0 = 0, L1 = 0, L2 = 0, L3 = 0,L4=0,L5=0,L6=0,L7=0;
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

//AiData->Card[14][5], "step"
//			b				d
void CardGroup(int b,bool d)
{
	//1,2,3,4枚カードの数をそれぞれ計算
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
	//カードが全部出し終わるまでのカウントダウン。
	if(d!=0)
		step = group[1] + group[2] + group[3] + group[4] + group[5];

}

// AiData->CardNum, AiData->Card[14][5]
//		b					c
void CardValue(int b,int c)
{
	//手札のカードの強さの期待値を計算
	int L0, L1, L2=0;
	for (L0 = 1; L0 <= 13; L0++) {
		for (L1 = 1; L1 <= 4; L1++) {
			if (Card[L0][L1] == 1) {
				L2 += L0 + 2;
			}
		}
	}																			//jokeに大きさがないため、計算にいれない。
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
	L5 = 0;																	//革命でない
		for(L0=13;L0>10;L0--){												//決める札2,A,Kがあるかを判定
			for (L1=1;L1<=4;L1++){
				if (Card[L0][L1] == 1){
					L5 = L0;
					break;
				}
			}
			if (L5 > 0) { break; }
		}	

		if (L5 > 0) {															//２、A、Kいずれを持つ場合
			switch (b) {														//革命でないとき
			case 0:																//先手
				if (value <= 8) {												//期待値が7.5より小さい場合
					if (c == 1) {												//joke 持ち
						num2 = 1;
						aCard[1] = 14;											//joke 出す
						pmark[1] = 5;											//jokeのマーク が５
						break;
					}
					else if (group[4] > 0 && c == 0) {							//joke なければ
						for (L0 = 1; L0 <= 13; L0++) {							//4枚カードを出す
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
					else if (group[4] == 0 && c == 0) {							//持ってない場合、4からだす。
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
				else {															//期待値が6.5より大きい場合、
					if (group[3] > 0) {											//2と3以外の３枚組があったら、３枚組を真っ先に出す
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
					if (num2 == 0) {										//なかったら、次へ
						if (group[1] >= group[2]) {							//1枚カードのほうが多い場合
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
							if (num2 == 0) {								//なかったら、4からだす。
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
						else if (group[1] <= group[2]) {												//2枚カードのほうが多い場合
							for (L0 = 2; L0 < L5; L0++) {					//2と3以外の1枚のカードを小さい順で出す
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
							if (num2 == 0) {								//なかったら、4からだす。
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
					if (Card[14][5] == 1) {											//手札にjokeがあるとき
						if (value >= 8.5) {											//強さの期待値が7.5以上の時
							if (FieldCard[1] <= 6) {								//フィールドのカードが7より
								for (L0 = 6; L0 < L5; L0++) {						//小さいとき、8から出す
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
						else {														//強さの期待値が7.5以下の時
							if (L5 == 13) {
								for (L1 = 1; L1 <= 4; L1++) {						//2があれば
									if (Card[13][L1] == 1) {						//2 出す
										num2 = 1;
										aCard[1] = 13;
										pmark[1] = L1;
										break;
									}
								}
							}
							else {													//２がなければ
								for (L0 = 13; L0 <= 1; L0--) {						//自分の手札の最強カードの番号
									for (L1 = 1; L1 <= 4; L1++) {					//と数を計算
										if (Card[L0][L1] == 1) {					//場に出されたカードの最強カード
											L2++;									//と自分の最強カードを比べ、強さ
											L6 = L0;								//一緒だったら、出す（数で判別）
											L7 = L1;
										}
									}
									if (L2 > 0) { break; }
								}													//２を例えとすると
								for (L0 = 13; L0 <= 1; L0--) {						//場に出されたカード+自分の手札の
									if (UseCard[L0] != 4) {							//カードが４だったら、相手の手札に
										if (L6 == L0) {								//２がないこと、
											num2 = 1;
											aCard[1] = L6;
											pmark[1] = L7;
											reset();
											L6 = 0, L7 = 0;
											break;
										}
										else {										//でなければ、小さい順
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
					else {															//ジョーカーないから、
						for (L0 = FieldCard[1] + 1; L0 < L5; L0++) {				//最大のカードと３以外
							for (L1 = 1; L1 <= 4; L1++) {							//ガンガン出せばいい
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

			case 2:																//一番強いカード以外のペアを出す
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
					if (group[3] > 0) {											//2と3以外の３枚組があったら、３枚組を真っ先に出す
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
								num2 = FieldNum;								//ここでは、ちょっとズルした。
								for (L2 = 1; L2 <= FieldNum; L2++) {			//僕だちの作戦は、できるだけ、２とAを残し
									pmark[L2] = L1;								//最後の決める札として、使いたいから、
									aCard[L2] = L0;					//相手が34567を出す場合返せるカードは
									L0++;										//8910JQと910JQKの2つしかない
								}
								break;
							}
						}
						else if (FieldNum == 6) {
							if (Card[L0][L1] == 1 && Card[L0 + 1][L1] == 1 && Card[L0 + 2][L1] == 1 && Card[L0 + 3][L1] == 1 && Card[L0 + 4][L1] == 1 && Card[L0 + 5][L1] == 1) {
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
		else if(L5==0) {															//２、A、K全部ない場合
			switch (b) {														//革命でないとき
			case 0:																//先手
				if (value <= 8) {												//期待値が7.5より小さい場合
					if (c == 1) {												//joke 持ち
						num2 = 1;
						aCard[1] = 14;											//joke 出す
						pmark[1] = 5;											//jokeのマーク が５
						break;
					}
					else if (group[4] > 0 && c == 0) {							//joke なければ
						for (L0 = 1; L0 <= 13; L0++) {							//4枚カードを出す
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
					else if (group[4] == 0 && c == 0) {							//持ってない場合、4からだす。
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
				else {															//期待値が6.5より大きい場合、
					if (group[3] > 0) {											//2と3以外の３枚組があったら、３枚組を真っ先に出す
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
					if (num2 == 0) {										//なかったら、次へ
						if (group[1] >= group[2]) {							//1枚カードのほうが多い場合
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
							if (num2 == 0) {								//なかったら、4からだす。
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
						else if (group[1] <= group[2]) {												//2枚カードのほうが多い場合
							for (L0 = 2; L0 < L5; L0++) {					//2と3以外の1枚のカードを小さい順で出す
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
							if (num2 == 0) {								//なかったら、4からだす。
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
					if (Card[14][5] == 1) {											//手札にjokeがあるとき
						if (value >= 8) {											//強さの期待値が7.5以上の時
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
					else {														//強さの期待値が7.5以下の時
						if (L5 == 13) {
							for (L1 = 1; L1 <= 4; L1++) {						//2があれば
								if (Card[13][L1] == 1) {						//2 出す
									num2 = 1;
									aCard[1] = 13;
									pmark[1] = L1;
									break;
								}
							}
						}
						else {													//２がなければ
							for (L0 = 13; L0 <= 1; L0--) {						//自分の手札の最強カードの番号
								for (L1 = 1; L1 <= 4; L1++) {					//と数を計算
									if (Card[L0][L1] == 1) {					//場に出されたカードの最強カード
										L2++;									//と自分の最強カードを比べ、強さ
										L6 = L0;								//一緒だったら、出す（数で判別）
										L7 = L1;
									}
								}
								if (L2 > 0) { break; }
							}													//２を例えとすると
							for (L0 = 13; L0 <= 1; L0--) {						//場に出されたカード+自分の手札の
								if (UseCard[L0] != 4) {							//カードが４だったら、相手の手札に
									if (L6 == L0) {								//２がないこと、
										num2 = 1;
										aCard[1] = L6;
										pmark[1] = L7;
										reset();
										L6 = 0, L7 = 0;
										break;
									}
									else {										//でなければ、小さい順
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

			case 2:																//一番強いカード以外のペアを出す
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
					if (c == 1) {												//joke 持ち
						num2 = 1;
						aCard[1] = 14;											//joke 出す
						pmark[1] = 5;											//jokeのマーク が５
						break;
					}
					else if (c == 0&& group[4] > 0) {							//4枚返し
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

			default:															//5枚以上の階段の場合
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
{																			//革命のとき
	for (L1 = 1; L1 <= 4; L1++) {											//決める札3の判定
			if (Card[1][L1] == 1) {
				L5 = 1;
				break;
			}
		}

	if (L5 > 0) {															//２、A、Kいずれを持つ場合
		switch (b) {														//革命でないとき
		case 0:																//先手
			if (value >= 9.5) {												//期待値が7.5より小さい場合
				if (c == 1) {												//joke 持ち
					num2 = 1;
					aCard[1] = 14;											//joke 出す
					pmark[1] = 5;											//jokeのマーク が５
					break;
				}
				else if (group[4] > 0 && c == 0) {							//joke なければ
					for (L0 = 13; L0 >= 1; L0--) {							//4枚カードを出す
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
				else if (group[4] == 0 && c == 0) {							//持ってない場合、4からだす。
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
			else {															//期待値が6.5より大きい場合、
				if (group[3] > 0) {											//2と3以外の３枚組があったら、３枚組を真っ先に出す
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
				if (num2 == 0) {										//なかったら、次へ
					if (group[1] > group[2]) {							//1枚カードのほうが多い場合
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
						if (num2 == 0) {								//なかったら、4からだす。
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
						if (num2 == 0) {								//なかったら、4からだす。
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
				if (Card[14][5] == 1) {											//手札にjokeがあるとき
					if (value <= 9.5) {											//強さの期待値が7.5以上の時
						if (FieldCard[1] >= 9) {								//フィールドのカードが7より
							for (L0 = 8; L0 >= 1; L0--) {						//小さいとき、8から出す
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
					else {														//強さの期待値が7.5以下の時
						if (L5 == 1) {
							for (L1 = 1; L1 <= 4; L1++) {						//2があれば
								if (Card[13][L1] == 1) {						//2 出す
									num2 = 1;
									aCard[1] = 1;
									pmark[1] = L1;
									break;
								}
							}
						}
						else if (L5 < 4 && L5>1) {													//２がなければ
							for (L0 = 1; L0 <= 13; L0++) {						//自分の手札の最強カードの番号
								for (L1 = 1; L1 <= 4; L1++) {					//と数を計算
									if (Card[L0][L1] == 1) {					//場に出されたカードの最強カード
										L2++;									//と自分の最強カードを比べ、強さ
										L6 = L0;								//一緒だったら、出す（数で判別）
										L7 = L1;
									}
								}
								if (L2 > 0) { break; }
							}													//２を例えとすると
							for (L0 = 13; L0 <= 1; L0--) {						//場に出されたカード+自分の手札の
								if (UseCard[L0] != 4) {							//カードが４だったら、相手の手札に
									if (L6 == L0) {								//２がないこと、
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
				else {															//ジョーカーないから、
					for (L0 = FieldCard[1] - 1; L0 > 0; L0--) {				//最大のカードと３以外
						for (L1 = 1; L1 <= 4; L1++) {							//ガンガン出せばいい
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

		case 2:																//一番強いカード以外のペアを出す
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
				if (group[4] > 0) {							//4枚返し
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

		default:															//5枚以上の階段の場合
			if (FieldNum == 5) {
				for (L1 = 1; L1 <= 4; L1++) {
					for (L0 = FieldCard[FieldNum] - 1; L0 >=FieldNum; L0--) {
						if (Card[L0][L1] == 1 && Card[L0 - 1][L1] == 1 && Card[L0 - 2][L1] == 1 && Card[L0 - 3][L1] == 1 && Card[L0 - 4][L1] == 1) {
							num2 = FieldNum;								//ここでは、ちょっとズルした。
							for (L2 = 1; L2 <= FieldNum; L2++) {			//僕だちの作戦は、できるだけ、２とAを残し
								pmark[L2] = L1;								//最後の決める札として、使いたいから、
								aCard[L2] = L0;					//相手が34567を出す場合返せるカードは
								L0--;										//8910JQと910JQKの2つしかない
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

	else if (L5 == 0) {															//２、A、K全部ない場合
		switch (b) {														//革命でないとき
		case 0:																//先手
			if (c == 1) {													//joke 持ち
				num2 = 1;
				aCard[1] = 14;												//joke 出す
				pmark[1] = 5;												//jokeのマーク が５
				break;
			}
			else if (group[4] > 0 && c == 0) {							//joke なければ
						for (L0 = 13; L0 >= 1; L0--) {							//4枚カードを出す
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
				if (group[3] > 0) {											//2と3以外の３枚組があったら、３枚組を真っ先に出す
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
				if (num2 == 0) {										//なかったら、次へ
					if (group[1] > group[2]) {							//1枚カードのほうが多い場合
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
						if (num2 == 0) {								//なかったら、4からだす。
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
					else if (group[1] < group[2]) {												//2枚カードのほうが多い場合
						for (L0 = 13; L0 >0; L0--) {					//2と3以外の1枚のカードを小さい順で出す
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
						if (num2 == 0) {								//なかったら、4からだす。
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
				if (Card[14][5] == 1) {											//手札にjokeがあるとき
					if (value <= 9.5) {											//強さの期待値が7.5以上の時
						if (FieldCard[1] >= 9) {								//フィールドのカードが7より
							for (L0 = 8; L0 >= 1; L0--) {						//小さいとき、8から出す
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
					else {														//強さの期待値が7.5以下の時
						if (L5 == 1) {
							for (L1 = 1; L1 <= 4; L1++) {						//2があれば
								if (Card[13][L1] == 1) {						//2 出す
									num2 = 1;
									aCard[1] = 1;
									pmark[1] = L1;
									break;
								}
							}
						}
						else if (L5 < 4 && L5>1) {													//２がなければ
							for (L0 = 1; L0 <= 13; L0++) {						//自分の手札の最強カードの番号
								for (L1 = 1; L1 <= 4; L1++) {					//と数を計算
									if (Card[L0][L1] == 1) {					//場に出されたカードの最強カード
										L2++;									//と自分の最強カードを比べ、強さ
										L6 = L0;								//一緒だったら、出す（数で判別）
										L7 = L1;
									}
								}
								if (L2 > 0) { break; }
							}													//２を例えとすると
							for (L0 = 13; L0 <= 1; L0--) {						//場に出されたカード+自分の手札の
								if (UseCard[L0] != 4) {							//カードが４だったら、相手の手札に
									if (L6 == L0) {								//２がないこと、
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
				else {															//ジョーカーないから、
					for (L0 = FieldCard[1] - 1; L0 < 0; L0--) {				//最大のカードと３以外
						for (L1 = 1; L1 <= 4; L1++) {							//ガンガン出せばいい
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

		case 2:																//一番強いカード以外のペアを出す
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
				if (group[3] > 0) {											//2と3以外の３枚組があったら、３枚組を真っ先に出す
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
				if (c == 1) {												//joke 持ち
					num2 = 1;
					aCard[1] = 14;											//joke 出す
					pmark[1] = 5;											//jokeのマーク が５
					break;
				}
				else if (c == 0 && group[4] > 0) {							//4枚返し
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

		default:															//5枚以上の階段の場合
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
	for (L0 = 13; L0 >= 1; L0--) {											//手札に残る一番強いカード
		for (L1 = 1; L1 <= 4; L1++) {										//の番号と枚数を検索し、記録する
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
			aCard[1] = 14;											//joke 出す
			pmark[1] = 5;											//jokeのマーク が５
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
		}
		break;
	}
}

void step2_1(int b, int c) {
	L4 = 0;
	for (L0 = 1; L0 <=13; L0++) {											//手札に残る一番強いカード
		for (L1 = 1; L1 <= 4; L1++) {										//の番号と枚数を検索し、記録する
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
			aCard[1] = 14;											//joke 出す
			pmark[1] = 5;											//jokeのマーク が５
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

