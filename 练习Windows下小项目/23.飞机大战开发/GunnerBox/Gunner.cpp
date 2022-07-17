#include"Gunner.h"
#include"../GameConfig/GameConfig.h"

CGunner::CGunner(){
	m_x =0;
	m_y =0;
}
CGunner::~CGunner(){

}
void CGunner::InitGunner(int x, int y){
	::loadimage(&m_gunImg,PATH_PIC(gunner.jpg));
	m_x = x;
	m_y = y;
}
void CGunner::ShowGunner(){
	::putimage(m_x,m_y,IMG_GUNNER_WIDHT,IMG_GUNNER_HEIGHT,
		&m_gunImg,IMG_GUNNER_WIDHT,0,SRCPAINT);

	::putimage(m_x,m_y,IMG_GUNNER_WIDHT,IMG_GUNNER_HEIGHT,
		&m_gunImg,0,0,SRCAND);
}
void CGunner::MoveGunner(int step){
	m_y -=step;
}