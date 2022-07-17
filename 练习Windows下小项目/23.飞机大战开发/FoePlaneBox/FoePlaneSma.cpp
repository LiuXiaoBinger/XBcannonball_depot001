#include"FoePlaneSma.h"
#include"../GameConfig/GameConfig.h"


CFoePlaneSma::CFoePlaneSma(){

}
CFoePlaneSma::~CFoePlaneSma(){

}
void CFoePlaneSma::InitFoePlane(){
	::loadimage(&m_foeImg,PATH_PIC(foeplanesma.jpg));
	m_blood = DEF_FOESMA_BLOOD;
	m_showId = 2;
	m_x = rand()%(IMG_BACKGROUND_WIDTH-IMG_FOESMA_WIDHT+1);
	m_y = -IMG_FOESMA_HEIGHT;
}
void CFoePlaneSma::ShowFoePlane(){
	::putimage(m_x,m_y,IMG_FOESMA_WIDHT,IMG_FOESMA_HEIGHT,
		&m_foeImg,IMG_FOESMA_WIDHT,(2-m_showId)*IMG_FOESMA_HEIGHT,SRCPAINT);

	::putimage(m_x,m_y,IMG_FOESMA_WIDHT,IMG_FOESMA_HEIGHT,
		&m_foeImg,0,(2-m_showId)*IMG_FOESMA_HEIGHT,SRCAND);

}
bool CFoePlaneSma::IsHitGunner(CGunner* pGun){
	int x = pGun->m_x+IMG_GUNNER_WIDHT/2;
	if(m_x  <=x  && x <  m_x+IMG_FOESMA_WIDHT  &&
		m_y <= pGun->m_y && pGun->m_y <= m_y+IMG_FOESMA_HEIGHT){
		return true;
	}
	return false;
}
bool CFoePlaneSma::IsHitPlayer(CPlayer& player){

	int x1 = player.m_x+IMG_PLAYER_WIDHT/2;
	if(m_x  <= x1 && x1 <  m_x+IMG_FOESMA_WIDHT  &&
		m_y <= player.m_y && player.m_y <= m_y+IMG_FOESMA_HEIGHT){
		return true;
	}

	int y1 = player.m_y+IMG_PLAYER_HEIGHT/2;
	if(m_x  <= player.m_x && player.m_x <  m_x+IMG_FOESMA_WIDHT  &&
		m_y <= y1 && y1 <= m_y+IMG_FOESMA_HEIGHT){
		return true;
	}

	int x2 = player.m_x+IMG_PLAYER_WIDHT;
	if(m_x  <= x2 && x2 <  m_x+IMG_FOESMA_WIDHT  &&
		m_y <= y1 && y1 <= m_y+IMG_FOESMA_HEIGHT){
		return true;
	}

	return false;
}