#include <DxLib.h>
#include <stdio.h>
#include "head.h"



void GameFrame::LoadFiles(){
	//�F�ݒ�
	white = GetColor(255,255,255);
	red   = GetColor(255,0,0);

	
	//�t�H���g�ݒ�



	//���ʉ�

	//�摜
	LoadDivGraph("card.png",52,13,5,48,64,gh_card);//�������I�ɂ̓W���[�J�[������53����

	////�a�f�l


}
void GameFrame::Reset(){
	exit_flag = 0;
	cursor_y = 290;
	cursor = 0;

	for(int i=0;i<52;i++){
		card[i].img = gh_card[i];
		card[i].suit = static_cast<CARDMARK>(i/13+1);
		card[i].num = i%13+1;
		card[i].place = -1;
		card[i].trush_flag=-1;
		if(i/13+1==5)
			card[i].suit = JOKER;
	}
	for(int i=0;i<4;i++){
		player[i].num_tehuda = 0;
		sprintf_s(player[i].name,"�v���C���[%d",i);
		NowBa.nowcard[i].img=0;
		NowBa.nowcard[i].num=0;
		NowBa.nowcard[i].place=0;
		NowBa.nowcard[i].suit=JOKER;
		NowBa.nowcard[i].trush_flag=0;
	}
	NowBa.nowmaisuu=0;
	NowBa.turn=0;
	NowBa.kaku_flag=0;
	count=0;

}


void GameFrame::drawGameTitle(){
	

	DrawFormatString( 380 , cursor_y ,white , "��" );
	DrawFormatString( 400 , 290      ,white, "NEW GAME" );
	DrawFormatString( 400 , 310      ,white,"LOG OUT");
	DrawFormatString( 400 , 370      ,white,"SELECT AND PUSH X");


		/*�������������ꂽ�Ƃ��̏���*/
	if(Key[KEY_INPUT_DOWN] == 1){
		cursor_y += 20;

	}
	else if(Key[ KEY_INPUT_UP] == 1){
		cursor_y -= 20;

	}
	//�s���߂��h�~
	if(cursor_y==270 )
		cursor_y = 310;
	else if( cursor_y == 330)
		cursor_y = 290;
	//X�������ꂽ�Ƃ��̏���
	if(Key[ KEY_INPUT_X ] >0){
		if(cursor_y == 290){
			setGameState(GAME_READY);}
		else if(cursor_y == 310){
			exit_flag=1;
				
		}
	}
}

int GameFrame::CheckCardCorrect(){	
	list<Card> Itizi;
	int maisuu=0;
	int i=0;

	for(it = player[NowBa.turn].tehuda.begin();it!=player[NowBa.turn].tehuda.end();it++){
		if((*it).trush_flag==1){
			Itizi.push_back((*it));
			maisuu++;
		}
	}
	if(Itizi.size()==0)
		return -1;

	//�o�����J�[�h�����ׂē���������
	it = Itizi.begin();
	Card a;
	if(Itizi.size()>1){
		for(i=0;i<Itizi.size()-1;i++){
			a = (*it);
			it++;
			if(a.num!=(*it).num)
				return -1;

		}
	}
	
	//��̃J�[�h�Ɩ������Ⴆ�΃G���[
	if(Itizi.size()!=NowBa.nowmaisuu && NowBa.nowmaisuu!=0)
		return -1;

	

	//�����̑傫����r
	it = Itizi.begin();
	//�v�����ĂȂ��ďo�����J�[�h��������������
	if(NowBa.kaku_flag==0 && NowBa.nowcard[0].num>=(*it).num){
		return -1;
		/*for(int i=0;i<maisuu;i++){
			NowBa.nowcard[i] = player[NowBa.turn].tehuda[i];
			//player[NowBa.turn].num_tehuda -= maisuu;
		return 0;*/
	}


	else if(NowBa.kaku_flag==1 && NowBa.nowcard[0].num<=(*it).num){
		return -1;
		/*for(int i=0;i<maisuu;i++){
			NowBa.nowcard[i] = player[NowBa.turn].tehuda[i];
			player[NowBa.turn].num_tehuda -= maisuu;
		}*/
		//return 0;
	}
	//�o�����̂�1���ŏꂪ��Ȃ炨��
	/*if(maisuu==1 && NowBa.status==0){
		for(int i=0;i<maisuu;i++){
			NowBa.nowcard[i] = player[NowBa.turn].tehuda[i];
			player[NowBa.turn].num_tehuda -= maisuu;
		}
		return 0;
	}*/
	it = player[NowBa.turn].tehuda.begin();
	while(it != player[NowBa.turn].tehuda.end()){
		if((*it).trush_flag==1)
			player[NowBa.turn].tehuda.erase(it);
		else 
			it++;
	}	
	
	return 0;
}




void GameFrame::drawGameReady(){
	DrawFormatString(100,50,white,"���Ȃ��̖��O����͂��Ă�������");
	KeyInputString(130,80,19,player[0].name,FALSE);
	setGameState(GAME_MAIN);
};







GAMESTATE GameFrame::setGameState(GAMESTATE state){
	if(gstate != state){
		gstate = state;
		starttime = GetNowCount();
	}
	return gstate;
}

//���ׂẴL�[�̉�������Ă���̃t���[����Ԃ��֐�
int GetHitKeyStateAll_2(int GetHitKeyStateAll_InputKey[]){
    char GetHitKeyStateAll_Key[256];
    GetHitKeyStateAll( GetHitKeyStateAll_Key );
    for(int i=0;i<256;i++){
        if(GetHitKeyStateAll_Key[i]==1) GetHitKeyStateAll_InputKey[i]++;
        else                            GetHitKeyStateAll_InputKey[i]=0;
    }
    return 0;
}
//���t���b�V�����[�g�����Ȉ�
void wait_fanc(){
    int term;
    static int t=0;
    term = GetNowCount()-t;
    if(16-term>0)
            Sleep(16-term);
    t=GetNowCount();
    return;
}//fps�\��
void fps(unsigned int counter){
    int i;
    static int t=0,ave=0,f[60];
 
    f[counter%60]=GetNowCount()-t;
    t=GetNowCount();
    if(counter%60==59){
        ave=0;
        for(i=0;i<60;i++)
            ave+=f[i];
        ave/=60;
    }
    if(ave!=0){
        DrawFormatString(1000, 750,GetColor(255,255,255),"%.1fFPS",1000.0/(double)ave);
        DrawFormatString(1000,7700,GetColor(255,255,255),"%dms"  ,ave);
    }
    return;
}
