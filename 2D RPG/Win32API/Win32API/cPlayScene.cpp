#include "stdafx.h"
#include "cPlayScene.h"


cPlayScene::cPlayScene()
{
}


cPlayScene::~cPlayScene()
{
}

void cPlayScene::Setup()
{
	//m_pMap->Update();
	//m_pPlayer->Update();
}

void cPlayScene::Update()
{
	 
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->ChangeScene(SLIST_TITLE);
	}
}

void cPlayScene::Render()
{
	
}

void cPlayScene::Release()
{
	//SAFE_DELETE(m_pPlayer);
	//SAFE_DELETE(m_pMap);
}
