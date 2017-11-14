#include "stdafx.h"
#include "cPlayScene.h"


cPlayScene::cPlayScene()
{
	

}


cPlayScene::~cPlayScene()
{

}

void cPlayScene::Setup()
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
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			newBox[x][y].PosX = 30 + x * 52;
			newBox[x][y].PosY = 30 + y * 52;
			newBox[x][y].isPlace = false;
			newBox[x][y].ColorType = none;
			newBox[x][y].ClickBox = RectMakeCenter(newBox[x][y].PosX, newBox[x][y].PosY, 40, 40);
			newBox[x][y].turn = -1;
			newBox[x][y].Weight = 0;
		}
	}
	newBox[9][9].Weight = 100;
	m_nTurn = 0;
	m_isOmok = false;
	m_nTestOmok = 0;
	m_ntime = 10;
	m_ntimecount = 0;
	m_isDoubleTriple = false;
	reworkCool = 0;
	m_isrework = false;
	turnSetup = true;
	OmokCount = 0;
}

void cPlayScene::Update()
{
	if (turnSetup == false)
	{
		for (int y = 0; y < 19; y++)
		{
			for (int x = 0; x < 19; x++)
			{
				newBox[x][y].Weight = 0;
			}
		}
		turnSetup = true;
		for (int y = 0; y < 19; y++)
		{
			for (int x = 0; x < 19; x++)
			{
				CheckWeight(x, y);
			}
		}
	}

	

#pragma region 돌 놓기 // 오목이 폴스일때 놓는다 //
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
			m_ntime = 10;
			turnSetup = false;

		}
		for (int y = 0; y < 19; y++)
		{
			
			for (int x = 0; x < 19; x++)
			{
				if (m_ntime <= 10)
				{
					newBox[x][y].Weight++;
				}

				if (m_nTurn % 2 == 0) // 컴퓨터가 둚
				{
					if (newBox[x][y].isPlace == false && m_ntime <= 9  && newBox[x][y].Weight >= 120)
					{
						newBox[x][y].isPlace = true;
						newBox[x][y].ColorType = black;
						m_nTurn++;
						newBox[x][y].turn = m_nTurn;
						m_ntime = 10;
						turnSetup = false;
					}
					//}
				}
				else if (m_nTurn % 2 == 1)
				{
					if (PtInRect(&newBox[x][y].ClickBox, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON) && newBox[x][y].isPlace == false)
					{
						newBox[x][y].isPlace = true;
						newBox[x][y].ColorType = white;
						m_nTurn++;
						newBox[x][y].turn = m_nTurn;
						m_ntime = 10;
						turnSetup = false;
					}
				}
			}
		}
	}
#pragma endregion
#pragma region 무르기 && 기권
	if (PtInRect(&rework, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON) && m_nTurn>= 1)
	{
		for (int y = 0; y < 19; y++)
		{
			for (int x = 0; x < 19; x++)
			{
				if (newBox[x][y].turn == m_nTurn)
				{
					m_isrework = true;
					newBox[x][y].isPlace = false;
					newBox[x][y].ColorType = none;
					m_nTurn--;
					m_ntime = 30;
				}
				if (newBox[x][y].turn == m_nTurn && m_isrework == false)
				{
					m_isrework = true;
					newBox[x][y].isPlace = false;
					newBox[x][y].ColorType = none;
					m_nTurn--;
					m_ntime = 30;
				}
			}
		}
	}

	if (m_isrework == true)
	{
		reworkCool++;
		if (reworkCool >= 45)
		{
			reworkCool = 0;
			m_isrework = false;
		}

	}
	if (PtInRect(&giveup, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON) && m_nTurn % 2 == 1)
	{
		m_isOmok = true;
	}
#pragma endregion
#pragma region 혼신의 오목검사
	for(int y = 0; y<19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			CheckHorizontalOmok(x, y, (ColorType)newBox[x][y].ColorType);
			CheckVerticalOmok(x, y, (ColorType)newBox[x][y].ColorType);
			CheckDiagonalOmok135(x, y, (ColorType)newBox[x][y].ColorType);
			CheckDiagonalOmok45(x, y, (ColorType)newBox[x][y].ColorType);
		}
	}
