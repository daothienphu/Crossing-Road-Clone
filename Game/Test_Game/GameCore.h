#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
#include "GameObject.h"
#include "Player.h"
#include "Obstacles.h"
#include "Items.h"
#include "Menu.h"
#include "GameMenu.h"
#include "GraphicsController.h"

using namespace std;

const vector<char> key = { 'W', 'A', 'S', 'D', 'P', 'R' };

class GameCore {
protected:
	vector<Items*> menuHier; //hierarchy
	GameObject* player;

	GraphicsController* graphic;

public:
	GameCore() {
		player = new Player;
		graphic = new GraphicsController;
	}
	~GameCore() {
		for (int i = 0; i < menuHier.size(); ++i)
			delete menuHier[i];

		delete graphic;
	}

	//void test() { cout << player->getBufferKey().size() << endl; }

	void start() {
		Items* startMenu = new GameMenu;

		//graphic->setBuffer(startMenu.getBufferData(), 0,0,0,7);
	}

	void playScreen(int level)
	{
<<<<<<< Updated upstream
=======
		if (soundOn)
			PlaySound(TEXT("GameSong1.wav"), NULL, SND_FILENAME | SND_ASYNC);
		graphic->clearBuffer();
		player->setPos(72, 2);
		player->clearOldPos(graphic);
		//GameLane* lane1 = new GameLane(1, 1, 1, graphic);
		//GameLane* lane2 = new GameLane(2, 2, 1, graphic);
		//GameLane* lane3 = new GameLane(3, 3, 1, graphic);
		vector<GameLane*> lanes;

		if (Level == 1)
		{
			levelController = new Level_1;
			levelController->getMap(lanes, graphic);
		}

		GameMenu* score = new Button("score");
		GameMenu* level = new Button("level");
		//GameMenu* laneIndex = new Button("score");
		vector<wstring> scoreCounter, levelCounter;

		int num = 0;
		bool* bKeyGame = new bool[key.size()]{ 0 };

>>>>>>> Stashed changes
		while (1)
		{
			graphic->setBuffer(graphic->getBuffer(player->getBufferKey()), this->player->getPos().x, this->player->getPos().y, 0, 7);
			graphic->render();

			bool* bKeyGame = new bool[key.size()]; // Check ingame input
			for (int i = 0; i < key.size(); i++) { 	// Read input
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}
<<<<<<< Updated upstream
			// W - Move up
			if (bKeyGame[0] == 1) {
=======
			if (bKeyGame[4] == 1 || GetAsyncKeyState(VK_ESCAPE)) {
				if (!pauseScreen())
					return Level;
				if (soundOn)
					PlaySound(TEXT("GameSong1.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (bKeyGame[0] == 1 && player->getPos().y > 1) {
>>>>>>> Stashed changes
				player->move(0, -1);
				//Player.moveUp();
			}
			// A - Move left
			if (bKeyGame[1] == 1) {
				player->move(-1, 0);
				//Player.moveLeft();
			}
			// S - Move down
			if (bKeyGame[2] == 1) {
				player->move(0, 1);
				//Player.moveDown();
			}
			// D - Move right
			if (bKeyGame[3] == 1) {
				player->move(1, 0);
				//Player.moveRight();
			}
		}
	}

	void pauseScreen() {};
};