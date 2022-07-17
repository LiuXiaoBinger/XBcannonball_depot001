#pragma once
#include"../GameFrame/GameFrame.h"
#include"../BackGround/BackGrond.h"
#include"../Player/Player.h"
#include"../GunnerBox/GunnerBox.h"
#include"../FoePlaneBox/FoePlaneBox.h"

class CPlaneApp:public CGameFrame{
public:
	CBackGround  m_back;
	CPlayer      m_player;
	CGunnerBox   m_gunBox;
	CFoePlaneBox m_foeBox;
	IMAGE        m_scoreImg;
	int          m_nScore;
public:
	CPlaneApp();
	~CPlaneApp();

public:
	virtual void InitGame();
	virtual void PaintGame();
	virtual void CloseGame();

public:
	virtual void ON_WM_TIMER(WPARAM w,LPARAM l);
	virtual void ON_WM_KEYDOWN(WPARAM w);

public:
	void GameOver();
	void ShowScore();


};