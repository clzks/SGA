#pragma once
#include "cImage.h"

class cGameNode
{
protected:
	cImage*		m_pImgBackBuffer;

public:
	cGameNode();
	virtual ~cGameNode();

	virtual void Setup() PURE;
	virtual void Update();
	virtual void Render() PURE;
	virtual void Release() PURE;

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

