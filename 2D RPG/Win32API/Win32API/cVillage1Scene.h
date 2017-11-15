#pragma once
#include "cGameNode.h"
class cVillage1Scene :public cGameNode
{
private:
	RECT		m_rtDun1;
	RECT		m_rtDun2;
	RECT		m_rtShop;
	RECT		m_rtForge;

	RECT		m_rtDun1Ent;
	RECT		m_rtDun2Ent;
	RECT		m_rtShopEnt;
	RECT		m_rtForgeEnt;

public:
	cVillage1Scene();
	virtual ~cVillage1Scene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

