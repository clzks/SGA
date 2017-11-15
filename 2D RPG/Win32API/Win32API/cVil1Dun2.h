#pragma once
#include "cGameNode.h"

class cVil1Dun2 : public cGameNode
{
private:

public:
	cVil1Dun2();
	virtual ~cVil1Dun2();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

