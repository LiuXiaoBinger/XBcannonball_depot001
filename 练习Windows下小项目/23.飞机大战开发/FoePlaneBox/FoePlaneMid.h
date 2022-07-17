#pragma once
#include"FoePlane.h"
class CFoePlaneMid:public CFoePlane{
public:
	CFoePlaneMid();
	~CFoePlaneMid();
public:
	virtual void InitFoePlane();
	virtual void ShowFoePlane();
	virtual bool IsHitGunner(CGunner* pGun);
	virtual bool IsHitPlayer(CPlayer& player);

};