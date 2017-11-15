#pragma once
#include "cGameNode.h"
class cVil1Shop : public cGameNode
{
private:


public:
	cVil1Shop();
	virtual ~cVil1Shop();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

