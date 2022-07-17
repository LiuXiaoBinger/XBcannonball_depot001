#include"PlayerApp.h"
#include"../GameConfig/GameConfig.h"
#include<time.h>
#include"../FoePlaneBox/FoePlaneBig.h"
#include"../FoePlaneBox/FoePlaneMid.h"
#include"../FoePlaneBox/FoePlaneSma.h"

DYNAMIC_OBJECT(CPlaneApp)
WINDOW_PARAM(WINDOW_X,WINDOW_Y,WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_TITLE)


CPlaneApp::CPlaneApp(){
	m_nScore =0;
}
CPlaneApp::~CPlaneApp(){

}

void CPlaneApp::InitGame(){
	//设置随机种子
	srand((unsigned int)time(NULL));


	//初始化背景
	m_back.InitBackGround();
	//初始化玩家飞机
	m_player.InitPlayer();

	m_gunBox.ShowAllGunner();


	::loadimage(&m_scoreImg,PATH_PIC(cardboard.png));



	//设定背景移动的定时器
	::SetTimer(m_hWnd,TIMER_BACKGROUND_MOVE_ID,TIMER_BACKGROUND_MOVE_INTERVAL,nullptr);

	::SetTimer(m_hWnd,TIMER_PLAYER_MOVE_ID,TIMER_PLAYER_MOVE_INTERVAL,nullptr);

	//炮弹移动
	::SetTimer(m_hWnd,TIMER_GUNNER_MOVE_ID,TIMER_GUNNER_MOVE_INTERVAL,nullptr);
	//炮弹定时发射
	::SetTimer(m_hWnd,TIMER_GUNNER_SEND_ID,TIMER_GUNNER_SEND_INTERVAL,nullptr);
	
	//敌人飞机定时移动
	::SetTimer(m_hWnd,TIMER_FOEBIG_MOVE_ID,TIMER_FOEBIG_MOVE_INTERVAL,nullptr);
	

	::SetTimer(m_hWnd,TIMER_FOEBIG_CREATE_ID,TIMER_FOEBIG_CREATE_INTERVAL,nullptr);
	::SetTimer(m_hWnd,TIMER_FOEMID_CREATE_ID,TIMER_FOEMID_CREATE_INTERVAL,nullptr);
	::SetTimer(m_hWnd,TIMER_FOESMA_CREATE_ID,TIMER_FOESMA_CREATE_INTERVAL,nullptr);
	
	::SetTimer(m_hWnd,TIMER_IS_HIT_ID,TIMER_IS_HIT_INTERVAL,nullptr);

	::SetTimer(m_hWnd,TIMER_CHANGE_SHOWID_ID,TIMER_CHANGE_SHOWID_INTERVAL,nullptr);
	
	
	
}
void CPlaneApp::PaintGame(){
	//显示背景图片
	m_back.showBackGround();

	//显示玩家飞机
	m_player.ShowPlayer();

	m_gunBox.ShowAllGunner();

	//显示正常的敌人飞机
	m_foeBox.ShowAllFoePlane();

	//显示爆炸的敌人飞机
	m_foeBox.ShowAllBoomFoePlane();

	//显示分数
	ShowScore();


}
void CPlaneApp::CloseGame(){

}


#define CREATE_FOE(FOE_CLASS)\
	CFoePlane* pFoe = new FOE_CLASS;\
	pFoe->InitFoePlane();\
	m_foeBox.m_lstFoe.push_back(pFoe);


