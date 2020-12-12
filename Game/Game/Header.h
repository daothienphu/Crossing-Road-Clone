#pragma once
#include <iostream>
#include <windows.h>
using namespace std;

#pragma region Util
void fixSizedConsoleWindow();
void gotoXY(int x, int y);
#pragma endregion

#pragma region Classes def
//class CPEOPLE {
//	int mX, mY;
//	bool mState;
//public:
//	CPEOPLE();
//	void Up(int);
//	void Left(int);
//	void Right(int);
//	void Down(int);
//	bool isImpact(const CVEHICLE*&);
//	bool isImpact(const CANIMAL*&);
//	bool isFinish();
//	bool isDead();
//};
//class CVEHICLE {
//	int mX, mY;
//public:
//	virtual void Move(int, int);
//	//...
//};
//class CTRUCK : public CVEHICLE {
//public:
//	//...
//};
//class CCAR : public CVEHICLE {
//public:
//	//...
//};
//class CANIMAL {
//	int mX, mY;
//public:
//	virtual void Move(int, int);
//	virtual void Tell();
//};
//class CDINOSAUR : public CANIMAL {
//public:
//	//...
//};
//class CBIRD : public CANIMAL {
//public:
//	//...
//};
//
//class CGAME {
//	CTRUCK* axt;
//	CCAR* axh;
//	CDINOSAUR* akl;
//	CBIRD* ac;
//	CPEOPLE cn;
//public:
//	CGAME();
//	void drawGame();
//	~CGAME();
//	CPEOPLE getPeople();
//	CVEHICLE* getVehicle();
//	CANIMAL* getAnimal();
//	void resetGame();
//	void exitGame(HANDLE);
//	void startGame();
//	void loadGame(istream);
//	void saveGame(istream);
//	void pauseGame(HANDLE);
//	void resumeGame(HANDLE);
//	void updatePosPeople(char);
//	void updatePosVehicle();
//	void updatePosAnimal();
//}
//
//
//
//char MOVING;
//CGAME cg;
//
//void SubThread()
//{
//	while (IS_RUNNING) {
//		if (!cg.getPeople().isDead())
//		{
//			cg.updatePosPeople(MOVING);
//
//		}
//		MOVING = ' ';
//		cg.updatePosVehicle();
//		cg.updatePosAnimal();
//		cg.drawGame();
//		if (cg.getPeople().isImpact(cg.getVehicle() ||
//			cg.getPeople().isImpact(cg.getAnimal())
//		{
//
//		}
//		if (cg.getPeople().isFinish()) {
//
//
//		}
//		Sleep(100);
//	}
//}
#pragma endregion