#pragma endregion
#pragma region 오목 or 기권
	if (m_isOmok == true)
	{
		OmokCount++;
		if(m_nTurn % 2 == 1 && OmokCount >= 120)
		g_pSceneManager->ChangeScene("OmokB");
		else if (m_nTurn % 2 == 0 && OmokCount >= 120)
		g_pSceneManager->ChangeScene("OmokW");
	}
#pragma endregion
	if (PtInRect(&gomain, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		g_pSceneManager->ChangeScene("Title");
	}

	
}

void cPlayScene::Render()
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
		g_pImageManager->FrameSizeRender("number", g_hDC, 1114, 177, 2,	2, a, 0);
		g_pImageManager->AlphaRender("white", g_hDC, 1030, 240, 64);

	}
	else if (m_nTurn % 2 == 1)
	{
		g_pImageManager->AlphaRender("black", g_hDC, 1030, 170, 64);
		g_pImageManager->Render("white", g_hDC, 1030, 240);
		g_pImageManager->FrameSizeRender("number", g_hDC, 1090, 247, 2, 2, b, 0);
		g_pImageManager->FrameSizeRender("number", g_hDC, 1114, 247, 2, 2, a, 0);
	}

	

	
		for (int y = 0; y < 19; y++)
		{
			for (int x = 0; x < 19; x++)
			{
				if (PtInRect(&newBox[x][y].ClickBox, g_ptMouse))
				{
					//if (m_nTurn % 2 == 0)g_pImageManager->AlphaRender("black", g_hDC, newBox[x][y].PosX - 26, newBox[x][y].PosY - 26, 128);
					if (m_nTurn % 2 == 1)g_pImageManager->AlphaRender("white", g_hDC, newBox[x][y].PosX - 26, newBox[x][y].PosY - 26, 128);
				}

				if (newBox[x][y].isPlace && newBox[x][y].ColorType == black)
				{
					g_pImageManager->Render("black", g_hDC, newBox[x][y].PosX - 26, newBox[x][y].PosY - 26);
				}
				else if (newBox[x][y].isPlace && newBox[x][y].ColorType == white)
				{
					g_pImageManager->Render("white", g_hDC, newBox[x][y].PosX - 26, newBox[x][y].PosY - 26);
				}
			}
		}
	
	char str[128];
	sprintf(str, "차례 : %d", m_nTurn%2);
	TextOut(g_hDC, WINSIZEX - 70, 0, str, strlen(str));
	sprintf(str, "횟수 : %d", m_nTurn);
	TextOut(g_hDC, WINSIZEX - 70, 20, str, strlen(str));
}

void cPlayScene::Release()
{
	
}

