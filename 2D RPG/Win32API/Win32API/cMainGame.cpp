#include "stdafx.h"
#include "cMainGame.h"

//�� ������ϵ� �߰�
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

	g_pSceneManager->AddScene(SLIST_TITLE, new cTitleScene); // ����ȭ��
	g_pSceneManager->AddScene(SLIST_VILLAGE1, new cVillage1Scene); // ����1 ��ü
	g_pSceneManager->AddScene(SLIST_VIL1DUN1, new cVil1Dun1); // ����1�� ����
	g_pSceneManager->AddScene(SLIST_VIL1DUN2, new cVil1Dun2); // ����1�� ����2
	g_pSceneManager->AddScene(SLIST_VIL1FORGE, new cVil1Forge); // ����1�� �������
	g_pSceneManager->AddScene(SLIST_VIL1SHOP, new cVil1Shop); // ����1�� ��ȭ����
	g_pSceneManager->AddScene(SLIST_LOADING, new cLoadingScene); // �ε�ȭ��

	// ó�� ���� �� ����
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

	// ������� �̹����� ĥ�Ѵ�.
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
