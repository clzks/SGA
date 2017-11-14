#include "stdafx.h"
#include "cMainGame.h"

//�� ������ϵ� �߰�
#include "cTitleScene.h"
#include "cPlayScene.h"
#include "cOmokScene.h"
#include "cOmokWiteScene.h"
#include "cLoadGame.h"
cMainGame::cMainGame()
{
    
}

cMainGame::~cMainGame()
{
	 
}

void cMainGame::Setup()
{
	// �� �߰�
	g_pSceneManager->AddScene("Title", new cTitleScene);
	g_pSceneManager->AddScene("Play", new cPlayScene);
	g_pSceneManager->AddScene("OmokB", new cOmokScene);
	g_pSceneManager->AddScene("OmokW", new cOmokWiteScene);
	g_pSceneManager->AddScene("Load", new cLoadGame);

	// ó�� ���� �� ����
	g_pSceneManager->ChangeScene("Title");
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

	// ������� �̹����� ĥ�Ѵ�.
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
