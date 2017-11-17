#include "stdafx.h"
#include "cLoading.h"


void cLoadItem::InitForEmpty(string key, int width, int height)
{
	m_eKind = LOAD_KIND_EMPTY;

	// 구조체 초기화
	memset(&m_stImageResource, 0, sizeof(tagImageResource));

	m_stImageResource.key = string(key);
	m_stImageResource.width = width;
	m_stImageResource.height = height;
}

void cLoadItem::InitForImage(string key, const char * fileName, int width, int height,
	bool isTrans, COLORREF transColor)
{
	m_eKind = LOAD_KIND_IMAGE_0;

	memset(&m_stImageResource, 0, sizeof(tagImageResource));

	m_stImageResource.key = string(key);
	m_stImageResource.fileName = fileName;
	m_stImageResource.width = width;
	m_stImageResource.height = height;
	m_stImageResource.isTrans = isTrans;
	m_stImageResource.transColor = transColor;
}

void cLoadItem::InitForFrameImage(string key, const char * fileName, int width, int height,
	int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	m_eKind = LOAD_KIND_FRAMEIMAGE_0;

	memset(&m_stImageResource, 0, sizeof(tagImageResource));

	m_stImageResource.key = string(key);
	m_stImageResource.fileName = fileName;
	m_stImageResource.width = width;
	m_stImageResource.height = height;
	m_stImageResource.frameX = frameX;
	m_stImageResource.frameY = frameY;
	m_stImageResource.isTrans = isTrans;
	m_stImageResource.transColor = transColor;
}

void cLoadItem::InitForFrameImage(string key, const char * fileName, int width, int height,
	int frameX, int frameY, int x, int y, bool isTrans, COLORREF transColor)
{
	m_eKind = LOAD_KIND_FRAMEIMAGE_1;

	memset(&m_stImageResource, 0, sizeof(tagImageResource));

	m_stImageResource.key = string(key);
	m_stImageResource.fileName = fileName;
	m_stImageResource.width = width;
	m_stImageResource.height = height;
	m_stImageResource.frameX = frameX;
	m_stImageResource.frameY = frameY;
	m_stImageResource.x = x;
	m_stImageResource.y = y;
	m_stImageResource.isTrans = isTrans;
	m_stImageResource.transColor = transColor;
}

void cLoadItem::InitForSound(string key, const char * fileName, bool bgm, bool loop)
{
	m_eKind = LOAD_KIND_SOUND;
	memset(&m_stSoundResource, 0, sizeof(tagSoundResource));

	m_stSoundResource.key = string(key);
	m_stSoundResource.fileName = fileName;
	m_stSoundResource.bgm = bgm;
	m_stSoundResource.loop = loop;
}

// =================================================================================================