void cPlayScene::LoadFile()
{
	g_pImageManager->AddImage("white", "images/white.bmp", 50, 50, true, RGB(255,0,255));
	g_pImageManager->AddImage("black", "images/black.bmp", 50, 50, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("pan", "images/Pan.bmp", 1200, 1000);
	g_pImageManager->AddImage("turn", "images/turn.bmp", 168, 55, true, RGB(255,0,255));
	g_pImageManager->AddImage("number", "images/number.bmp", 120, 17, 10, 1, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("rework", "images/rework.bmp", 120, 45, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("giveup", "images/giveup.bmp", 120, 45, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("gomain", "images/gomain.bmp", 120, 45, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("save", "images/save.bmp", 120, 45, true, RGB(255, 0, 255));
}

void cPlayScene::CheckWeight(int x, int y)
{
	//자기꺼
#pragma region  자신의 돌 근처에 가중치 2 상대방은 1
	if (newBox[x][y].ColorType == 0) 
	{
		newBox[x-1][y-1].Weight += 2;
		newBox[x-1][y].Weight += 2;
		newBox[x-1][y+1].Weight += 2;
		newBox[x][y-1].Weight += 2;
		newBox[x][y+1].Weight += 2;
		newBox[x+1][y-1].Weight += 2;
		newBox[x+1][y].Weight += 2;
		newBox[x+1][y+1].Weight += 2;
	}

	if (newBox[x][y].ColorType == 1)
	{
		newBox[x - 1][y - 1].Weight += 1;
		newBox[x - 1][y].Weight += 1;
		newBox[x - 1][y + 1].Weight += 1;
		newBox[x][y - 1].Weight += 1;
		newBox[x][y + 1].Weight += 1;
		newBox[x + 1][y - 1].Weight += 1;
		newBox[x + 1][y].Weight += 1;
		newBox[x + 1][y + 1].Weight += 1;
	}
#pragma endregion
#pragma region 2줄일때
	if (newBox[x][y].ColorType == 0)
	{
		if (newBox[x][y].ColorType == 0 && newBox[x + 1][y].ColorType == 0) // 가로
		{
			if (newBox[x + 3][y].ColorType != 1 && newBox[x + 4][y].ColorType != 1 && newBox[x-1][y].ColorType != 1)
			{
				newBox[x + 2][y].Weight += 6;
			}
			if (newBox[x - 2][y].ColorType != 1 && newBox[x - 3][y].ColorType != 1 && newBox[x+1][y].ColorType != 1)
			{
				newBox[x - 1][y].Weight += 6;
			}
		}
		if (newBox[x][y].ColorType == 0 && newBox[x][y+1].ColorType == 0) // 세로
		{
			if (newBox[x][y+3].ColorType != 1 && newBox[x][y+4].ColorType != 1 && newBox[x][y-1].ColorType != 1)
			{
				newBox[x][y+2].Weight += 6;
			}
			if (newBox[x][y-2].ColorType != 1 && newBox[x][y-3].ColorType != 1 && newBox[x][y+1].ColorType != 1)
			{
				newBox[x][y-1].Weight += 6;
			}
		}
		if (newBox[x][y].ColorType == 0 && newBox[x+1][y-1].ColorType == 0) // 45각
		{
			if (newBox[x+3][y - 3].ColorType != 1 && newBox[x+4][y - 4].ColorType != 1 && newBox[x - 1][y+1].ColorType != 1)
			{
				newBox[x+2][y - 2].Weight += 6;
			}
			if (newBox[x-2][y + 2].ColorType != 1 && newBox[x-3][y + 3].ColorType != 1 && newBox[x + 1][y-1].ColorType != 1)
			{
				newBox[x-1][y + 1].Weight += 6;
			}
		}
		if (newBox[x][y].ColorType == 0 && newBox[x + 1][y + 1].ColorType == 0) // 135각
		{
			if (newBox[x + 3][y + 3].ColorType != 1 && newBox[x + 4][y + 4].ColorType != 1 && newBox[x - 1][y-1].ColorType != 1)
			{
				newBox[x + 2][y + 2].Weight += 6;
			}
			if (newBox[x - 2][y - 2].ColorType != 1 && newBox[x - 3][y - 3].ColorType != 1 && newBox[x + 1][y + 1].ColorType != 1)
			{
				newBox[x - 1][y - 1].Weight += 6;
			}
		}
	}
#pragma endregion
#pragma region 3줄일때 
	if (newBox[x][y].ColorType == 0 && newBox[x + 1][y].ColorType == 0 && newBox[x + 2][y].ColorType == 0) // 가로
	{
		if (newBox[x + 4][y].ColorType != 1)
		{
			newBox[x + 3][y].Weight += 30;
		}
		if (newBox[x - 2][y].ColorType != 1)
		{
			newBox[x-1][y].Weight += 30;
		}
		
		if (newBox[x-3][y].ColorType != 0 &&  newBox[x - 2][y].ColorType == 0 && newBox[x - 1][y].ColorType != 1)
		{
			newBox[x - 1][y].Weight += 120;
		}
		if (newBox[x + 5][y].ColorType != 0 && newBox[x + 4][y].ColorType == 0 && newBox[x + 3][y].ColorType != 1)
		{
			newBox[x + 3][y].Weight += 120;
		}
	}
	if (newBox[x][y].ColorType == 0 && newBox[x][y+1].ColorType == 0 && newBox[x][y+2].ColorType == 0) // 세로
	{
		if (newBox[x][y + 4].ColorType != 1)
		{
			newBox[x][y + 3].Weight += 30;
		}
		if (newBox[x][y - 2].ColorType != 1)
		{
			newBox[x][y - 1].Weight += 30;
		}

		if (newBox[x][y - 3].ColorType != 0 && newBox[x][y - 2].ColorType == 0 && newBox[x][y - 1].ColorType != 1)
		{
			newBox[x][y - 1].Weight += 120;
		}
		if (newBox[x][y + 5].ColorType != 0 && newBox[x][y + 4].ColorType == 0 && newBox[x][y + 3].ColorType != 1)
		{
			newBox[x][y + 3].Weight += 120;
		}
	}

	if (newBox[x][y].ColorType == 0 && newBox[x+1][y-1].ColorType == 0 && newBox[x+2][y-2].ColorType == 0) // 45각 
	{
		if (newBox[x+4][y-4].ColorType != 1)
		{
			newBox[x+3][y-3].Weight += 30;
		}
		if (newBox[x-2][y+2].ColorType != 1)
		{
			newBox[x-1][y + 1].Weight += 30;
		}

		if (newBox[x - 3][y+3].ColorType != 0 && newBox[x - 2][y+2].ColorType == 0 && newBox[x - 1][y+1].ColorType != 1)
		{
			newBox[x - 1][y+1].Weight += 120;
		}
		if (newBox[x + 5][y-5].ColorType != 0 && newBox[x + 4][y-4].ColorType == 0 && newBox[x + 3][y-3].ColorType != 1)
		{
			newBox[x + 3][y-3].Weight += 120;
		}
	}

	if (newBox[x][y].ColorType == 0 && newBox[x + 1][y + 1].ColorType == 0 && newBox[x + 2][y + 2].ColorType == 0) // 135각
	{
		if (newBox[x + 4][y + 4].ColorType != 1)
		{
			newBox[x + 3][y + 3].Weight += 30;
		}
		if (newBox[x - 2][y - 2].ColorType != 1)
		{
			newBox[x - 1][y - 1].Weight += 30;
		}

		if (newBox[x-3][y - 3].ColorType != 0 && newBox[x-2][y - 2].ColorType == 0 && newBox[x-1][y - 1].ColorType != 1)
		{
			newBox[x-1][y - 1].Weight += 120;
		}
		if (newBox[x+5][y + 5].ColorType != 0 && newBox[x+4][y + 4].ColorType == 0 && newBox[x+3][y + 3].ColorType != 1)
		{
			newBox[x+3][y + 3].Weight += 120;
		}
	}

#pragma endregion
#pragma region 한칸 띄어진 3줄
	if (newBox[x][y].ColorType == 0 && newBox[x + 1][y].ColorType == none && newBox[x + 2][y].ColorType == 0 && newBox[x + 3][y].ColorType == 0) // 가로
	{
		if (newBox[x - 2][y].ColorType != 0)
			newBox[x + 1][y].Weight += 30;
		if (newBox[x + 5][y].ColorType != 0)
			newBox[x + 1][y].Weight += 30;
	}
	if (newBox[x][y].ColorType == 0 && newBox[x + 1][y].ColorType == 0 && newBox[x + 2][y].ColorType == none && newBox[x + 3][y].ColorType == 0) // 가로
	{
		if (newBox[x - 2][y].ColorType != 0)
			newBox[x + 2][y].Weight += 30;
		if (newBox[x + 5][y].ColorType != 0)
			newBox[x + 2][y].Weight += 30;
	}


	if (newBox[x][y].ColorType == 0 && newBox[x][y + 1].ColorType == none && newBox[x][y + 2].ColorType == 0 && newBox[x][y + 3].ColorType == 0) // 세로
	{
		if (newBox[x][y - 2].ColorType != 0)
			newBox[x][y + 1].Weight += 30;
		if (newBox[x][y + 5].ColorType != 0)
			newBox[x][y + 1].Weight += 30;
	}
	if (newBox[x][y].ColorType == 0 && newBox[x][y + 1].ColorType == 0 && newBox[x][y + 2].ColorType == none && newBox[x][y + 3].ColorType == 0) // 세로
	{
		if (newBox[x][y - 2].ColorType != 0)
			newBox[x][y + 2].Weight += 30;
		if (newBox[x][y + 5].ColorType != 0)
			newBox[x][y + 2].Weight += 30;
	}


	if (newBox[x][y].ColorType == 0 && newBox[x + 1][y - 1].ColorType == none && newBox[x + 2][y - 2].ColorType == 0 && newBox[x + 3][y - 3].ColorType == 0)// 45각
	{
		if (newBox[x - 2][y + 2].ColorType != 0)
			newBox[x + 1][y - 1].Weight += 30;
		if (newBox[x + 5][y - 5].ColorType != 0)
			newBox[x + 1][y - 1].Weight += 30;
	}
	if (newBox[x][y].ColorType == 0 && newBox[x + 1][y - 1].ColorType == 0 && newBox[x + 2][y - 2].ColorType == none && newBox[x + 3][y - 3].ColorType == 0)// 45각
	{
		if (newBox[x - 2][y + 2].ColorType != 0)
			newBox[x + 2][y - 2].Weight += 30;
		if (newBox[x + 5][y - 5].ColorType != 0)
			newBox[x + 2][y - 2].Weight += 30;
	}


	if (newBox[x][y].ColorType == 0 && newBox[x + 1][y + 1].ColorType == none && newBox[x + 2][y + 2].ColorType == 0 && newBox[x + 3][y + 3].ColorType == 0) // 135각
	{
		if (newBox[x - 2][y - 2].ColorType != 0)
			newBox[x + 1][y + 1].Weight += 30;
		if (newBox[x + 5][y + 5].ColorType != 0)
			newBox[x + 1][y + 1].Weight += 30;
	}
	if (newBox[x][y].ColorType == 0 && newBox[x + 1][y + 1].ColorType == 0 && newBox[x + 2][y + 2].ColorType == none && newBox[x + 3][y + 3].ColorType == 0) // 135각
	{
		if (newBox[x - 2][y - 2].ColorType != 0)
			newBox[x + 2][y + 2].Weight += 30;
		if (newBox[x + 5][y + 5].ColorType != 0)
			newBox[x + 2][y + 2].Weight += 30;
	}
#pragma endregion
#pragma region 4줄일때 
	if (newBox[x][y].ColorType == 0 && newBox[x + 1][y].ColorType == 0 && newBox[x + 2][y].ColorType == 0 && newBox[x + 3][y].ColorType == 0) // 가로
	{
		if (newBox[x - 2][y].ColorType != 0)
		newBox[x-1][y].Weight += 120;
		if (newBox[x + 5][y].ColorType != 0)
		newBox[x+4][y].Weight += 120;
	}
	if (newBox[x][y].ColorType == 0 && newBox[x][y + 1].ColorType == 0 && newBox[x][y + 2].ColorType == 0 && newBox[x][y + 3].ColorType == 0) // 세로
	{
		if (newBox[x][y - 2].ColorType != 0)
		newBox[x][y - 1].Weight += 120;
		if (newBox[x][y + 5].ColorType != 0)
		newBox[x][y + 4].Weight += 120;
	}
	if (newBox[x][y].ColorType == 0 && newBox[x + 1][y - 1].ColorType == 0 && newBox[x + 2][y - 2].ColorType == 0 && newBox[x + 3][y - 3].ColorType == 0)// 45각
	{
		if (newBox[x - 2][y + 2].ColorType != 0)
		newBox[x - 1][y+1].Weight += 120;
		if (newBox[x + 5][y - 5].ColorType != 0)
		newBox[x + 4][y-4].Weight += 120;
	}
	if (newBox[x][y].ColorType == 0 && newBox[x+1][y + 1].ColorType == 0 && newBox[x+2][y + 2].ColorType == 0 && newBox[x+3][y + 3].ColorType == 0) // 135각
	{
		if (newBox[x - 2][y - 2].ColorType != 0)
		newBox[x-1][y - 1].Weight += 120;
		if (newBox[x + 5][y + 5].ColorType != 0)
		newBox[x+4][y + 4].Weight += 120;
	}
#pragma endregion
#pragma region 플레이어 2줄일때
	if (newBox[x][y].ColorType == 1)
	{
		if (newBox[x][y].ColorType == 1 && newBox[x + 1][y].ColorType == 1) // 가로
		{
			if (newBox[x + 3][y].ColorType != 0 && newBox[x + 4][y].ColorType != 0 && newBox[x - 1][y].ColorType != 0)
			{
				newBox[x + 2][y].Weight += 5;
			}
			if (newBox[x - 2][y].ColorType != 0 && newBox[x - 3][y].ColorType != 0 && newBox[x + 1][y].ColorType != 0)
			{
				newBox[x - 1][y].Weight += 5;
			}
		}
		if (newBox[x][y].ColorType == 1 && newBox[x][y + 1].ColorType == 1) // 세로
		{
			if (newBox[x][y + 3].ColorType != 0 && newBox[x][y + 4].ColorType != 0 && newBox[x][y - 1].ColorType != 0)
			{
				newBox[x][y + 2].Weight += 5;
			}
			if (newBox[x][y - 2].ColorType != 0 && newBox[x][y - 3].ColorType != 1 && newBox[x][y + 1].ColorType != 0)
			{
				newBox[x][y - 1].Weight += 5;
			}
		}
		if (newBox[x][y].ColorType == 1 && newBox[x + 1][y - 1].ColorType == 1) // 45각
		{
			if (newBox[x + 3][y - 3].ColorType != 0 && newBox[x + 4][y - 4].ColorType != 0 && newBox[x - 1][y + 1].ColorType != 0)
			{
				newBox[x + 2][y - 2].Weight += 5;
			}
			if (newBox[x - 2][y + 2].ColorType != 0 && newBox[x - 3][y + 3].ColorType != 0 && newBox[x + 1][y - 1].ColorType != 0)
			{
				newBox[x - 1][y + 1].Weight += 5;
			}
		}
		if (newBox[x][y].ColorType == 1 && newBox[x + 1][y + 1].ColorType == 1) // 135각
		{
			if (newBox[x + 3][y + 3].ColorType != 0 && newBox[x + 4][y + 4].ColorType != 0 && newBox[x - 1][y - 1].ColorType != 0)
			{
				newBox[x + 2][y + 2].Weight += 5;
			}
			if (newBox[x - 2][y - 2].ColorType != 0 && newBox[x - 3][y - 3].ColorType != 0 && newBox[x + 1][y + 1].ColorType != 0)
			{
				newBox[x - 1][y - 1].Weight += 5;
			}
		}
	}
#pragma endregion
#pragma region 플레이어 3줄일때
	//플레이어꺼
	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y].ColorType == 1 && newBox[x + 2][y].ColorType == 1 && newBox[x-1][y].ColorType != 1) // 가로
	{
		if (newBox[x + 4][y].ColorType != 0)
		{
			newBox[x + 3][y].Weight += 25;
		}
		if (newBox[x - 2][y].ColorType != 0)
		{
			newBox[x - 1][y].Weight += 25;
		}

		if (newBox[x - 3][y].ColorType != 1 && newBox[x - 2][y].ColorType == 1 && newBox[x - 1][y].ColorType != 0)
		{
			newBox[x - 1][y].Weight += 100;
		}
		if (newBox[x + 5][y].ColorType != 1 && newBox[x + 4][y].ColorType == 1 && newBox[x + 3][y].ColorType != 0)
		{
			newBox[x + 3][y].Weight += 100;
		}
	}
	if (newBox[x][y].ColorType == 1 && newBox[x][y + 1].ColorType == 1 && newBox[x][y + 2].ColorType == 1 && newBox[x][y-1].ColorType != 1) // 세로
	{
		if (newBox[x][y + 4].ColorType != 0)
		{
			newBox[x][y + 3].Weight += 25;
		}
		if (newBox[x][y - 2].ColorType != 0)
		{
			newBox[x][y - 1].Weight += 25;
		}

		if (newBox[x][y - 3].ColorType != 1 && newBox[x][y - 2].ColorType == 1 && newBox[x][y - 1].ColorType != 0)
		{
			newBox[x][y - 1].Weight += 100;
		}
		if (newBox[x][y + 5].ColorType != 1 && newBox[x][y + 4].ColorType == 1 && newBox[x][y + 3].ColorType != 0)
		{
			newBox[x][y + 3].Weight += 100;
		}
	}
	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y - 1].ColorType == 1 && newBox[x + 2][y - 2].ColorType == 1 && newBox[x-1][y + 1].ColorType != 1 ) // 45각
	{
		if (newBox[x + 4][y - 4].ColorType != 0)
		{
			newBox[x + 3][y - 3].Weight += 25;
		}
		if (newBox[x - 2][y + 2].ColorType != 0)
		{
			newBox[x - 1][y + 1].Weight += 25;
		}

		if (newBox[x - 3][y + 3].ColorType != 1 && newBox[x - 2][y + 2].ColorType == 1 && newBox[x - 1][y + 1].ColorType != 0)
		{
			newBox[x - 1][y + 1].Weight += 100;
		}
		if (newBox[x + 5][y - 5].ColorType != 1 && newBox[x + 4][y - 4].ColorType == 1 && newBox[x + 3][y - 3].ColorType != 0)
		{
			newBox[x + 3][y - 3].Weight += 100;
		}
	}
	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y + 1].ColorType == 1 && newBox[x + 2][y + 2].ColorType == 1 && newBox[x - 1][y - 1].ColorType != 1) // 135각
	{
		if (newBox[x + 4][y + 4].ColorType != 0)
		{
			newBox[x + 3][y + 3].Weight += 25;
		}
		if (newBox[x - 2][y - 2].ColorType != 0)
		{
			newBox[x - 1][y - 1].Weight += 25;
		}
		if (newBox[x - 3][y - 3].ColorType != 1 && newBox[x - 2][y - 2].ColorType == 1 && newBox[x - 1][y - 1].ColorType != 0)
		{
			newBox[x - 1][y - 1].Weight += 100;
		}
		if (newBox[x + 5][y + 5].ColorType != 1 && newBox[x + 4][y + 4].ColorType == 1 && newBox[x + 3][y + 3].ColorType != 0)
		{
			newBox[x + 3][y + 3].Weight += 100;
		}
	}
