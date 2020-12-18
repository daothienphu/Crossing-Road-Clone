#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>

#pragma region game config

#define GAME_RATE 50
enum GAMESTATE {PLAYING, PAUSE, EXIT};
enum DIRECTION { LEFT, RIGHT };
#pragma endregion

#pragma region Define Colors
#define halfup "\xdf"
#define halfdown "\xdc"
#define whole "\xdb"

#define black50 "\x1B[30m"
#define red50 "\x1B[31m"
#define green50 "\x1B[32m"
#define yellow50 "\x1B[33m"
#define blue50 "\x1B[34m"
#define magenta50 "\x1B[35m"
#define cyan50 "\x1B[36m"
#define white50 "\x1B[37m"

#define blackBG50 "\x1B[40m"
#define redBG50 "\x1B[41m"
#define greenBG50 "\x1B[42m"
#define yellowBG50 "\x1B[43m"
#define blueBG50 "\x1B[44m"
#define magentaBG50 "\x1B[45m"
#define cyanBG50 "\x1B[46m"
#define whiteBG50 "\x1B[47m"

#define black "\x1B[90m"
#define red "\x1B[91m"
#define green "\x1B[92m"
#define yellow "\x1B[93m"
#define blue "\x1B[94m"
#define magenta "\x1B[95m"
#define cyan "\x1B[96m"
#define white "\x1B[97m"

#define blackBG "\x1B[100m"
#define redBG "\x1B[101m"
#define greenBG "\x1B[102m"
#define yellowBG "\x1B[103m"
#define blueBG "\x1B[104m"
#define magentaBG "\x1B[105m"
#define cyanBG "\x1B[106m"
#define whiteBG "\x1B[107m"
#pragma endregion
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

#pragma region Util
void fixSizedConsoleWindow();
void gotoXY(int x, int y);
void printPalette();
bool delay(int millisec) {
	sleep_for(milliseconds(millisec));
	return true;
}

#pragma endregion

#pragma region GameObject

class GameObject {
private:
protected:
	int x, y; // coordinate of bottom-left corner
	int w, h; // box size
	int row;  // path number for checking collision
public:
	GameObject() : x(0), y(0), w(0), h(0), row(0) {}
	GameObject(int x, int y, int w, int h, int row) : x(x), y(y), w(w), h(h), row(0) {}

	virtual void move() = 0;
	virtual void render() = 0;
	//virtual void collision() = 0;
};

class Obstacle : public GameObject {
private:
protected:
	int veclocity;
	DIRECTION direction; // may need a direction
public:
	Obstacle() : GameObject(), veclocity(0), direction(DIRECTION::RIGHT) {}
	Obstacle(int x, int y, int w, int h, int row, int veclocity, DIRECTION direction = DIRECTION::RIGHT) 
		: GameObject(x, y, w, h, row), veclocity(veclocity), direction(direction) {}

	void move();
	void render() = 0;
	//void collision();
};

#pragma region Obstacles
class Something : public Obstacle {};
class Will: public Obstacle {};
class BeDefineLater : public Obstacle {};
#pragma endregion

class Player : public GameObject {
private:
protected:
public:
	Player() : GameObject() {}
	Player(int x, int y, int w, int h) : GameObject(x, y, w, h, 0) {}
	void move();
	void render();
};
#pragma endregion

#pragma region GameCore

class GameCore {
private:
	GAMESTATE state;
	GameGraphic graphic;
	int level;
	//will need more param
public:
	void start()
	{
		thread t1(&GameCore::draw, this);
		thread t2(&GameCore::inputChecking, this);
		thread t3(&GameCore::gameLogic, this);

		t1.join();
		t2.join();
		t3.join();
	}
	void draw()
	{
		//check game state
		while(1)
		{
			//pre-process graphic
			graphic.drawGame();
			delay(GAME_RATE);
		}
	}
	void inputChecking()
	{
		while (1)
		{
			//check for input
			delay(50);
		}
	}
	void gameLogic();

	void pause();
	void resume();
	//void load();
	//void save();

};

#pragma endregion

#pragma region GameGraphic

class GameGraphic
{
private:
	//list of param
public:
	void drawGame();
};

#pragma endregion 