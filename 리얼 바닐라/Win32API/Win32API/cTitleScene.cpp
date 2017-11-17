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
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		g_pSceneManager->ChangeScene(SLIST_PLAY);
	}

	//if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	//	PostQuitMessage(0);
}

void cTitleScene::Render()
{
	TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
}

void cTitleScene::Release()
{
}
