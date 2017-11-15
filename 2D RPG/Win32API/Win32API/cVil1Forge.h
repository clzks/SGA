#pragma once
#include "cGameNode.h"

class cVil1Forge : public cGameNode 
{
private:

public:
	cVil1Forge();
	virtual ~cVil1Forge();
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

