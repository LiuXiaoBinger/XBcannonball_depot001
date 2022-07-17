#pragma once
#include<list>
#include"FoePlane.h"
using namespace std;

class CFoePlaneBox{
public:
	list<CFoePlane*>  m_lstFoe;
	list<CFoePlane*>  m_lstBoomFoe;
public:
	CFoePlaneBox();
	~CFoePlaneBox();
public:
	void ShowAllFoePlane();
	void ShowAllBoomFoePlane();
	void MoveAllFoePlane();

};