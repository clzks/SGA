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
	g_pImageManager->AddImage("main", "images/main.bmp", 1200, 1000);
	g_pImageManager->AddImage("newgame", "images/newgame.bmp", 413, 89, true,RGB(255,0,255));
	g_pImageManager->AddImage("loadgame", "images/loadgame.bmp", 398, 107, true, RGB(255, 0, 255));
	g_pImageManager->FindImage("main");
	g_pImageManager->FindImage("newgame");
	g_pImageManager->FindImage("loadgame");

	newgame = RectMake(400, 400, 413, 89);
	loadgame = RectMake(400, 600, 398, 107);
}

void cTitleScene::Update()
{

	if (PtInRect(&newgame, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
		g_pSceneManager->ChangeScene("Play");
	if (PtInRect(&loadgame, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
		g_pSceneManager->ChangeScene("Load");
	else if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);
}

void cTitleScene::Render()
{
	g_pImageManager->Render("main", g_hDC);
	if (PtInRect(&newgame, g_ptMouse))
		g_pImageManager->Render("newgame", g_hDC, 400, 400);
	else
		g_pImageManager->AlphaRender("newgame", g_hDC, 400, 400, 150);
	if (PtInRect(&loadgame, g_ptMouse))
		g_pImageManager->Render("loadgame", g_hDC, 400, 600);
	else
		g_pImageManager->AlphaRender("loadgame", g_hDC, 400, 600, 150);
}

void cTitleScene::Release()
{
}
