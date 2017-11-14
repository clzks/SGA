#pragma once
#include "cGameNode.h"

enum ColorType
{
	black,
	white,
	none,
	
};

struct tagBox
{
	int PosX;					// ��ġ
	int PosY;					// ��ġ
	int ColorType;				// ����
	bool isPlace;				// �׳�
	RECT ClickBox;				// Ŭ���ڽ�
	int turn;
	int Weight;
};

class cPlayScene : public cGameNode
{
private:
	
	tagBox newBox[19][19];
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
	bool turnSetup;

	int OmokCount;
public:
	cPlayScene();
	virtual ~cPlayScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	
	void LoadFile();
	void LoadGame(tagBox box);
	void SaveGame(tagBox box);
	void CheckWeight(int x, int y);

	bool CheckHorizontalOmok(int x, int y, ColorType color);
	bool CheckVerticalOmok(int x, int y, ColorType color);
	bool CheckDiagonalOmok45(int x, int y, ColorType color);
	bool CheckDiagonalOmok135(int x, int y, ColorType color);
	bool CheckDoubleTriple(int x, int y, ColorType color);
};

