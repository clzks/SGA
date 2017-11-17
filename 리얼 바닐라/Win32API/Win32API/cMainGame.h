#pragma once
#include "cGameNode.h"

class cMainGame : public cGameNode
{
public:
	cMainGame();
	virtual ~cMainGame();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};