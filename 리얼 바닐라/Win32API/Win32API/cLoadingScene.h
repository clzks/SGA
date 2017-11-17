#pragma once
#include "cGameNode.h"
#include "cLoading.h"


class cLoadingScene : public cGameNode
{
private:
	cLoading*		m_pLoading;

public:
	cLoadingScene() {};
	virtual ~cLoadingScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void LoadingImage();
	void LoadingSound();
};

