#pragma once
#include "cGameNode.h"

class cOmokScene : public cGameNode
{
private:
	RECT newgame;
	RECT gomain;
public:
	cOmokScene();
	virtual ~cOmokScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

