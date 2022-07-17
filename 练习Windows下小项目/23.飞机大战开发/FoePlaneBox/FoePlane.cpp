#include"FoePlane.h"



CFoePlane::CFoePlane(){
	m_blood = 0;
	m_showId= 0;
	m_x= 0;
	m_y= 0;
}
CFoePlane::~CFoePlane(){

}
	
void CFoePlane::MoveFoePlane(int step){
	m_y+=step;
}
	