#pragma once
#include"cGameNode.h"

enum ColorType2
{
	black2,
	white2,
	none2,

};
struct tagBox2
{
	int PosX;					// 위치
	int PosY;					// 위치
	int ColorType;				// 색깔
	bool isPlace;				// 뒀냐
	RECT ClickBox;				// 클릭박스
	int turn;
};

class cLoadGame : public  cGameNode
{
private:
	tagBox2 newBox[19][19];
	int m_nTurn;
	bool m_isOmok;
	int m_nTestOmok;
	int m_ntime;
	int m_ntimecount;
	bool m_isDoubleTriple;
	RECT rework;
	RECT giveup;
	RECT gomain;
	RECT save;
	bool m_isrework;
	int reworkCool;
public:
	cLoadGame();
	~cLoadGame();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void LoadFile();
	void LoadGame(tagBox2 box);
	void SaveGame(tagBox2 box);

	bool CheckHorizontalOmok(int x, int y, ColorType2 color);
	bool CheckVerticalOmok(int x, int y, ColorType2 color);
	bool CheckDiagonalOmok45(int x, int y, ColorType2 color);
	bool CheckDiagonalOmok135(int x, int y, ColorType2 color);
	bool CheckDoubleTriple(int x, int y, ColorType2 color);
};

