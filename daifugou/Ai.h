	// ----- 手札情報
extern	int Stat ;		// 2:大富豪 1:富豪 -1:貧民 0:平民
extern	int CardNum ;	// 持ってるカードの枚数
extern	int Card[15][6] ;	// 手札の枚数:
					// 　[1]-3  [2]-4 [3]-5  [4]-6  [5]-7  [6]-8 [7]-9
					//   [8]-10 [9]-J [10]-Q [11]-K [12]-A [13]-2
					//   [14]-ジョーカーの枚数

	// ----- 場札情報
extern	int FieldCard[13] ;			// 場札のカード番号
extern	int FieldNum ;			// 場札のカード枚数
extern	int UseNum ;			// これまでに場に出されたカードの枚数
extern	int UseCard[15] ;		// これまでに場に出された各カードの枚数:
							// 　[1]-3  [2]-4 [3]-5  [4]-6  [5]-7  [6]-8 [7]-9
							//   [8]-10 [9]-J [10]-Q [11]-K [12]-A [13]-2
							//   [14]-ジョーカーの枚数
							//   [0]にはUseNumと同じ値が入っている。

	// ----- 他プレイヤー情報
extern	int PlayerNum ;			// ゲーム中のプレイヤー数(自分を含まない)
extern	int PlayerCard[5] ;		// 他プレイヤーの残りカード枚数[0]～[PlayerNum-1]

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
