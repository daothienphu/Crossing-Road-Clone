#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>


#include "GameGraphic.h"
#include "Header.h"
#include "GameObject.h"
#include "Player.h"
#include "GameObstacles.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

#pragma region GameCore

class GameCore {
private:
	GAMESTATE state;
	GameGraphic gph;
	int level;
	//will need more param
public:
	GameCore(GAMESTATE state = GAMESTATE::PLAYING);
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

		delete[] bKey;
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

		delete player;
		//delete obstacles too
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
