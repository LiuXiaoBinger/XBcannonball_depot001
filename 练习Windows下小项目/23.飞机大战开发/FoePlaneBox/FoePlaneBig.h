#pragma once
#include"FoePlane.h"

class CFoePlaneBig:public CFoePlane{
public:
	CFoePlaneBig();
	~CFoePlaneBig();
public:
	virtual void InitFoePlane();
	virtual void ShowFoePlane();
	virtual bool IsHitGunner(CGunner* pGun);
	virtual bool IsHitPlayer(CPlayer& player);

};