#include "stdafx.h"
#include "cSceneManager.h"
#include "cGameNode.h"

// 스태틱 변수 초기화
cGameNode* cSceneManager::m_pCurrScene = NULL;

void cSceneManager::Update()
{
	if (m_pCurrScene)
		m_pCurrScene->Update();
}

void cSceneManager::Render()
{
	if (m_pCurrScene)
		m_pCurrScene->Render();
}

cGameNode* cSceneManager::AddScene(string sceneName, cGameNode* scene)
{
	// 씬을 씬 목록(맵)에 추가 한다.
	if (scene) m_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

void cSceneManager::ChangeScene(string sceneName)
{
	// 씬 목록 맵 이터레이터
	miSceneList find = m_mSceneList.find(sceneName);

	// 찾는 씬이 없는 경우
	if (find == m_mSceneList.end())
		assert(false && "찾는 씬이 없음.");

	// 찾는 씬이 현재씬과 같은 경우
	if (find->second == m_pCurrScene)
		assert(false && "찾는 씬이 현재 씬과 같음");

	// 여기까지 왔다면 씬 전환에 문제가 없음
	if (m_pCurrScene != NULL)
	{ // 현재 씬의 모든 것을 해제
		m_pCurrScene->Release();
		g_pImageManager->ReleaseAll();
	}

	// 새로운 씬으로 교체 및 셋업
	m_pCurrScene = find->second;
	m_pCurrScene->Setup();
}

void cSceneManager::ReleaseAll()
{
	// 모든 씬을 반복자를 통해서 돌면서 전부 해제 한다.
	miSceneList iter = m_mSceneList.begin();
	for (; iter != m_mSceneList.end();)
	{
		// 삭제
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = m_mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	m_mSceneList.clear();
}
