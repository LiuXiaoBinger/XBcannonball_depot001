#include"Player.h"
#include"../GameConfig/GameConfig.h"


CPlayer::CPlayer(){
	m_x = 0;
	m_y = 0;
}
CPlayer::~CPlayer(){

}

void CPlayer::InitPlayer(){
	::loadimage(&m_playerImg,PATH_PIC(playerplane.jpg));
	::loadimage(&m_playerMaskImg,PATH_PIC(playerplane-mask.jpg));
	

	m_x = (IMG_BACKGROUND_WIDTH - IMG_PLAYER_WIDHT)/2;
	m_y = IMG_BACKGROUND_HEIGHT - IMG_PLAYER_HEIGHT;
}
void CPlayer::ShowPlayer(){
	::putimage(m_x,m_y,&m_playerMaskImg,SRCPAINT);   //屏蔽图与 背景做 位或操作
	::putimage(m_x,m_y,&m_playerImg,SRCAND);         //上一步的结果图，与 原图做 位与操作
}
void CPlayer::MovePlayer(int direct, int step){

	switch (direct)
	{
	case VK_LEFT:
		{
			if( m_x-step >=0){
				m_x-=step;
			}else{
				m_x = 0;
			}
		}
		break;
	case VK_RIGHT:
		{
			if( m_x+step <=IMG_BACKGROUND_WIDTH - IMG_PLAYER_WIDHT){
				m_x+=step;
			}else{
				m_x = IMG_BACKGROUND_WIDTH - IMG_PLAYER_WIDHT;
			}
		}
		break;
	case VK_UP:
		{
			if(m_y-step>=0){
				m_y-=step;
			}else{
				m_y = 0;
			}
		}
		break;
	case VK_DOWN:
		{
			if(m_y+step<=IMG_BACKGROUND_HEIGHT - IMG_PLAYER_HEIGHT){
				m_y+=step;
			}else{
				m_y = IMG_BACKGROUND_HEIGHT - IMG_PLAYER_HEIGHT;
			}
		}
		break;
	}

}
CGunner*  CPlayer::SendGunner(){

	CGunner * pGun = new CGunner;
	pGun->InitGunner(m_x+(IMG_PLAYER_WIDHT-IMG_GUNNER_WIDHT)/2,m_y-IMG_GUNNER_HEIGHT);

	return pGun;
}