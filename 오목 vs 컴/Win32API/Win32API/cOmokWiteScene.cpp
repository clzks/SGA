#include "stdafx.h"
#include "cOmokWiteScene.h"


cOmokWiteScene::cOmokWiteScene()
{
}


cOmokWiteScene::~cOmokWiteScene()
{
}

void cOmokWiteScene::Setup()
{
	g_pImageManager->AddImage("white", "images/white.bmp", 150, 150, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("victory", "images/victory.bmp", 800, 200, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("newgame", "images/newgame.bmp", 400, 100, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("gomain", "images/gomain.bmp", 400, 100, true, RGB(255, 0, 255));
	g_pImageManager->FindImage("newgame");
	g_pImageManager->FindImage("gomain");
	g_pImageManager->FindImage("white");
	g_pImageManager->FindImage("victory");

	newgame = RectMake(400, 500, 400, 100);
	gomain = RectMake(400, 700, 400, 100);
}

void cOmokWiteScene::Update()
{
	if (PtInRect(&newgame, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		g_pSceneManager->ChangeScene("Play");
	}
	if (PtInRect(&gomain, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		g_pSceneManager->ChangeScene("Title");
	}
}

void cOmokWiteScene::Render()
{
	g_pImageManager->Render("white", g_hDC, 200, 300);
	g_pImageManager->Render("victory", g_hDC, 400, 250);

	if (PtInRect(&newgame, g_ptMouse))
	{
		g_pImageManager->Render("newgame", g_hDC, 400, 500);
	}
	else
		g_pImageManager->AlphaRender("newgame", g_hDC, 400, 500, 150);
	if (PtInRect(&gomain, g_ptMouse))
	{
		g_pImageManager->Render("gomain", g_hDC, 400, 700);
	}
	else
		g_pImageManager->AlphaRender("gomain", g_hDC, 400, 700, 150);
}

void cOmokWiteScene::Release()
{
}
