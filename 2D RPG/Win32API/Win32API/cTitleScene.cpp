#include "stdafx.h"
#include "cTitleScene.h"


cTitleScene::cTitleScene()
{
}

cTitleScene::~cTitleScene()
{
}

void cTitleScene::Setup()
{
}

void cTitleScene::Update()
{
	//if (g_pKeyManager->isOnceKeyDown('1'))
	//{
	//	g_pSceneManager->SetNextScene(SLIST_DUNGEON1);
	//	g_pSceneManager->ChangeScene(SLIST_LOADING);
	//}
	json js;
	js["Place"] = SLIST_TITLE;
	ofstream ofs;
	ofs.open("SavePlace.json");
	ofs << js;
	ofs.close();
	
	if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		js["Place"] = SLIST_VILLAGE1;
		ofs.open("SavePlace.json");
		ofs << js;
		ofs.close();
		g_pSceneManager->ChangeScene(SLIST_VILLAGE1);
	}
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);
}

void cTitleScene::Render()
{
	TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
}

void cTitleScene::Release()
{
}
