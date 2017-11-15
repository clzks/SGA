#pragma once
#include "cProgressBar.h"

enum LOAD_KIND
{
	LOAD_KIND_EMPTY,		// 빈 비트맵 이미지
	LOAD_KIND_IMAGE_0,		// 일반 이미지
	LOAD_KIND_FRAMEIMAGE_0,	// 프레임 이미지
	LOAD_KIND_FRAMEIMAGE_1,	// 프레임 이미지
	LOAD_KIND_SOUND,		// 사운드
	LOAD_KIND_END
};

struct tagImageResource
{
	string key;				// 이미지 키값
	const char* fileName;	// 파일 이름
	int x, y;				// 위치 좌표
	int width, height;		// 가로 세로 크기
	int frameX, frameY;		// 프레임 갯수
	bool isTrans;			// 배경(마젠타) 처리
	COLORREF transColor;	// 배경(마젠타) 값
};

class cLoadItem
{
private:
	LOAD_KIND			m_eKind;
	tagImageResource	m_stImageResource;

public:
	cLoadItem() {};
	~cLoadItem() {};

	// 빈 비트맵으로 초기화 및 추가
	void InitForEmpty(string key, int width, int height);
	// 이미지 - 파일로 초기화 및 추가
	void InitForImage(string key, const char* fileName,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 프레임 이미지 - 파일로 초기화 및 추가
	void InitForFrameImage(string key, const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void InitForFrameImage(string key, const char* fileName, int width, int height,
		int frameX, int frameY, int x, int y, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	// 로딩 아이템 종류 가져오기
	LOAD_KIND GetLoadingKind() { return m_eKind; }
	// 이미지 리소스 정보 가져오기
	tagImageResource GetImageResource() { return m_stImageResource; }
};

class cLoading
{
private:
	vector<cLoadItem*>		m_vLoadItem;		// 로드할 리소스들을 담을 벡터
	cImage*					m_pImgBackground;	// 로딩 화면 배경
	cProgressBar*			m_pLoadingBar;		// 로딩 바
	int						m_nCurrentGauge;	// 현재 로딩 게이지

public:
	cLoading() {};
	~cLoading() {};

	void Setup();
	void Render();
	void Release();

	void LoadEmpty(string key, int width, int height);
	void LoadImageFile(string key, const char* fileName,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void LoadFrameImage(string key, const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void LoadFrameImage(string key, const char* fileName, int width, int height,
		int frameX, int frameY, int x, int y, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// void LoadSound(string key, const char* fileName, bool bgm, bool loop);		// 나중에 추가

	// 로딩 완료 됐는가?
	bool LoadingDone();

	// 로드 아이템 벡터 가져오기
	vector<cLoadItem*> GetLoadItem() { return m_vLoadItem; }
};

