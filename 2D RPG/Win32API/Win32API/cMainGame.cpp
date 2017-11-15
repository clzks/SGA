#include "stdafx.h"
#include "cMainGame.h"

//씬 헤더파일들 추가
#include "cTitleScene.h"
#include "cVillage1Scene.h"
#include "cVil1Dun1.h"
#include "cVil1Dun2.h"
#include "cVil1Shop.h"
#include "cVil1Forge.h"
#include "cLoadingScene.h"

cMainGame::cMainGame()
{
	m_pPlayer = new cPlayer;
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pPlayer);
}

void cMainGame::Setup()
{

	g_pSceneManager->AddScene(SLIST_TITLE, new cTitleScene); // 시작화면
	g_pSceneManager->AddScene(SLIST_VILLAGE1, new cVillage1Scene); // 마을1 전체
	g_pSceneManager->AddScene(SLIST_VIL1DUN1, new cVil1Dun1); // 마을1의 던전
	g_pSceneManager->AddScene(SLIST_VIL1DUN2, new cVil1Dun2); // 마을1의 던전2
	g_pSceneManager->AddScene(SLIST_VIL1FORGE, new cVil1Forge); // 마을1의 무기상점
	g_pSceneManager->AddScene(SLIST_VIL1SHOP, new cVil1Shop); // 마을1의 잡화상점
	g_pSceneManager->AddScene(SLIST_LOADING, new cLoadingScene); // 로딩화면

	// 처음 시작 씬 셋팅
	g_pSceneManager->ChangeScene(SLIST_TITLE);

	m_pPlayer->Setup();
}

void cMainGame::Update()
{
	cGameNode::Update();

	g_pSceneManager->Update();
	m_pPlayer->Update();
}

void cMainGame::Render()
{
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(g_hWnd, &ps);

	// 흰색으로 이미지를 칠한다.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);


	g_pSceneManager->Render();
	g_pTimeManager->Render();
	m_pPlayer->Render();
	m_pImgBackBuffer->Render(hdc);
	EndPaint(g_hWnd, &ps);


}

void cMainGame::Release()
{
	g_pKeyManager->ReleaseInstance();
	g_pFileData->ReleaseInstance();
	g_pPixelManager->ReleaseInstance();
	g_pTimeManager->ReleaseInstance();
	g_pIniData->ReleaseInstance();
	g_pImageManager->ReleaseAll();
	g_pImageManager->ReleaseInstance();
}