#pragma endregion
#pragma region 플레이어 한칸 띄어진 3줄
	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y].ColorType == 2 && newBox[x + 2][y].ColorType == 1 && newBox[x + 3][y].ColorType == 1) // 가로
	{
		if (newBox[x - 2][y].ColorType != 1)
			newBox[x + 1][y].Weight += 25;
		if (newBox[x + 5][y].ColorType != 1)
			newBox[x + 1][y].Weight += 25;
	}
	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y].ColorType == 1 && newBox[x + 2][y].ColorType == 2 && newBox[x + 3][y].ColorType == 1) // 가로
	{
		if (newBox[x - 2][y].ColorType != 1)
			newBox[x + 2][y].Weight += 25;
		if (newBox[x + 5][y].ColorType != 1)
			newBox[x + 2][y].Weight += 25;
	}

	if (newBox[x][y].ColorType == 1 && newBox[x][y + 1].ColorType == 2 && newBox[x][y + 2].ColorType == 1 && newBox[x][y + 3].ColorType == 1) // 세로
	{
		if (newBox[x][y - 2].ColorType != 1)
			newBox[x][y + 1].Weight += 25;
		if (newBox[x][y + 5].ColorType != 1)
			newBox[x][y + 1].Weight += 25;
	}
	if (newBox[x][y].ColorType == 1 && newBox[x][y + 1].ColorType == 1 && newBox[x][y + 2].ColorType == 2 && newBox[x][y + 3].ColorType == 1) // 세로
	{
		if (newBox[x][y - 2].ColorType != 1)
			newBox[x][y + 2].Weight += 25;
		if (newBox[x][y + 5].ColorType != 1)
			newBox[x][y + 2].Weight += 25;
	}

	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y - 1].ColorType == 2 && newBox[x + 2][y - 2].ColorType == 1 && newBox[x + 3][y - 3].ColorType == 1)// 45각
	{
		if (newBox[x - 2][y + 2].ColorType != 1)
			newBox[x + 1][y - 1].Weight += 25;
		if (newBox[x + 5][y - 5].ColorType != 1)
			newBox[x + 1][y - 1].Weight += 25;
	}
	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y - 1].ColorType == 1 && newBox[x + 2][y - 2].ColorType == 2 && newBox[x + 3][y - 3].ColorType == 1)// 45각
	{
		if (newBox[x - 2][y + 2].ColorType != 1)
			newBox[x + 2][y - 2].Weight += 25;
		if (newBox[x + 5][y - 5].ColorType != 1)
			newBox[x + 2][y - 2].Weight += 25;
	}

	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y + 1].ColorType == 2 && newBox[x + 2][y + 2].ColorType == 1 && newBox[x + 3][y + 3].ColorType == 1) // 135각
	{
		if (newBox[x - 2][y - 2].ColorType != 1)
			newBox[x + 1][y + 1].Weight += 25;
		if (newBox[x + 5][y + 5].ColorType != 1)
			newBox[x + 1][y + 1].Weight += 25;
	}
	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y + 1].ColorType == 1 && newBox[x + 2][y + 2].ColorType == 2 && newBox[x + 3][y + 3].ColorType == 1) // 135각
	{
		if (newBox[x - 2][y - 2].ColorType != 1)
			newBox[x + 2][y + 2].Weight += 25;
		if (newBox[x + 5][y + 5].ColorType != 1)
			newBox[x + 2][y + 2].Weight += 25;
	}

