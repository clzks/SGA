#pragma once
#include "cGameNode.h"
class cVil1Dun1 : public cGameNode
{ 
private:

public:
	cVil1Dun1();
	virtual ~cVil1Dun1();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

