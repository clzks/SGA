#include "stdafx.h"
#include "cTimer.h"


cTimer::cTimer()
{
	// 고성능 타이머 지원 여부 체크
	// 마이크로 세컨드 (1 / 1,000,000)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_nPeriodFrequency))
	{
		m_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);

		// 초당 시간 계산 범위
		m_fTimeScale = 1.0f / m_nPeriodFrequency;
	}
	else
	{
		m_isHardware = false;
		m_nLastTime = timeGetTime();
		m_fTimeScale = 1.0f / 1000.0f; // 밀리세컨드 (1 / 1,000)
	}

	// 타이머 관련 변수들 초기화
	m_nFrameRate = 0;
	m_nFPSFrameCount = 0;
	m_fFPSTimeElapsed = 0.0f;
	m_fWorldTime = 0.0f;
}


cTimer::~cTimer()
{
}

void cTimer::Tick(float lockFPS)
{
	// 고성능 타이머 확인
	if (m_isHardware)
	{
		// 마이크로세컨드 단위로 계산한다.
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrTime);
	}
	else
	{
		m_nCurrTime = timeGetTime();
	}

	// 마지막 시간으로 부터 현재 시간까지의 경과량
	m_fTimeElapsed = (m_nCurrTime - m_nLastTime) * m_fTimeScale;

	if (lockFPS > 0.0f)
	{
		while (m_fTimeElapsed < (1.0f / lockFPS))
		{
			if (m_isHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrTime);
			else
				m_nCurrTime = timeGetTime();

			m_fTimeElapsed = (m_nCurrTime - m_nLastTime) * m_fTimeScale;
		}
	}

	m_nLastTime = m_nCurrTime;
	++m_nFPSFrameCount;
	m_fFPSTimeElapsed += m_fTimeElapsed;
	m_fWorldTime += m_fTimeElapsed;

	// 프레임 카운팅 시작후 1초가 넘어가면
	if (m_fFPSTimeElapsed > 1.0f)
	{
		m_nFrameRate = m_nFPSFrameCount;
		m_nFPSFrameCount = 0;
		m_fFPSTimeElapsed = 0.0f;
	}
}

unsigned int cTimer::GetFPS(char* str) const
{
	return m_nFrameRate;
}