#pragma endregion
#pragma region 플레이어 4줄일때
	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y].ColorType == 1 && newBox[x + 2][y].ColorType == 1 && newBox[x + 3][y].ColorType == 1) // 가로
	{
		if (newBox[x - 2][y].ColorType != 1)
		newBox[x - 1][y].Weight += 100;
		if (newBox[x + 5][y].ColorType != 1)
		newBox[x + 4][y].Weight += 100;
	}
	if (newBox[x][y].ColorType == 1 && newBox[x][y + 1].ColorType == 1 && newBox[x][y + 2].ColorType == 1 && newBox[x][y + 3].ColorType == 1) // 세로
	{
		if (newBox[x][y-2].ColorType != 1)
		newBox[x][y - 1].Weight += 100;
		if (newBox[x][y+5].ColorType != 1)
		newBox[x][y + 4].Weight += 100;
	}
	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y - 1].ColorType == 1 && newBox[x + 2][y - 2].ColorType == 1 && newBox[x + 3][y - 3].ColorType == 1)// 45각
	{
		if (newBox[x - 2][y+2].ColorType != 1)
		newBox[x - 1][y + 1].Weight += 100;
		if (newBox[x +5][y-5].ColorType != 1)
		newBox[x + 4][y - 4].Weight += 100;
	}
	if (newBox[x][y].ColorType == 1 && newBox[x + 1][y + 1].ColorType == 1 && newBox[x + 2][y + 2].ColorType == 1 && newBox[x + 3][y + 3].ColorType == 1) // 135각
	{
		if(newBox[x-2][y-2].ColorType != 1 )
		newBox[x - 1][y - 1].Weight += 100;
		if (newBox[x +5][y+5].ColorType != 1)
		newBox[x + 4][y + 4].Weight += 100;
	}
