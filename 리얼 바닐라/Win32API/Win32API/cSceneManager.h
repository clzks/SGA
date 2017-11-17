#pragma once
#include "cSingletonBase.h"

#define g_pSceneManager cSceneManager::GetInstance()

class cGameNode;

enum SCENE_LIST
{
	SLIST_LOADING,
	SLIST_TITLE,
	SLIST_PLAY,
	SLIST_END
};

class cSceneManager : public cSingletonBase<cSceneManager>
{
private:
	typedef map<SCENE_LIST, cGameNode*> mSceneList;
	typedef map<SCENE_LIST, cGameNode*>::iterator miSceneList;

private:
	static cGameNode*	m_pCurrScene;		// ÇöÀç ¾À
	static SCENE_LIST	m_eNextScene;		// ´ÙÀ½ ¾À (Å° °ª)
	mSceneList			m_mSceneList;		// ÀüÃ¼ ¾À ¸ñ·Ï

public:
	void Update();
	void Render();

	// ¾À Ãß°¡
	cGameNode* AddScene(SCENE_LIST sceneName, cGameNode* scene);
	// ´ÙÀ½ ¾À
	void SetNextScene(SCENE_LIST next) { m_eNextScene = next; }
	SCENE_LIST GetNextScene() { return m_eNextScene; }
	// ¾À º¯°æ
	void ChangeScene(SCENE_LIST sceneName);
	// ¸ðµç ¾À »èÁ¦
	void ReleaseAll();
};