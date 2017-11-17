#pragma once
class cProgressBar
{
private:
	cImage*		m_imgBack;
	cImage*		m_imgFront;

	RECT		m_rt;			// 그려질 위치 렉트
	int			m_nPosX;		// 센터 x 위치
	int			m_nPosY;		// 센터 y 위치
	int			m_nWidth;		// 가로 길이
	int			m_nHeight;		// 세로 길이
	int			m_nCurrWidth;	// 현재 체력바 길이

public:
	cProgressBar(string strBack, string strFront, int width, int heigth);
	~cProgressBar();

	void Update();
	void Render();

	void SetGauge(float currGauge, float maxGauge);
	void SetPosX(int x) { m_nPosX = x; }
	int GetPosX() { return m_nPosX; }
	void SetPosY(int y) { m_nPosY = y; }
	int GetPosY() { return m_nPosY; }

	RECT GetRect() { return m_rt; }
};

