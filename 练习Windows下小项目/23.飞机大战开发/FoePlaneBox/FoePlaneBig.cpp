#include"FoePlaneBig.h"
#include"../GameConfig/GameConfig.h"


CFoePlaneBig::CFoePlaneBig(){

}
CFoePlaneBig::~CFoePlaneBig(){

}
void CFoePlaneBig::InitFoePlane(){
	::loadimage(&m_foeImg,PATH_PIC(foeplanebig.jpg));
	m_blood = DEF_FOEBIG_BLOOD;
	m_showId = 4;
	m_x = rand()%(IMG_BACKGROUND_WIDTH-IMG_FOEBIG_WIDHT+1);
	m_y = -IMG_FOEBIG_HEIGHT;
}
void CFoePlaneBig::ShowFoePlane(){
	::putimage(m_x,m_y,IMG_FOEBIG_WIDHT,IMG_FOEBIG_HEIGHT,
		&m_foeImg,IMG_FOEBIG_WIDHT,(4-m_showId)*IMG_FOEBIG_HEIGHT,SRCPAINT);

	::putimage(m_x,m_y,IMG_FOEBIG_WIDHT,IMG_FOEBIG_HEIGHT,
		&m_foeImg,0,(4-m_showId)*IMG_FOEBIG_HEIGHT,SRCAND);

}
bool CFoePlaneBig::IsHitGunner(CGunner* pGun){
	int x = pGun->m_x+IMG_GUNNER_WIDHT/2;
	if(m_x  <=x  && x <  m_x+IMG_FOEBIG_WIDHT  &&
		m_y <= pGun->m_y && pGun->m_y <= m_y+IMG_FOEBIG_HEIGHT){
		return true;
	}
	return false;
}
bool CFoePlaneBig::IsHitPlayer(CPlayer& player){
	int x1 = player.m_x+IMG_PLAYER_WIDHT/2;
	if(m_x  <= x1 && x1 <  m_x+IMG_FOEBIG_WIDHT  &&
		m_y <= player.m_y && player.m_y <= m_y+IMG_FOEBIG_HEIGHT){
		return true;
	}

	int y1 = player.m_y+IMG_PLAYER_HEIGHT/2;
	if(m_x  <= player.m_x && player.m_x <  m_x+IMG_FOEBIG_WIDHT  &&
		m_y <= y1 && y1 <= m_y+IMG_FOEBIG_HEIGHT){
		return true;
	}

	int x2 = player.m_x+IMG_PLAYER_WIDHT;
	if(m_x  <= x2 && x2 <  m_x+IMG_FOEBIG_WIDHT  &&
		m_y <= y1 && y1 <= m_y+IMG_FOEBIG_HEIGHT){
		return true;
	}

	return false;
}