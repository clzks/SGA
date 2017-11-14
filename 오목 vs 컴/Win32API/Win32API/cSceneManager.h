#pragma once
#include "cSingletonBase.h"

#define g_pSceneManager cSceneManager::GetInstance()

class cGameNode;

class cSceneManager : public cSingletonBase<cSceneManager>
{
private:
	typedef map<string, cGameNode*> mSceneList;
	typedef map<string, cGameNode*>::iterator miSceneList;


private:
	static cGameNode*	m_pCurrScene;		// ÇöÀç ¾À
	mSceneList			m_mSceneList;		// ÀüÃ¼ ¾À ¸ñ·Ï

public:
	void Update();
	void Render();

	// ¾À Ãß°¡
	cGameNode* AddScene(string sceneName, cGameNode* scene);
	// ¾À º¯°æ
	void ChangeScene(string sceneName);
	// ¸ðµç ¾À »èÁ¦
	void ReleaseAll();
};