#pragma endregion
}

bool cPlayScene::CheckHorizontalOmok(int x, int y, ColorType color)
{
	if (x <= 14 && color != 2)
	{
		if (x == 0)
		{
			if (newBox[x][y].ColorType == color && newBox[x + 5][y].ColorType != color && newBox[x + 1][y].ColorType == color &&
				newBox[x + 2][y].ColorType == color && newBox[x + 3][y].ColorType == color && newBox[x + 4][y].ColorType == color)
				m_isOmok = true;
		}
		else if (x >= 1 && x<=13)
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

bool cPlayScene::CheckVerticalOmok(int x, int y, ColorType color)
{
	if (y <= 14 && color != 2)
	{
		if (y == 0)
		{
			if (newBox[x][y].ColorType == color && newBox[x][y+5].ColorType != color && newBox[x][y+1].ColorType == color &&
				newBox[x][y+2].ColorType == color && newBox[x][y+3].ColorType == color && newBox[x][y+4].ColorType == color)
				m_isOmok = true;
		}
		else if (y >= 1 && y <= 13)
		{
			if (newBox[x][y].ColorType == color && newBox[x][y + 5].ColorType != color&& newBox[x][y-1].ColorType != color && newBox[x][y + 1].ColorType == color &&
				newBox[x][y + 2].ColorType == color && newBox[x][y + 3].ColorType == color && newBox[x][y + 4].ColorType == color)
				m_isOmok = true;
		}
		else if (y == 14 )
		{
			if (newBox[x][y].ColorType == color && newBox[x][y - 1].ColorType != color && newBox[x][y + 1].ColorType == color &&
				newBox[x][y + 2].ColorType == color && newBox[x][y + 3].ColorType == color && newBox[x][y + 4].ColorType == color)
				m_isOmok = true;
		}
	}
	return m_isOmok;
}

bool cPlayScene::CheckDiagonalOmok45(int x, int y, ColorType color)
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

bool cPlayScene::CheckDiagonalOmok135(int x, int y, ColorType color)
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
				newBox[x + 4][y + 4].ColorType == color && newBox[x-1][y-1].ColorType != color)
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

bool cPlayScene::CheckDoubleTriple(int x, int y, ColorType color)
{
	
	return m_isDoubleTriple;
}
