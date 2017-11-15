#include "stdafx.h"
#include "cLoadingScene.h"


void cLoadingScene::Setup()
{
	m_pLoading = new cLoading;
	m_pLoading->Setup();

	LoadingImage();
	LoadingSound();
}

void cLoadingScene::Update()
{
	// m_pLoading->LoadingDone() : ���� ���� ���ҽ� �ε��� ���α׷����� ������Ʈ
	if (m_pLoading->LoadingDone())
	{
		g_pSceneManager->ChangeScene(g_pSceneManager->GetNextScene());
	}
}

void cLoadingScene::Render()
{
	m_pLoading->Render();
}

void cLoadingScene::Release()
{
	SAFE_DELETE(m_pLoading);
}

void cLoadingScene::LoadingImage()
{
	char szBuf[32];
	char* str;

	/* ==== ���ҽ� ���� ===== */
	for (int i = 100; i < 600; ++i)
	{
		str = itoa(i, szBuf, 10);
		g_pImageManager->ReleaseImage(str);
	}
	/* ====================== */

	// ���� ��ü���� �ʿ��� ���ҽ��� Ÿ��Ʋ �� �ε����� ���� �ε��Ѵ�.
	if (g_pSceneManager->GetNextScene() == SLIST_TITLE)
	{
		for (int i = 0; i < 100; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_VILLAGE1)
	{
		for (int i = 100; i < 200; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_VIL1DUN1)
	{
		for (int i = 200; i < 300; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_VIL1DUN2)
	{
		for (int i = 300; i < 400; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_VIL1FORGE)
	{
		for (int i = 400; i < 500; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_VIL1SHOP)
	{
		for (int i = 500; i < 600; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
}

void cLoadingScene::LoadingSound()
{
}