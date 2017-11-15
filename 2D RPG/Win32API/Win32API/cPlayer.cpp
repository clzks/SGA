#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
{

}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	// 마을 1의 좌표
	//m_rtShop = RectMake(100, 100, 160, 120);
	//m_rtForge = RectMake(100, 620, 160, 120);
	//m_rtDun1 = RectMake(600, 80, 160, 120);
	//m_rtDun2 = RectMake(600, 600, 160, 120);
	
	m_rtShopEnt = RectMake(140, 180, 80, 40);
	m_rtForgeEnt = RectMake(140, 700, 80, 40);
	m_rtDun1Ent = RectMake(640, 160, 80, 40);
	m_rtDun2Ent = RectMake(640, 680, 80, 40);

	m_fPosX = 400;
	m_fPosY = 400;

	m_rtPlayer = RectMake(m_fPosX, m_fPosY, 20, 20);
	m_isMove = false;
	m_nMoveDelay = 0;
	m_isLoadScene = true;
	// 플레이어 능력치, 저장 필수
	m_nPlayerAtk = 10;
	m_nPlayerDef = 5;
	m_nPlayerMax_Hp = 100;
	m_nPlayerCurr_Hp = 100;
	m_nPlayerLevel = 1;
}

void cPlayer::Update()
{
	json js;
	ifstream LoadPlace;
	LoadPlace.open("SavePlace.json");
	js << LoadPlace;
	LoadPlace.close();
	RECT rt;

	if (IntersectRect(&rt, &m_rtPlayer, &m_rtShopEnt))
	{
		m_isLoadScene = false;
		js["Place"] = SLIST_VIL1SHOP;
		ofstream SavePlace;
		SavePlace.open("SavePlace.json");
		js >> SavePlace;
		SavePlace.close();
	}
	else if (IntersectRect(&rt, &m_rtPlayer, &m_rtForgeEnt))
	{
		m_isLoadScene = false;
		js["Place"] = SLIST_VIL1FORGE;
		ofstream SavePlace;
		SavePlace.open("SavePlace.json");
		js >> SavePlace;
		SavePlace.close();
	}
	else if (IntersectRect(&rt, &m_rtPlayer, &m_rtDun1Ent))
	{
		m_isLoadScene = false;
		js["Place"] = SLIST_VIL1DUN1;
		ofstream SavePlace;
		SavePlace.open("SavePlace.json");
		js >> SavePlace;
		SavePlace.close();
	}
	else if (IntersectRect(&rt, &m_rtPlayer, &m_rtDun2Ent))
	{
		m_isLoadScene = false;
		js["Place"] = SLIST_VIL1DUN2;
		ofstream SavePlace;
		SavePlace.open("SavePlace.json");
		js >> SavePlace;
		SavePlace.close();
	}



#pragma region 마을1 상점 진입
	if (js["Place"] == SLIST_VIL1SHOP && m_isLoadScene == false)
	{
		m_fPosX = 380.0f;
		m_fPosY = 700.0f;
		m_isLoadScene = true;
		g_pSceneManager->ChangeScene(SLIST_VIL1SHOP);
	}
#pragma endregion
#pragma region 마을1 무기상점 진입
	if (js["Place"] == SLIST_VIL1FORGE && m_isLoadScene == false)
	{
		m_fPosX = 380.0f;
		m_fPosY = 700.0f;
		m_isLoadScene = true;
		g_pSceneManager->ChangeScene(SLIST_VIL1FORGE);
	}
#pragma endregion
#pragma region 마을1 던전1 진입
	if (js["Place"] == SLIST_VIL1DUN1 && m_isLoadScene == false)
	{
		m_fPosX = 380.0f;
		m_fPosY = 700.0f;
		m_isLoadScene = true;
		g_pSceneManager->ChangeScene(SLIST_VIL1DUN1);
	}
#pragma endregion
#pragma region 마을1 던전2 진입
	if (js["Place"] == SLIST_VIL1DUN2 && m_isLoadScene == false)
	{
		m_fPosX = 380.0f;
		m_fPosY = 700.0f;
		m_isLoadScene = true;
		g_pSceneManager->ChangeScene(SLIST_VIL1DUN2);
	}
#pragma endregion

	m_rtPlayer = RectMake(m_fPosX, m_fPosY, 20, 20);
	if (g_pKeyManager->isStayKeyDown(VK_LEFT) && m_isMove == false)
	{	
		m_isMove = true;
		m_fPosX -= 20;
	}
	else if(g_pKeyManager->isStayKeyDown(VK_RIGHT) && m_isMove == false)
	{
		m_isMove = true;
		m_fPosX += 20;
	}
	if(g_pKeyManager->isStayKeyDown(VK_UP) && m_isMove == false)
	{
		m_isMove = true;
		m_fPosY -= 20;
	}
	else if(g_pKeyManager->isStayKeyDown(VK_DOWN) && m_isMove == false)
	{
		m_isMove = true;
		m_fPosY += 20;
	}
	if (m_isMove)
	{
		m_nMoveDelay++;
	}
	if (m_nMoveDelay >= 2)
	{
		m_nMoveDelay = 0;
		m_isMove = false;
	}

}

void cPlayer::Render()
{
	json js;
	ifstream LoadPlace;
	LoadPlace.open("SavePlace.json");
	js << LoadPlace;
	LoadPlace.close();
	if(js["Place"] != SLIST_TITLE)
	RectangleMake(g_hDC, m_rtPlayer);
}

void cPlayer::Release()
{
}
