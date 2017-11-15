#include "stdafx.h"
#include "cDungeon1.h"


void cDungeon1::Setup()
{
}

void cDungeon1::Update()
{
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown('2'))
	{
		g_pSceneManager->SetNextScene(SLIST_DUNGEON2);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown('3'))
	{
		g_pSceneManager->SetNextScene(SLIST_DUNGEON3);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);
}

void cDungeon1::Render()
{
	TextOut(g_hDC, 100, 100, "1¹ø¾À", strlen("1¹ø¾À"));
}

void cDungeon1::Release()
{
}
