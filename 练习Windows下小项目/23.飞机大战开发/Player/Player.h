#pragma once
#include<easyx.h>
#include"../GunnerBox/Gunner.h"


class CPlayer{
public:
	IMAGE m_playerImg;
	IMAGE m_playerMaskImg;
	int   m_x;
	int   m_y;
public:
	CPlayer();
	~CPlayer();
public:
	void InitPlayer();
	void ShowPlayer();
	void MovePlayer(int direct, int step);
	CGunner*  SendGunner();

};