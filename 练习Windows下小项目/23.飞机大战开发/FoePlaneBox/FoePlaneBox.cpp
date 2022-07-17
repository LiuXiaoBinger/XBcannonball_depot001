#include<typeinfo>
#include"FoePlaneBox.h"
#include"FoePlaneBig.h"
#include"FoePlaneMid.h"
#include"FoePlaneSma.h"
#include"../GameConfig/GameConfig.h"

CFoePlaneBox::CFoePlaneBox(){

}

#define DELETE_FOE(LIST)\
	list<CFoePlane*>::iterator ite##LIST = LIST.begin();\
	while( ite##LIST != LIST.end()  ){\
		if( *ite##LIST ){\
			delete ( *ite##LIST );\
			( *ite##LIST ) = nullptr;\
		}\
		ite##LIST++;\
	}\
	LIST.clear();


CFoePlaneBox::~CFoePlaneBox(){
	/*list<CFoePlane*>::iterator ite = m_lstFoe.begin();
	while( ite != m_lstFoe.end()  ){
		if( *ite ){
			delete ( *ite );
			( *ite ) = nullptr;
		}
		ite++;
	}
	m_lstFoe.clear();*/
	DELETE_FOE(m_lstFoe)

	DELETE_FOE(m_lstBoomFoe)

}

void CFoePlaneBox::ShowAllFoePlane(){
	list<CFoePlane*>::iterator ite = m_lstFoe.begin();
	while( ite != m_lstFoe.end()  ){
		if( *ite ){
			(*ite)->ShowFoePlane();
		}
		ite++;
	}
}
void CFoePlaneBox::ShowAllBoomFoePlane(){
	list<CFoePlane*>::iterator ite = m_lstBoomFoe.begin();
	while( ite != m_lstBoomFoe.end()  ){
		if( *ite ){
			(*ite)->ShowFoePlane();
		}
		ite++;
	}
}


void CFoePlaneBox::MoveAllFoePlane(){
	list<CFoePlane*>::iterator ite = m_lstFoe.begin();
	while( ite != m_lstFoe.end()  ){
		if( *ite ){

			//*ite    ==  CFoePlane*
			//**ite    ==  *(CFoePlane*)

			//RTTI (RunTime Type Id) 运行时类型识别
			if( typeid(**ite)==typeid(CFoePlaneBig)){
				(*ite)->MoveFoePlane(TIMER_FOEBIG_MOVE_STEP);
			}else if(typeid(**ite)==typeid(CFoePlaneMid)){
				(*ite)->MoveFoePlane(TIMER_FOEMID_MOVE_STEP);
			}else if(typeid(**ite)==typeid(CFoePlaneSma)){
				(*ite)->MoveFoePlane(TIMER_FOESMA_MOVE_STEP);
			}

			//判断是否出界
			if((*ite)->m_y>=IMG_BACKGROUND_HEIGHT){
				// 删除子类飞机
				delete *ite;
				*ite = nullptr;

				//删除节点
				ite = m_lstFoe.erase(ite);
				continue;
			
			}
		}

		ite++;
	}
}