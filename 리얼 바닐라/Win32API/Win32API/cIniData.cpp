#include "stdafx.h"
#include "cIniData.h"


// 데이터 추가 (섹션, 키, 밸류)
void cIniData::AddData(char* section, char* key, char* value)
{
	// INI 데이터 구조체 선언 및 초기화
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	// ini데이터 구조체 벡터에 담기
	arrIniData vIniData;
	m_vIniDatas.push_back(iniData);
}

// 세이브 (파일 이름)
void cIniData::IniSave(char* fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	for (int i = 0; i < m_vIniDatas.size(); ++i)
	{
		WritePrivateProfileString(m_vIniDatas[i].section, m_vIniDatas[i].key, m_vIniDatas[i].value, str);
	}

	//for (arrIniDataIter iter = m_vIniDatas.begin(); iter != m_vIniDatas.end(); ++iter)
	//{
	//	WritePrivateProfileString(iter->section, iter->key, iter->value, str);
	//}

	m_vIniDatas.clear();
}

// 문자값 로드 (파일, 섹션, 키)
char* cIniData::LoadDataString(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	char data[64] = { NULL };
	GetPrivateProfileString(section, key, "", data, 64, str);

	return data;
}

// 정수값 로드 (파일, 섹션, 키)
int cIniData::LoadDataInteger(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	return GetPrivateProfileInt(section, key, 0, str);
}
