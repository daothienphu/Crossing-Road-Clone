#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
#include "Utils.h"
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
		player = new Player(70, 38);
		graphic = new GraphicsController;
	}
	~GameCore() {
		for (int i = 0; i < menuHier.size(); ++i)
			delete menuHier[i];

		delete graphic;
	}

	void start() {
		graphic->charToBlock();
		int tmp = titleScreen();
		graphic->clearBuffer();
		switch (tmp) {
		case 0: playScreen(1); break;
		case 1: loadScreen(); break;
		case 2: settingsScreen(); break;
		case 3: cout << "\n\n\n\n\n\n             How dare you exit our game?\n\n\n\n\n\n"; exit(0);
		default: break;
		}
	}
	int titleScreen() {
		//title
		GameMenu* title = new Button(46, 10, "title");
		graphic->setBuffer(graphic->getBuffer(title->getBufferKey()), 47, 12, 0, 7);
		//4 buttons
		GameMenu* startButton = new Button("start");
		GameMenu* loadButton = new Button("load");
		GameMenu* settingButton = new Button("settings");
		GameMenu* exitButton = new Button("exit");
		
		int choice = 0;
		bool* bKeyGame = new bool[key.size()]{ 0 }; // Check ingame input
		while (1) {
			//delay to slow down the speed
			delay(1000 / (FRAMERATE / 8));
			//default color
			graphic->setBuffer(graphic->getBuffer(startButton->getBufferKey()), 68, 21, 0, 7);
			graphic->setBuffer(graphic->getBuffer(loadButton->getBufferKey()), 68, 22, 0, 7);
			graphic->setBuffer(graphic->getBuffer(settingButton->getBufferKey()), 68, 23, 0, 7);
			graphic->setBuffer(graphic->getBuffer(exitButton->getBufferKey()), 68, 24, 0, 7);

			//input
			for (int i = 0; i < key.size(); i++)
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			if (GetAsyncKeyState(VK_RETURN))
				return choice;
			else if (bKeyGame[0] == 1) {
				choice = (choice + 4 - 1) % 4;
			}
			else if (bKeyGame[2] == 1) {
				choice = (choice + 1) % 4;
			}

			//change color depends on choice
			switch (choice) {
			case 0: 
				graphic->setBuffer(graphic->getBuffer(startButton->getBufferKey()), 68, 21, 7, 0); break;
			case 1: 
				graphic->setBuffer(graphic->getBuffer(loadButton->getBufferKey()), 68, 22, 7, 0); break;
			case 2:
				graphic->setBuffer(graphic->getBuffer(settingButton->getBufferKey()), 68, 23, 7, 0); break;
			case 3:
				graphic->setBuffer(graphic->getBuffer(exitButton->getBufferKey()), 68, 24, 7, 0); break;
			default: break;
			}

			graphic->render();
		}		
	}
	void playScreen(int level)
	{
		GameObject* enemy1 = new Obstacles(20, 5, 10, 4, "enemy1");
		vector<wstring> enemy1Blank{L"          ",L"          " ,L"          " ,L"          " };
		GameObject* enemy2 = new Obstacles(10, 10, 10, 4, "enemy2");
		vector<wstring> enemy2Blank{ L"          ",L"          " ,L"          " ,L"          " };
		GameObject* enemy3 = new Obstacles(30, 15, 10, 4, "enemy3");
		vector<wstring> enemy3Blank{ L"          ",L"          " ,L"          " ,L"          " };
		GameObject* enemy4 = new Obstacles(40, 20, 10, 4, "enemy4");
		vector<wstring> enemy4Blank{ L"          ",L"          " ,L"          " ,L"          " };


		vector<wstring> playerGraphic = graphic->getBuffer(player->getBufferKey());
		int playerHeight = playerGraphic.size();
		int playerWidth = playerGraphic[0].length();
		vector<wstring> playerBlank{ L"  ", L"  " };

		bool* bKeyGame = new bool[key.size()]{ 0 };
		while (1)
		{
			delay(1000/FRAMERATE);
			graphic->setBuffer(playerBlank, this->player->getOldPos().x, this->player->getOldPos().y, 0, 7);
			graphic->setBuffer(playerGraphic, this->player->getPos().x, this->player->getPos().y, 0, 7);

			for (int i = 0; i < key.size(); i++) { 	// Read input
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}
			//W A S D
			if (bKeyGame[0] == 1 && player->getPos().y > 0) {
				player->move(0, -1);
				//Player.moveUp();
			}
			else if (bKeyGame[1] == 1 && player->getPos().x > 0) {
				player->move(-1, 0);
				//Player.moveLeft();
			}
			else if (bKeyGame[2] == 1 && player->getPos().y < screenHeight - playerHeight) {
				player->move(0, 1);
				//Player.moveDown();
			}
			else if (bKeyGame[3] == 1 && player->getPos().x < screenWidth - 1 - playerWidth) {
				player->move(1, 0);
				//Player.moveRight();
			}
			


			graphic->setBuffer(enemy1Blank, enemy1->getOldPos().x, enemy1->getOldPos().y, 0, 7);
			graphic->setBuffer(graphic->getBuffer(enemy1->getBufferKey()), enemy1->getPos().x, enemy1->getPos().y, 0, 7);
			graphic->setBuffer(enemy2Blank, enemy2->getOldPos().x, enemy2->getOldPos().y, 0, 7);
			graphic->setBuffer(graphic->getBuffer(enemy2->getBufferKey()), enemy2->getPos().x, enemy2->getPos().y, 0, 7);
			graphic->setBuffer(enemy3Blank, enemy3->getOldPos().x, enemy3->getOldPos().y, 0, 7);
			graphic->setBuffer(graphic->getBuffer(enemy3->getBufferKey()), enemy3->getPos().x, enemy3->getPos().y, 0, 7);
			graphic->setBuffer(enemy4Blank, enemy4->getOldPos().x, enemy4->getOldPos().y, 0, 7);
			graphic->setBuffer(graphic->getBuffer(enemy4->getBufferKey()), enemy4->getPos().x, enemy4->getPos().y, 0, 7);

			if (enemy1->getPos().x > screenWidth - 1 - graphic->getBuffer(enemy1->getBufferKey())[0].length()) {
				enemy1->resetPos(1);
				graphic->setBuffer(enemy1Blank, enemy1->getOldPos().x, enemy1->getOldPos().y, 0, 7);
			}
			enemy1->move(2, 0);
			if (enemy2->getPos().x < 1) {
				enemy2->resetPos(2, false);
				graphic->setBuffer(enemy2Blank, 0, enemy2->getOldPos().y, 0, 7);
			}
			enemy2->move(-2, 0);
			if (enemy3->getPos().x > screenWidth - 1 - graphic->getBuffer(enemy3->getBufferKey())[0].length()) {
				enemy3->resetPos(3);
				graphic->setBuffer(enemy3Blank, enemy3->getOldPos().x, enemy3->getOldPos().y, 0, 7);
			}
			enemy3->move(2, 0);
			if (enemy4->getPos().x < 1) {
				enemy4->resetPos(4, false);
				graphic->setBuffer(enemy4Blank, 0, enemy4->getOldPos().y, 0, 7);
			}
			enemy4->move(-2, 0);

			graphic->render();
		}

	}
	void loadScreen() {};
	void settingsScreen() {
		
	};
	void pauseScreen() {};
};