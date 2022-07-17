#pragma once
#include<easyx.h>
#include"../GunnerBox/Gunner.h"
#include"../Player/Player.h"

class CFoePlane{
public:
	IMAGE m_foeImg;
	int   m_blood;
	int   m_showId;
	int   m_x;
	int   m_y;
public:
	CFoePlane();
	virtual ~CFoePlane();
public:
	virtual void InitFoePlane()=0;
	virtual void ShowFoePlane()=0;
	void MoveFoePlane(int step);
	virtual bool IsHitGunner(CGunner* pGun)=0;
	virtual bool IsHitPlayer(CPlayer& player)=0;


};