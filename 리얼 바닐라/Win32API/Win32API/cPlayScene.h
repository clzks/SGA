#pragma once
#include "cGameNode.h"

class cPlayScene : public cGameNode
{
private:
	//cMap*			m_pMap;
	//cPlayer*		m_pPlayer;




public:
	cPlayScene();
	virtual ~cPlayScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

