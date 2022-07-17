#pragma once
#include<easyx.h>

class CBackGround{
public:
	IMAGE m_backImg;
	int   m_x;
	int   m_y;
public:
	CBackGround();
	~CBackGround();
public:
	void InitBackGround();
	void showBackGround();
	void MoveBackGround(int step);


};