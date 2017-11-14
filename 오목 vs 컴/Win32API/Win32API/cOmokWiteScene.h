#pragma once
#include "cGameNode.h"


class cOmokWiteScene : public cGameNode
{
private:
	RECT newgame;
	RECT gomain;
public:
	cOmokWiteScene();
	~cOmokWiteScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

