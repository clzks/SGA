#include "stdafx.h"
#include "cMainGame.h"

//씬 헤더파일들 추가
#include "cTitleScene.h"
#include "cPlayScene.h"

cMainGame::cMainGame()
{
    
}

cMainGame::~cMainGame()
{
	 
}

void cMainGame::Setup()
{
	g_pSceneManager->AddScene(SLIST_TITLE, new cTitleScene); // 시작화면
	g_pSceneManager->AddScene(SLIST_PLAY, new cPlayScene);

	// 처음 시작 씬 셋팅
	g_pSceneManager->ChangeScene(SLIST_TITLE);
}

void cMainGame::Update()
{
	cGameNode::Update();

	g_pSceneManager->Update();
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
