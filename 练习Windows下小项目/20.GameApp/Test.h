#pragma once
#include"GameFrame.h"
class CTest :public CGameFrame 
{
public:
	CTest(void);
	~CTest(void);

	virtual void InitGame();
	virtual void PaintGame();
	virtual void CloseGame();


};

