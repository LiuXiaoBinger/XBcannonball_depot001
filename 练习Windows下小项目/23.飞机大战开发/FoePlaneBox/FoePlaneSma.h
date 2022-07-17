#pragma once

#include"FoePlane.h"
class CFoePlaneSma:public CFoePlane{
public:
	CFoePlaneSma();
	~CFoePlaneSma();
public:
	virtual void InitFoePlane();
	virtual void ShowFoePlane();
	virtual bool IsHitGunner(CGunner* pGun);
	virtual bool IsHitPlayer(CPlayer& player);

};