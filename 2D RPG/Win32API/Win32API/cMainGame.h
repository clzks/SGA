#pragma once
#include "cGameNode.h"
#include "cPlayer.h"
class cMainGame : public cGameNode
{
private:
	cPlayer*			m_pPlayer;


public:
	cMainGame();
	virtual ~cMainGame();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};