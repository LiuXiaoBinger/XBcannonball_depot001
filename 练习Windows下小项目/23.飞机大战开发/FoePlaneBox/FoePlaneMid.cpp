#include"FoePlaneMid.h"
#include"../GameConfig/GameConfig.h"


CFoePlaneMid::CFoePlaneMid(){

}
CFoePlaneMid::~CFoePlaneMid(){

}
void CFoePlaneMid::InitFoePlane(){
	::loadimage(&m_foeImg,PATH_PIC(foeplanemid.jpg));
	m_blood = DEF_FOEMID_BLOOD;
	m_showId = 3;
	m_x = rand()%(IMG_BACKGROUND_WIDTH-IMG_FOEMID_WIDHT+1);
	m_y = -IMG_FOEMID_HEIGHT;
}
void CFoePlaneMid::ShowFoePlane(){
	::putimage(m_x,m_y,IMG_FOEMID_WIDHT,IMG_FOEMID_HEIGHT,
		&m_foeImg,IMG_FOEMID_WIDHT,(3-m_showId)*IMG_FOEMID_HEIGHT,SRCPAINT);

	::putimage(m_x,m_y,IMG_FOEMID_WIDHT,IMG_FOEMID_HEIGHT,
		&m_foeImg,0,(3-m_showId)*IMG_FOEMID_HEIGHT,SRCAND);

}
bool CFoePlaneMid::IsHitGunner(CGunner* pGun){
	int x = pGun->m_x+IMG_GUNNER_WIDHT/2;
	if(m_x  <=x  && x <  m_x+IMG_FOEMID_WIDHT  &&
		m_y <= pGun->m_y && pGun->m_y <= m_y+IMG_FOEMID_HEIGHT){
		return true;
	}
	return false;
}
bool CFoePlaneMid::IsHitPlayer(CPlayer& player){

	int x1 = player.m_x+IMG_PLAYER_WIDHT/2;
	if(m_x  <= x1 && x1 <  m_x+IMG_FOEMID_WIDHT  &&
		m_y <= player.m_y && player.m_y <= m_y+IMG_FOEMID_HEIGHT){
		return true;
	}

	int y1 = player.m_y+IMG_PLAYER_HEIGHT/2;
	if(m_x  <= player.m_x && player.m_x <  m_x+IMG_FOEMID_WIDHT  &&
		m_y <= y1 && y1 <= m_y+IMG_FOEMID_HEIGHT){
		return true;
	}

	int x2 = player.m_x+IMG_PLAYER_WIDHT;
	if(m_x  <= x2 && x2 <  m_x+IMG_FOEMID_WIDHT  &&
		m_y <= y1 && y1 <= m_y+IMG_FOEMID_HEIGHT){
		return true;
	}


	return false;
}