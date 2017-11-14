#pragma once
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
// timeGetTime 함수를 사용하기 위한 라이브러리 추가
// 윈도우가 시작되고 난 후 시간을 리턴시켜 준다.

class cTimer
{
private:
	bool			m_isHardware;		// 고성능 타이머를 지원하냐?
	float			m_fTimeScale;		// 시간 경과량
	float			m_fTimeElapsed;		// 한프레임 당 경과 시간 (1 / 60)
	__int64			m_nCurrTime;		// 현재 시간
	__int64			m_nLastTime;		// 마지막 시간
	__int64			m_nPeriodFrequency;	// 시간 주기

	unsigned int	m_nFrameRate;		// FPS (Frame Per Second)
	unsigned int	m_nFPSFrameCount;	// FPS 카운터
	float			m_fFPSTimeElapsed;	// FPS 마지막 시간과 현재 시간 경과량
	float			m_fWorldTime;		// 전체 경과 시간

public:
	cTimer();
	~cTimer();

	// 현재 시간 계산
	void Tick(float lockFPS = 0.0f);
	// 현재 FPS 가져오기
	unsigned int GetFPS(char* str = NULL) const;
	// 한 프레임당 경과 시간 (1 / 60)
	float GetElapsedTime() const { return m_fFPSTimeElapsed; }
	// 전체 경과 시간 가져오기
	float GetWorldTime() const { return m_fWorldTime; }
};

