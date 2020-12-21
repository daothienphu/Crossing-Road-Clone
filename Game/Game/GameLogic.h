#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>


#include "GameGraphic.h"
#include "Header.h"

#pragma region GAME CONFIG

#define PLAYER_H 50
#define PLAYER_W 50

#pragma endregion

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

	void move(int x, int y)
	{
		this->x += x;
		this->y += y;
	}
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
	Player(int x, int y, int w = PLAYER_W, int h = PLAYER_H) : GameObject(x, y, w, h, 0) {}
	void render();
};
#pragma endregion

#pragma region GameCore

class GameCore {
private:
	GAMESTATE state;
	GameGraphic gph;
	int level;
	int currentInput;
	//will need more param
public:
	void start()
	{
		thread t1(&GameCore::draw, this);
		thread t2(&GameCore::gameLogic, this);

		t1.join();
		t2.join();
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
	void inputChecking(GameObject* &player)
	{
		const vector<char> key = { 'W', 'A', 'S', 'D' };

		// INPUT
		bool* bKey = new bool[key.size()];
		// Read input
		for (int i = 0; i < key.size(); i++) {
			bKey[i] = (GetAsyncKeyState(key.at(i))) != 0;
		}
		// Move up
		if (bKey[0] == 1) {
			player->move(0, -1);
		}
		// Move down
		if (bKey[2] == 1) {
			player->move(0, 1);
		}
		// Move left
		if (bKey[1] == 1) {
			player->move(-1, 0);
		}
		// Move right
		if (bKey[3] == 1) {
			player->move(1, 0);
		}
	}

	void gameLogic()
	{
		//intilize player at place
		//intilize obstacles
		GameObject* player = new Player(50, 40);
		vector<vector<GameObject*>> obs;
		this->initObstacles(level, obs);
		while (1)
		{
			inputChecking(player);
			//input special case:
				//pause -> break the game render -> render menu
				//resume -> break the menu render -> render game
			//check for input -> update pos player
			//check for obstacles properties -> update pos obst
			//collision check
			//if pass -> send signal to check
			//else set flag game over
		}
	}

	void initObstacles(int level, vector<vector<GameObject*>> & obs)
	{
		while (level--)
		{
			//something to generate
		}
	}
	

	//void pause();
	//void resume();
	//void load();
	//void save();

};

#pragma endregion
