#include "stdafx.h"
#include "cVillage1Scene.h"


cVillage1Scene::cVillage1Scene()
{
	
}


cVillage1Scene::~cVillage1Scene()
{
}

void cVillage1Scene::Setup()
{
	m_rtShop = RectMake(100, 100, 160, 120);
	m_rtForge = RectMake(100, 620, 160, 120);
	m_rtDun1 = RectMake(600, 80, 160, 120);
	m_rtDun2 = RectMake(600, 600, 160, 120);

	m_rtShopEnt = RectMake(140, 180, 80, 40);
	m_rtForgeEnt = RectMake(140, 700, 80, 40);
	m_rtDun1Ent = RectMake(640, 160, 80, 40);
	m_rtDun2Ent = RectMake(640, 680, 80, 40);
}

void cVillage1Scene::Update()
{
}

void cVillage1Scene::Render()
{
	RectangleMake(g_hDC, m_rtShop);
	RectangleMake(g_hDC, m_rtForge);
	RectangleMake(g_hDC, m_rtDun1);
	RectangleMake(g_hDC, m_rtDun2);
	RectangleMake(g_hDC, m_rtShopEnt);
	RectangleMake(g_hDC, m_rtForgeEnt);
	RectangleMake(g_hDC, m_rtDun1Ent);
	RectangleMake(g_hDC, m_rtDun2Ent);
    
}

void cVillage1Scene::Release()
{
}
