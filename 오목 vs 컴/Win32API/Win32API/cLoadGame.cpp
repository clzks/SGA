#include "stdafx.h"
#include "cLoadGame.h"


cLoadGame::cLoadGame()
{
}


cLoadGame::~cLoadGame()
{
}

void cLoadGame::Setup()
{
	LoadFile();
	g_pImageManager->FindImage("white");
	g_pImageManager->FindImage("pan");
	g_pImageManager->FindImage("black");
	g_pImageManager->FindImage("number");
	g_pImageManager->FindImage("turn");
	g_pImageManager->FindImage("rework");
	g_pImageManager->FindImage("giveup");
	g_pImageManager->FindImage("gomain");
	g_pImageManager->FindImage("save");

	rework = RectMake(1030, 380, 120, 45);
	giveup = RectMake(1030, 500, 120, 45);
	gomain = RectMake(1030, 620, 120, 45);
	save = RectMake(1030, 740, 120, 45);

	// 이부분만 로딩으로 바꾸면 댄다
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			newBox[x][y].PosX = 30 + x * 52;
			newBox[x][y].PosY = 30 + y * 52;
			newBox[x][y].isPlace = false;
			newBox[x][y].ColorType = none2;
			newBox[x][y].ClickBox = RectMakeCenter(newBox[x][y].PosX, newBox[x][y].PosY, 40, 40);
			newBox[x][y].turn = -1;
		}
	}
	m_nTurn = 0;
	m_isOmok = false;
	m_nTestOmok = 0;
	m_ntime = 30;
	m_ntimecount = 0;
	m_isDoubleTriple = false;
	reworkCool = 0;
	m_isrework = false;
}

