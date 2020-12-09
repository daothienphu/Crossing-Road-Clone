#include <iostream>
#include <WinUser.h> //GetWindowLong(), GWL_STYLE, WL_MAXIMIZEBOX...
#include <consoleapi3.h> //GetConsoleWindow()
#include <consoleapi2.h> //SetConsoleCursorPosition
#include <WinBase.h> //GetStdHandle, STD_OUTPUT_HANDLE
#include <Windows.h>
using namespace std;

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

class CPEOPLE {
	int mX, mY;
	bool mState;
public:
	CPEOPLE();
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	bool isImpact(const CVEHICLE*&);
	bool isImpact(const CANIMAL*&);
	bool isFinish();
	bool isDead();
};
class CVEHICLE {
	int mX, mY;
public:
	virtual void Move(int, int);
	//...
};
class CTRUCK : public CVEHICLE {
public:
	//...
};
class CCAR : public CVEHICLE {
public:
	//...
};
class CANIMAL {
	int mX, mY;
public:
	virtual void Move(int, int);
	virtual void Tell();
};
class CDINOSAUR : public CANIMAL {
public:
	//...
};
class CBIRD : public CANIMAL {
public:
	//...
};

class CGAME {
	CTRUCK* axt;
	CCAR* axh;
	CDINOSAUR* akl;
	CBIRD* ac;
	CPEOPLE cn;
public:
	CGAME();
	void drawGame();
	~CGAME();
	CPEOPLE getPeople();
	CVEHICLE* getVehicle();
	CANIMAL* getAnimal();
	void resetGame();
	void exitGame(HANDLE);
	void startGame();
	void loadGame(istream);
	void saveGame(istream);
	void pauseGame(HANDLE);
	void resumeGame(HANDLE);
	void updatePosPeople(char);
	void updatePosVehicle();
	void updatePosAnimal();
}



char MOVING;
CGAME cg;

void SubThread()
{
	while (IS_RUNNING) {
		if (!cg.getPeople().isDead())
		{
			cg.updatePosPeople(MOVING);

		}
		MOVING = ' ';
		cg.updatePosVehicle();
		cg.updatePosAnimal();
		cg.drawGame();
		if (cg.getPeople().isImpact(cg.getVehicle() ||
			cg.getPeople().isImpact(cg.getAnimal())
		{

		}
		if (cg.getPeople().isFinish()) {


		}
		Sleep(100);
	}
}


void main()
{

	cg = new CGAME();
	int temp;
	FixConsoleWindow();
	cg.startGame();
	thread t1(SubThread);
	while (1)
	{
		temp = toupper(getch());
		if (!cg.getPeople().isDead())
		{
			if (temp == 27) {
				cg.exitGame(t1.native_handle());
				return;

			}
			else if (temp == 'P') {
				cg.pauseGame(t1.native_handle());

			}
			else {
				cg.resumeGame((HANDLE)t1.native_handle());
				MOVING = temp;

			}
		}
		else
		{
			if (temp == 'Y') cg.startGame();
			else {
				cg.exitGame(t1.native_handle());
				return;

			}
		}
	}

}



//"multithread"

//void exitGame(thread* t) {
//	 system(“cls”);
//	 IS_RUNNING = false;
//	 t->join();
//}
//void ThreadFunc1() {
//	while (IS_RUNNING) {
//	}
//}
//void main() {
//	...
//	thread t1(ThreadFunc1); //parallel thread
//	while (1) {
//		int temp = toupper(getch());
//		...
//		if (temp == 27) {// esc
//			exitGame(&t1); return;
//
//		}
//		...
//
//	}
//}


