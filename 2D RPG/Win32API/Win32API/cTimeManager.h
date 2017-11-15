#pragma once
#include "cSingletonBase.h"
#include "cTimer.h"

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager : public cSingletonBase<cTimeManager>
{
private:
	cTimer*		m_pTimer;

public:
	cTimeManager();
	~cTimeManager();

	void Update(float lock);
	void Render();

	float GetElapsedTime() const { return m_pTimer->GetElapsedTime(); }
	float GetWorldTime() const { return m_pTimer->GetWorldTime(); }
	float GetDeltaTime() const { return 60.0f / m_pTimer->GetFPS(); }
};

