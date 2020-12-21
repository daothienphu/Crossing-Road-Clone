#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>


#include "GameGraphic.h"
#include "Header.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

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
class Will : public Obstacle {};
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
	GameGraphic gph;
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
		while (1)
		{
			//pre-process graphic
			//gph.drawGame();
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

	void gameLogic()
	{
		//intilize player at place
		//intilize obstacles
		while (1)
		{
			//input special case:
				//pause -> lock this thread
				//resume -> release thread
			//check for input -> update pos player
			//check for obstacles properties -> update pos obst
			//collision check
			//if pass -> send signal to check
			//else set flag game over
		}
	}

	//void pause();
	//void resume();
	//void load();
	//void save();

};

#pragma endregion
