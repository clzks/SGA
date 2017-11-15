#pragma once
#include "cGameNode.h"

class UIScene : public cGameNode
{
public:
	UIScene();
	virtual ~UIScene();
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

