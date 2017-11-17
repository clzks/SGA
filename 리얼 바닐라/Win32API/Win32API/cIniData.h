#pragma once
#include "cSingletonBase.h"

#define g_pIniData cIniData::GetInstance()

// INI 데이터 구조체
struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class cIniData : public cSingletonBase<cIniData>
{
private:
	// typedef: 형 재정의
	typedef vector<tagIniData> arrIniData;
	typedef vector<tagIniData>::iterator arrIniDataIter;

	//typedef vector<arrIniData> arrIniDatas;
	//typedef vector<arrIniData>::iterator arrIniDatasIter;

private:
	arrIniData m_vIniDatas;

public:
	// 데이터 추가 (섹션, 키, 밸류)
	void AddData(char* section, char* key, char* value);
	// 세이브 (파일 이름)
	void IniSave(char* fileName);
	// 문자값 로드 (파일, 섹션, 키)
	char* LoadDataString(char* fileName, char* section, char* key);
	// 정수값 로드 (파일, 섹션, 키)
	int LoadDataInteger(char* fileName, char* section, char* key);
};

