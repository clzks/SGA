#include "stdafx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager()
{
	m_pTimer = new cTimer;
}


cTimeManager::~cTimeManager()
{
	SAFE_DELETE(m_pTimer);
}

void cTimeManager::Update(float lock)
{
	if (m_pTimer)
		m_pTimer->Tick(lock);
}

void cTimeManager::Render()
{
	char str[128];
	string strFrame;

	// 글자 배경 모드
	SetBkMode(g_hDC, TRANSPARENT);
	// 글자 색상
	SetTextColor(g_hDC, RGB(0, 0, 255));
	// 텍스트 정렬
	SetTextAlign(g_hDC, TA_LEFT);

#ifdef _DEBUG
	if (m_pTimer)
	{
		// FPS
		sprintf(str, "FPS : %d", m_pTimer->GetFPS());
		TextOut(g_hDC, 10, 10, str, strlen(str));
		// WorldTime
		sprintf(str, "WorldTime : %f", m_pTimer->GetWorldTime());
		TextOut(g_hDC, 10, 30, str, strlen(str));
		// ElapsedTime
		sprintf(str, "ElapsedTime : %f", m_pTimer->GetElapsedTime());
		TextOut(g_hDC, 10, 50, str, strlen(str));
	}
#else
	if (!m_pTimer)
	{
		// FPS
		sprintf(str, "FPS : %d", m_pTimer->GetFPS());
		TextOut(g_hDC, 0, 0, str, strlen(str));
	}
#endif
}
