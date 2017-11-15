#pragma once
#include "cGameNode.h"



class cPlayer : public cGameNode
{
private:
	float				m_fPosX;
	float				m_fPosY;
	RECT				m_rtPlayer;
	int					m_nPlayerAtk;
	int					m_nPlayerDef;
	int					m_nPlayerMax_Hp;
	int					m_nPlayerCurr_Hp;
	int					m_nPlayerLevel;


	RECT				m_rtShopEnt;
	RECT				m_rtForgeEnt;
	RECT				m_rtDun1Ent;
	RECT				m_rtDun2Ent;


	bool				m_isLoadScene;
	bool				m_isMove;
	int					m_nMoveDelay;
public:
	cPlayer();
	virtual ~cPlayer();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