//定时器消息的处理函数
void CPlaneApp::ON_WM_TIMER(WPARAM w,LPARAM l){

	switch (w)
	{
	case TIMER_BACKGROUND_MOVE_ID:  //背景移动
		{
			m_back.MoveBackGround(	TIMER_BACKGROUND_MOVE_STEP);				  
								  
		}
		break;
	case TIMER_PLAYER_MOVE_ID:  //玩家飞机的移动
		{
			if(::GetAsyncKeyState(VK_LEFT)){   //定时检测房间键左 ，是否按下
				m_player.MovePlayer(VK_LEFT,TIMER_PLAYER_MOVE_STEP);
			}	
			if(::GetAsyncKeyState(VK_RIGHT)){   //定时检测房间键右 ，是否按下
				m_player.MovePlayer(VK_RIGHT,TIMER_PLAYER_MOVE_STEP);
			}
			if(::GetAsyncKeyState(VK_UP)){   //定时检测房间键上 ，是否按下
				m_player.MovePlayer(VK_UP,TIMER_PLAYER_MOVE_STEP);
			}	
			if(::GetAsyncKeyState(VK_DOWN)){   //定时检测房间键下 ，是否按下
				m_player.MovePlayer(VK_DOWN,TIMER_PLAYER_MOVE_STEP);
			}	

		}
		break;
	case TIMER_GUNNER_MOVE_ID:   //炮弹移动的定时器
		{
			m_gunBox.MoveAllGunner(TIMER_GUNNER_MOVE_STEP);
		}
		break;

	case TIMER_GUNNER_SEND_ID:  //炮弹定时发射
		{
			CGunner * pGun = m_player.SendGunner();  //发射炮弹
			m_gunBox.m_lstGun.push_back(pGun);     //炮弹放到炮弹盒子里
		
		}
		break;
	case TIMER_FOEBIG_MOVE_ID:
		{
			m_foeBox.MoveAllFoePlane();
		
		}
		break;
	case TIMER_FOEBIG_CREATE_ID:
		{
			//CFoePlane* pFoe = new CFoePlaneBig;
			//pFoe->InitFoePlane();
			//m_foeBox.m_lstFoe.push_back(pFoe);
			//创建敌人飞机，并添加到敌人飞机链表中
			CREATE_FOE(CFoePlaneBig)
		}
		break;
	case TIMER_FOEMID_CREATE_ID:
		{
			CREATE_FOE(CFoePlaneMid)
		}
		break;
	case TIMER_FOESMA_CREATE_ID:
		{
			CREATE_FOE(CFoePlaneSma)
		}
		break;
	case TIMER_IS_HIT_ID:   //定时检测是否撞击（敌人飞机-》炮弹，敌人飞机-》玩家飞机）
		{
			list<CFoePlane*>::iterator iteFoe =   m_foeBox.m_lstFoe.begin();
			while(iteFoe  != m_foeBox.m_lstFoe.end()){
				bool isBoom = false;


				if(  (*iteFoe) ){
					//-----------------------------
					//1. 判断是否撞击玩家飞机
					if( (*iteFoe)->IsHitPlayer(m_player)  ){
						
						//GameOver
						GameOver();
						return ;
					}
					// 2. 判断是否撞击炮弹
					list<CGunner*>::iterator iteGun =   m_gunBox.m_lstGun.begin();
					while(iteGun !=   m_gunBox.m_lstGun.end()){
						if( (*iteFoe)->IsHitGunner(*iteGun) ){ //是否撞击到炮弹
						
							delete (*iteGun);  //删除炮弹
							(*iteGun) = nullptr;

							//删除节点
							iteGun = m_gunBox.m_lstGun.erase(iteGun);

							//掉血
							(*iteFoe)->m_blood-=DEF_GUNNER_HURT;
							if( (*iteFoe)->m_blood <=0){
								m_foeBox.m_lstBoomFoe.push_back(*iteFoe);  //添加到爆炸链表中

								iteFoe = m_foeBox.m_lstFoe.erase(iteFoe);
								isBoom = true;

								m_nScore+=3;


								break;
							}


							continue;
						}
						
						iteGun++;
					}

					//-----------------------------
				}
				if(!isBoom)
					iteFoe++;
			}
		}
		break;

	case TIMER_CHANGE_SHOWID_ID:
		{
			list<CFoePlane*>::iterator iteBoom =  m_foeBox.m_lstBoomFoe.begin();
			while(iteBoom !=  m_foeBox.m_lstBoomFoe.end()){
				
				(*iteBoom)->m_showId--;
				if((*iteBoom)->m_showId <0 ){
					delete (*iteBoom);
					(*iteBoom) = nullptr;

				
					iteBoom = m_foeBox.m_lstBoomFoe.erase(iteBoom);
					continue;
				}

				iteBoom++;
			}
		}
		break;
	}

}

//键盘按下消息处理
void CPlaneApp::ON_WM_KEYDOWN(WPARAM w){
	//m_player.MovePlayer(w,TIMER_PLAYER_MOVE_STEP);
}

void CPlaneApp::GameOver(){
	//停止所有定时器
	::KillTimer(m_hWnd,TIMER_BACKGROUND_MOVE_ID);

	::KillTimer(m_hWnd,TIMER_PLAYER_MOVE_ID);

	::KillTimer(m_hWnd,TIMER_GUNNER_MOVE_ID);
	::KillTimer(m_hWnd,TIMER_GUNNER_SEND_ID);
	
	::KillTimer(m_hWnd,TIMER_FOEBIG_MOVE_ID);

	::KillTimer(m_hWnd,TIMER_FOEBIG_CREATE_ID);
	::KillTimer(m_hWnd,TIMER_FOEMID_CREATE_ID);
	::KillTimer(m_hWnd,TIMER_FOESMA_CREATE_ID);
	
	::KillTimer(m_hWnd,TIMER_IS_HIT_ID);
	::KillTimer(m_hWnd,TIMER_CHANGE_SHOWID_ID);

	::MessageBox(m_hWnd,"GameOver","游戏结束",MB_OK);

	//程序自动退出，发送退出WM_CLOSE的消息
	::PostMessage(m_hWnd,WM_CLOSE,0,0);
}

void CPlaneApp::ShowScore(){
	::putimage(0,0,&m_scoreImg);
	char score[5]={0};
	itoa(m_nScore,score,10);
	RECT rect={0,0,180,60};
	settextcolor(RGB(255,0,0));
	::drawtext(score,&rect,DT_CENTER);
	
}