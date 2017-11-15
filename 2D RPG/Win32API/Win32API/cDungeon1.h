#pragma once
#include "cGameNode.h"
class cDungeon1 : public cGameNode
{
public:
	cDungeon1() {};
	virtual ~cDungeon1() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