void cLoading::Setup()
{
	m_pImgBackground = g_pImageManager->AddImage("Loading", "images/bgLoadingScene.bmp", WINSIZEX, WINSIZEY);

	g_pImageManager->AddImage("BarBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("BarFront", "images/progressBarFront.bmp", 50, 10);

	// 로딩바 초기화
	m_pLoadingBar = new cProgressBar("BarBack", "BarFront", WINSIZEX - 100, 30);
	m_pLoadingBar->SetPosX(WINSIZEX / 2);
	m_pLoadingBar->SetPosY(WINSIZEY - 100);
	// 로딩 게이지 초기화
	m_nCurrentGauge = 0;

	m_pLoadingBar->Update();
}

void cLoading::Render()
{
	// 백그라운드
	m_pImgBackground->Render(g_hDC);
	// 로딩바
	m_pLoadingBar->Render();

	/* 로딩 데이터 */
	// 폰트 설정
	SetBkMode(g_hDC, TRANSPARENT);
	SetTextColor(g_hDC, RGB(255, 255, 255));
	SetTextAlign(g_hDC, TA_CENTER);
	HFONT hFont = CreateFont(0, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, 0, 0);
	HFONT hOldFont = (HFONT)SelectObject(g_hDC, hFont);

	char str[256];

	if (m_nCurrentGauge < m_vLoadItem.size()) // 로딩 중
	{
		cLoadItem* currItem = *(m_vLoadItem.begin() + m_nCurrentGauge);
		// 이미지 로드
		if (currItem->GetLoadingKind() != LOAD_KIND_SOUND)
		{
			sprintf_s(str, 256, "%s", currItem->GetImageResource().key.c_str());
		}
		else // 사운드 로드
		{
			sprintf_s(str, 256, "%s", currItem->GetSoundResource().key.c_str());
		}

		TextOut(g_hDC, m_pLoadingBar->GetPosX(), m_pLoadingBar->GetPosY() - 15, str, strlen(str));
	}

	DeleteObject(hFont);
	DeleteObject(hOldFont);


}

void cLoading::Release()
{
	g_pImageManager->ReleaseImage("Loading");
	g_pImageManager->ReleaseImage("BarBack");
	g_pImageManager->ReleaseImage("BarFront");
	SAFE_DELETE(m_pLoadingBar);
}

void cLoading::LoadEmpty(string key, int width, int height)
{
	cLoadItem* item = new cLoadItem;
	item->InitForEmpty(key, width, height);

	m_vLoadItem.push_back(item);
}

void cLoading::LoadImageFile(string key, const char* fileName, int width, int height,
	bool isTrans, COLORREF transColor)
{
	cLoadItem* item = new cLoadItem;
	item->InitForImage(key, fileName, width, height, isTrans, transColor);

	m_vLoadItem.push_back(item);
}

void cLoading::LoadFrameImage(string key, const char * fileName, int width, int height,
	int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	cLoadItem* item = new cLoadItem;
	item->InitForFrameImage(key, fileName, width, height, frameX, frameY, isTrans, transColor);

	m_vLoadItem.push_back(item);
}

void cLoading::LoadFrameImage(string key, const char * fileName, int width, int height,
	int frameX, int frameY, int x, int y, bool isTrans, COLORREF transColor)
{
	cLoadItem* item = new cLoadItem;
	item->InitForFrameImage(key, fileName, width, height, frameX, frameY, x, y, isTrans, transColor);

	m_vLoadItem.push_back(item);
}

void cLoading::LoadSound(string key, const char * fileName, bool bgm, bool loop)
{
	cLoadItem* item = new cLoadItem;
	item->InitForSound(key, fileName, bgm, loop);

	m_vLoadItem.push_back(item);

}

bool cLoading::LoadingDone()
{
	if (m_nCurrentGauge >= m_vLoadItem.size())
		return true;

	cLoadItem* item = m_vLoadItem[m_nCurrentGauge];
	tagImageResource img;
	tagSoundResource wav;

	switch (item->GetLoadingKind())
	{
	case LOAD_KIND_EMPTY:
		img = item->GetImageResource();
		g_pImageManager->AddEmptyImage(img.key, img.width, img.height);
		break;
	case LOAD_KIND_IMAGE_0:
		img = item->GetImageResource();
		g_pImageManager->AddImage(img.key, img.fileName, img.width, img.height,
			img.isTrans, img.transColor);
		break;
	case LOAD_KIND_FRAMEIMAGE_0:
		img = item->GetImageResource();
		g_pImageManager->AddFrameImage(img.key, img.fileName, img.width, img.height,
			img.frameX, img.frameY, img.isTrans, img.transColor);
		break;
	case LOAD_KIND_FRAMEIMAGE_1:
		img = item->GetImageResource();
		g_pImageManager->AddFrameImage(img.key, img.fileName, img.width, img.height,
			img.frameX, img.frameY, img.x, img.y, img.isTrans, img.transColor);
		break;
	case LOAD_KIND_SOUND:
		wav = item->GetSoundResource();
		g_pSoundManager->AddSound(wav.key, wav.fileName, wav.bgm, wav.loop);
		break;
	}

	// 카운트
	++m_nCurrentGauge;

	// 로딩바 업데이트
	m_pLoadingBar->SetGauge(m_nCurrentGauge, m_vLoadItem.size());

	return false;
}