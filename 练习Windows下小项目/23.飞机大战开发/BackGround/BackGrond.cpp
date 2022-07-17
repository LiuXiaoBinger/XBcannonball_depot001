
#include"BackGrond.h"
#include"../GameConfig/GameConfig.h"

CBackGround::CBackGround(){
	m_x = 0;
	m_y = 0;
}
CBackGround::~CBackGround(){

}

void CBackGround::InitBackGround(){
	::loadimage(&m_backImg,"./res/background.jpg");   //路径相对于 工程文件
	m_x =0;
	m_y = -IMG_BACKGROUND_HEIGHT;
}
void CBackGround::showBackGround(){

	::putimage(m_x,m_y,&m_backImg);

}
void CBackGround::MoveBackGround(int step){

	m_y+= step;
	if(m_y>0){  //判断背景移动到最大限度，恢复到初始的位置
		m_y = -IMG_BACKGROUND_HEIGHT;
	}

}