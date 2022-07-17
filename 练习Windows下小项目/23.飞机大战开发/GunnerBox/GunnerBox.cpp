#include"GunnerBox.h"
#include"../GameConfig/GameConfig.h"
CGunnerBox::CGunnerBox(){

}
CGunnerBox::~CGunnerBox(){
	list<CGunner*>::iterator ite =   m_lstGun.begin();
	while(ite !=   m_lstGun.end()){   //遍历删除 new 炮弹
		if((*ite)){
			delete (*ite);
			(*ite) = nullptr;
		}

		ite++;
	}
	m_lstGun.clear();  //删除所有节点
}

void CGunnerBox::ShowAllGunner(){
	list<CGunner*>::iterator ite =   m_lstGun.begin();
	while(ite !=   m_lstGun.end()){   //遍历删除 new 炮弹
		if((*ite)){
			(*ite)->ShowGunner();
		}

		ite++;
	}
}
void CGunnerBox::MoveAllGunner(int step){
	list<CGunner*>::iterator ite =   m_lstGun.begin();
	while(ite !=   m_lstGun.end()){   //遍历删除 new 炮弹
		if((*ite)){
			(*ite)->MoveGunner(step);

			//判断炮弹是否出界，出界则删除
			if(  (*ite)->m_y<= - IMG_GUNNER_HEIGHT  ){
				delete (*ite);
				(*ite) = nullptr;   //删除new的炮弹

				ite = m_lstGun.erase(ite);  //删除节点
				continue;
			}
		}

		ite++;
	}
}