void cLoadGame::Update()
{

#pragma region 돌 놓기 // 오목이 폴스일때, 쌍삼이 아닐때 놓는다 //
	if (m_isOmok == false && m_isDoubleTriple == false)
	{
		m_ntimecount++;
		if (m_ntimecount >= 60)
		{
			m_ntime--;
			m_ntimecount = 0;
		}
		if (m_ntime <= 0)
		{
			m_nTurn++;
			m_ntime = 30;
		}
		for (int y = 0; y < 19; y++)
		{
			for (int x = 0; x < 19; x++)
			{
				if (m_nTurn % 2 == 0)
				{
					if (PtInRect(&newBox[x][y].ClickBox, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON) && newBox[x][y].isPlace == false)
					{
						newBox[x][y].isPlace = true;
						newBox[x][y].ColorType = black2;
						m_nTurn++;
						newBox[x][y].turn = m_nTurn;
						m_ntime = 30;
					}
				}
				else if (m_nTurn % 2 == 1)
				{
					if (PtInRect(&newBox[x][y].ClickBox, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON) && newBox[x][y].isPlace == false)
					{
						newBox[x][y].isPlace = true;
						newBox[x][y].ColorType = white2;
						m_nTurn++;
						newBox[x][y].turn = m_nTurn;
						m_ntime = 30;
					}
				}
			}
		}
	}
#pragma endregion
#pragma region 무르기 && 기권
	if (PtInRect(&rework, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON) && m_nTurn >= 1)
	{
		for (int y = 0; y < 19; y++)
		{
			for (int x = 0; x < 19; x++)
			{
				if (newBox[x][y].turn == m_nTurn && m_isrework == false)
				{
					m_isrework = true;
					newBox[x][y].isPlace = false;
					newBox[x][y].ColorType = none2;
					m_nTurn--;
					m_ntime = 30;
				}
			}
		}
	}

	if (m_isrework == true)
	{
		reworkCool++;
		if (reworkCool >= 20)
		{
			reworkCool = 0;
			m_isrework = false;
		}

	}
	if (PtInRect(&giveup, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		m_isOmok = true;
	}
#pragma endregion
#pragma region 혼신의 오목검사
	for (int y = 0; y<19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			CheckHorizontalOmok(x, y, (ColorType2)newBox[x][y].ColorType);
			CheckVerticalOmok(x, y, (ColorType2)newBox[x][y].ColorType);
			CheckDiagonalOmok135(x, y, (ColorType2)newBox[x][y].ColorType);
			CheckDiagonalOmok45(x, y, (ColorType2)newBox[x][y].ColorType);
		}
	}
#pragma endregion
#pragma region 오목 or 기권
	if (m_isOmok == true)
	{
		if (m_nTurn % 2 == 1)
			g_pSceneManager->ChangeScene("OmokB");
		else
			g_pSceneManager->ChangeScene("OmokW");
	}
#pragma endregion
	if (PtInRect(&gomain, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		g_pSceneManager->ChangeScene("Title");
	}


}

void cLoadGame::Render()
{
	int a = m_ntime % 10; // 남은시간 1의자리
	int b = m_ntime / 10; // 남은시간 10의 자리
	g_pImageManager->Render("pan", g_hDC);
	g_pImageManager->Render("turn", g_hDC, 1010, 95);

	if (PtInRect(&rework, g_ptMouse))
	{
		g_pImageManager->Render("rework", g_hDC, 1030, 380);
	}
	else
	{
		g_pImageManager->AlphaRender("rework", g_hDC, 1030, 380, 100);
	}
	if (PtInRect(&giveup, g_ptMouse))
	{
		g_pImageManager->Render("giveup", g_hDC, 1030, 500);
	}
	else
	{
		g_pImageManager->AlphaRender("giveup", g_hDC, 1030, 500, 128);
	}
	if (PtInRect(&gomain, g_ptMouse))
	{
		g_pImageManager->Render("gomain", g_hDC, 1030, 620);
	}
	else
	{
		g_pImageManager->AlphaRender("gomain", g_hDC, 1030, 620, 128);
	}
	if (PtInRect(&save, g_ptMouse))
	{
		g_pImageManager->Render("save", g_hDC, 1030, 740);
	}
	else
	{
		g_pImageManager->AlphaRender("save", g_hDC, 1030, 740, 128);
	}

	if (m_nTurn % 2 == 0)
	{
		g_pImageManager->Render("black", g_hDC, 1030, 170);
		g_pImageManager->FrameSizeRender("number", g_hDC, 1090, 177, 2, 2, b, 0);
		g_pImageManager->FrameSizeRender("number", g_hDC, 1114, 177, 2, 2, a, 0);
		g_pImageManager->AlphaRender("white", g_hDC, 1030, 240, 64);

	}
	else if (m_nTurn % 2 == 1)
	{
		g_pImageManager->AlphaRender("black", g_hDC, 1030, 170, 64);
		g_pImageManager->Render("white", g_hDC, 1030, 240);
		g_pImageManager->FrameSizeRender("number", g_hDC, 1090, 247, 2, 2, b, 0);
		g_pImageManager->FrameSizeRender("number", g_hDC, 1114, 247, 2, 2, a, 0);
	}



	if (m_isOmok == false)
	{
		for (int y = 0; y < 19; y++)
		{
			for (int x = 0; x < 19; x++)
			{
				if (PtInRect(&newBox[x][y].ClickBox, g_ptMouse))
				{
					if (m_nTurn % 2 == 0)g_pImageManager->AlphaRender("black", g_hDC, newBox[x][y].PosX - 26, newBox[x][y].PosY - 26, 128);
					if (m_nTurn % 2 == 1)g_pImageManager->AlphaRender("white", g_hDC, newBox[x][y].PosX - 26, newBox[x][y].PosY - 26, 128);
				}

				if (newBox[x][y].isPlace && newBox[x][y].ColorType == black2)
				{
					g_pImageManager->Render("black", g_hDC, newBox[x][y].PosX - 26, newBox[x][y].PosY - 26);
				}
				else if (newBox[x][y].isPlace && newBox[x][y].ColorType == white2)
				{
					g_pImageManager->Render("white", g_hDC, newBox[x][y].PosX - 26, newBox[x][y].PosY - 26);
				}
			}
		}
	}
	char str[128];
	sprintf(str, "오목 : %d", m_isOmok);
	TextOut(g_hDC, WINSIZEX - 70, 0, str, strlen(str));
	sprintf(str, "횟수 : %d", m_nTurn);
	TextOut(g_hDC, WINSIZEX - 70, 20, str, strlen(str));
}

void cLoadGame::Release()
{

}

void cLoadGame::LoadFile()
{
	g_pImageManager->AddImage("white", "images/white.bmp", 50, 50, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("black", "images/black.bmp", 50, 50, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("pan", "images/Pan.bmp", 1200, 1000);
	g_pImageManager->AddImage("turn", "images/turn.bmp", 168, 55, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("number", "images/number.bmp", 120, 17, 10, 1, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("rework", "images/rework.bmp", 120, 45, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("giveup", "images/giveup.bmp", 120, 45, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("gomain", "images/gomain.bmp", 120, 45, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("save", "images/save.bmp", 120, 45, true, RGB(255, 0, 255));
}

bool cLoadGame::CheckHorizontalOmok(int x, int y, ColorType2 color)
{
	if (x <= 14 && color != 2)
	{
		if (x == 0)
		{
			if (newBox[x][y].ColorType == color && newBox[x + 5][y].ColorType != color && newBox[x + 1][y].ColorType == color &&
				newBox[x + 2][y].ColorType == color && newBox[x + 3][y].ColorType == color && newBox[x + 4][y].ColorType == color)
				m_isOmok = true;
		}
		else if (x >= 1 && x <= 13)
		{
			if (newBox[x][y].ColorType == color && newBox[x + 5][y].ColorType != color && newBox[x - 1][y].ColorType != color && newBox[x + 1][y].ColorType == color &&
				newBox[x + 2][y].ColorType == color && newBox[x + 3][y].ColorType == color && newBox[x + 4][y].ColorType == color)
				m_isOmok = true;
		}
		else if (x == 14)
		{
			if (newBox[x][y].ColorType == color && newBox[x - 1][y].ColorType != color && newBox[x + 1][y].ColorType == color &&
				newBox[x + 2][y].ColorType == color && newBox[x + 3][y].ColorType == color && newBox[x + 4][y].ColorType == color)
				m_isOmok = true;
		}
	}
	return m_isOmok;
}

bool cLoadGame::CheckVerticalOmok(int x, int y, ColorType2 color)
{
	if (y <= 14 && color != 2)
	{
		if (y == 0)
		{
			if (newBox[x][y].ColorType == color && newBox[x][y + 5].ColorType != color && newBox[x][y + 1].ColorType == color &&
				newBox[x][y + 2].ColorType == color && newBox[x][y + 3].ColorType == color && newBox[x][y + 4].ColorType == color)
				m_isOmok = true;
		}
		else if (y >= 1 && y <= 13)
		{
			if (newBox[x][y].ColorType == color && newBox[x][y + 5].ColorType != color&& newBox[x][y - 1].ColorType != color && newBox[x][y + 1].ColorType == color &&
				newBox[x][y + 2].ColorType == color && newBox[x][y + 3].ColorType == color && newBox[x][y + 4].ColorType == color)
				m_isOmok = true;
		}
		else if (y == 14)
		{
			if (newBox[x][y].ColorType == color && newBox[x][y - 1].ColorType != color && newBox[x][y + 1].ColorType == color &&
				newBox[x][y + 2].ColorType == color && newBox[x][y + 3].ColorType == color && newBox[x][y + 4].ColorType == color)
				m_isOmok = true;
		}
	}
	return m_isOmok;
}

bool cLoadGame::CheckDiagonalOmok45(int x, int y, ColorType2 color)
{
	if (x >= 4 && y <= 14 && color != 2)
	{
		if (x == 18 && y <= 13)
		{
			if (newBox[x][y].ColorType == color && newBox[x - 1][y + 1].ColorType == color && newBox[x - 2][y + 2].ColorType == color &&newBox[x - 3][y + 3].ColorType == color &&
				newBox[x - 4][y + 4].ColorType == color &&newBox[x - 5][y + 5].ColorType != color)
				m_isOmok = true;
		}
		else if (x >= 5 && y == 0)
		{
			if (newBox[x][y].ColorType == color && newBox[x - 1][y + 1].ColorType == color && newBox[x - 2][y + 2].ColorType == color &&newBox[x - 3][y + 3].ColorType == color &&
				newBox[x - 4][y + 4].ColorType == color &&newBox[x - 5][y + 5].ColorType != color)
				m_isOmok = true;
		}
		else if (x == 4 && y == 0)
		{
			if (newBox[x][y].ColorType == color && newBox[x - 1][y + 1].ColorType == color && newBox[x - 2][y + 2].ColorType == color &&newBox[x - 3][y + 3].ColorType == color &&
				newBox[x - 4][y + 4].ColorType == color)
				m_isOmok = true;
		}
		else if (x == 18 && y == 14)
		{
			if (newBox[x][y].ColorType == color && newBox[x - 1][y + 1].ColorType == color && newBox[x - 2][y + 2].ColorType == color &&newBox[x - 3][y + 3].ColorType == color &&
				newBox[x - 4][y + 4].ColorType == color)
				m_isOmok = true;
		}
		else if (y >= 1 && y <= 14 && x == 4)
		{
			if (newBox[x][y].ColorType == color && newBox[x - 1][y + 1].ColorType == color && newBox[x - 2][y + 2].ColorType == color &&newBox[x - 3][y + 3].ColorType == color &&
				newBox[x - 4][y + 4].ColorType == color && newBox[x + 1][y - 1].ColorType != color)
				m_isOmok = true;
		}
		else if (y == 14 && x <= 17 && x >= 4)
		{
			if (newBox[x][y].ColorType == color && newBox[x - 1][y + 1].ColorType == color && newBox[x - 2][y + 2].ColorType == color &&newBox[x - 3][y + 3].ColorType == color &&
				newBox[x - 4][y + 4].ColorType == color && newBox[x + 1][y - 1].ColorType != color)
				m_isOmok = true;
		}

		else if (x >= 5 && x <= 17 && y >= 1 && y <= 13)
		{
			if (newBox[x][y].ColorType == color && newBox[x - 1][y + 1].ColorType == color && newBox[x - 2][y + 2].ColorType == color &&newBox[x - 3][y + 3].ColorType == color &&
				newBox[x - 4][y + 4].ColorType == color && newBox[x + 1][y - 1].ColorType != color  &&newBox[x - 5][y + 5].ColorType != color)
				m_isOmok = true;
		}
	}
	return m_isOmok;
}

bool cLoadGame::CheckDiagonalOmok135(int x, int y, ColorType2 color)
{
	if (x <= 14 && y <= 14 && color != 2)
	{
		if (x == 0 && y <= 13)
		{
			if (newBox[x][y].ColorType == color && newBox[x + 1][y + 1].ColorType == color && newBox[x + 2][y + 2].ColorType == color &&newBox[x + 3][y + 3].ColorType == color &&
				newBox[x + 4][y + 4].ColorType == color &&newBox[x + 5][y + 5].ColorType != color)
				m_isOmok = true;
		}
		else if (x <= 14 && y == 0)
		{
			if (newBox[x][y].ColorType == color && newBox[x + 1][y + 1].ColorType == color && newBox[x + 2][y + 2].ColorType == color &&newBox[x + 3][y + 3].ColorType == color &&
				newBox[x + 4][y + 4].ColorType == color &&newBox[x + 5][y + 5].ColorType != color)
				m_isOmok = true;
		}
		else if (x == 0 && y == 14)
		{
			if (newBox[x][y].ColorType == color && newBox[x + 1][y + 1].ColorType == color && newBox[x + 2][y + 2].ColorType == color &&newBox[x + 3][y + 3].ColorType == color &&
				newBox[x + 4][y + 4].ColorType == color)
				m_isOmok = true;
		}
		else if (x == 14 && y == 0)
		{
			if (newBox[x][y].ColorType == color && newBox[x + 1][y + 1].ColorType == color && newBox[x + 2][y + 2].ColorType == color &&newBox[x + 3][y + 3].ColorType == color &&
				newBox[x + 4][y + 4].ColorType == color)
				m_isOmok = true;
		}
		else if (x >= 1 && x <= 14 && y == 14)
		{
			if (newBox[x][y].ColorType == color && newBox[x + 1][y + 1].ColorType == color && newBox[x + 2][y + 2].ColorType == color &&newBox[x + 3][y + 3].ColorType == color &&
				newBox[x + 4][y + 4].ColorType == color && newBox[x - 1][y - 1].ColorType != color)
				m_isOmok = true;
		}
		else if (x == 14 && y >= 1 && y <= 14)
		{
			if (newBox[x][y].ColorType == color && newBox[x + 1][y + 1].ColorType == color && newBox[x + 2][y + 2].ColorType == color &&newBox[x + 3][y + 3].ColorType == color &&
				newBox[x + 4][y + 4].ColorType == color && newBox[x - 1][y - 1].ColorType != color)
				m_isOmok = true;
		}

		else if (x <= 13 && x >= 1 && y >= 1 && y <= 13)
		{
			if (newBox[x][y].ColorType == color && newBox[x + 1][y + 1].ColorType == color && newBox[x + 2][y + 2].ColorType == color &&newBox[x + 3][y + 3].ColorType == color &&
				newBox[x + 4][y + 4].ColorType == color && newBox[x - 1][y - 1].ColorType != color &&  newBox[x + 5][y + 5].ColorType != color)
				m_isOmok = true;
		}
	}
	return m_isOmok;
}

bool cLoadGame::CheckDoubleTriple(int x, int y, ColorType2 color)
{

	return m_isDoubleTriple;
}