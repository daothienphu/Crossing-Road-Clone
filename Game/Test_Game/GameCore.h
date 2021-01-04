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
		graphic = new GraphicsController;
		player = new Player(70, 38, graphic);
	}
	~GameCore() {
		for (int i = 0; i < menuHier.size(); ++i)
			delete menuHier[i];

		delete graphic;
	}

	void start() {
		int tmp = titleScreen();
		graphic->clearBuffer();
		switch (tmp) {
		case 0: playScreen(1); break;
		case 1: loadScreen(); break;
		//setting screen is included in titleScreen
		//exit screen is included in titleScreen
		default: break;
		}
	}
	int titleScreen() {
		//title
		GameMenu* title = new Button(46, 10, "title");
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

			//has to put here instead of outside the loop due to after the settingsScreen() return.
			graphic->setBuffer(graphic->getBuffer(title->getBufferKey()), 46, 12, 0, 7);

			//default color
			graphic->setBuffer(graphic->getBuffer(startButton->getBufferKey()), 68, 21, 0, 7);
			graphic->setBuffer(graphic->getBuffer(loadButton->getBufferKey()), 68, 22, 0, 7);
			graphic->setBuffer(graphic->getBuffer(settingButton->getBufferKey()), 68, 23, 0, 7);
			graphic->setBuffer(graphic->getBuffer(exitButton->getBufferKey()), 68, 24, 0, 7);

			//input
			for (int i = 0; i < key.size(); i++)
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			if (GetAsyncKeyState(VK_RETURN)) {
				if (choice == 2)
					settingsScreen();
				else if (choice == 3)
					exitScreen();
				else return choice;
			}
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
	void playScreen(int Level)
	{
		Obstacles* enemy1 = new Obstacles(20, 5, 2, 0, 1, "enemy1", graphic);
		Obstacles* enemy2 = new Obstacles(10, 10, 3, 0, 3, "enemy2", graphic);
		Obstacles* enemy3 = new Obstacles(30, 15, 2, 0, 4, "enemy3", graphic);
		Obstacles* enemy4 = new Obstacles(40, 20, 3, 0, 6, "enemy4", graphic);

		GameMenu* score = new Button("score");
		GameMenu* level = new Button("level");
		vector<wstring> scoreCounter, levelCounter;


		vector<wstring> playerGraphic = graphic->getBuffer(player->getBufferKey());
		int playerHeight = playerGraphic.size();
		int playerWidth = playerGraphic[0].length();
		vector<wstring> playerBlank{ L"  ", L"  " };


		int num = 0;
		bool* bKeyGame = new bool[key.size()]{ 0 };
		while (1)
		{
			delay(1000/(FRAMERATE - 20));
			player->render(graphic, 0, 7);

			for (int i = 0; i < key.size(); i++) { 	// Read input
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}
			if (bKeyGame[4] == 1 || GetAsyncKeyState(VK_ESCAPE))
				pauseScreen();
			//W A S D
			else if (bKeyGame[0] == 1 && player->getPos().y > 0) {
				player->move(0, -1, graphic);
				//Player.moveUp();
			}
			else if (bKeyGame[1] == 1 && player->getPos().x > 0) {
				player->move(-1, 0, graphic);
				//Player.moveLeft();
			}
			else if (bKeyGame[2] == 1 && player->getPos().y < screenHeight - 1 - playerHeight) {
				player->move(0, 1, graphic);
				//Player.moveDown();
			}
			else if (bKeyGame[3] == 1 && player->getPos().x < screenWidth - 1 - playerWidth) {
				player->move(1, 0, graphic);
				//Player.moveRight();
			}
			

			toVwstring(num++, scoreCounter);
			toVwstring(Level, levelCounter);
			graphic->setBuffer(graphic->getBuffer(score->getBufferKey()), 2, 1, 0, 7);
			graphic->setBuffer(scoreCounter, 9, 1, 0, 7);
			graphic->setBuffer(graphic->getBuffer(level->getBufferKey()), 2, 2, 0, 7);
			graphic->setBuffer(levelCounter, 9, 2, 0, 7);


			/*graphic->setBuffer(enemy1Blank, enemy1->getOldPos().x, enemy1->getOldPos().y, 0, 7);
			graphic->setBuffer(graphic->getBuffer(enemy1->getBufferKey()), enemy1->getPos().x, enemy1->getPos().y, 0, 1);
			graphic->setBuffer(enemy2Blank, enemy2->getOldPos().x, enemy2->getOldPos().y, 0, 7);
			graphic->setBuffer(graphic->getBuffer(enemy2->getBufferKey()), enemy2->getPos().x, enemy2->getPos().y, 0, 3);
			graphic->setBuffer(enemy3Blank, enemy3->getOldPos().x, enemy3->getOldPos().y, 0, 7);
			graphic->setBuffer(graphic->getBuffer(enemy3->getBufferKey()), enemy3->getPos().x, enemy3->getPos().y, 0, 4);
			graphic->setBuffer(enemy4Blank, enemy4->getOldPos().x, enemy4->getOldPos().y, 0, 7);
			graphic->setBuffer(graphic->getBuffer(enemy4->getBufferKey()), enemy4->getPos().x, enemy4->getPos().y, 0, 6);*/
			enemy1->render(graphic);
			enemy2->render(graphic);
			enemy3->render(graphic);
			enemy4->render(graphic);

			enemy1->move(2, 0, graphic);
			enemy2->move(-2, 0, graphic);
			enemy3->move(2, 0, graphic);
			enemy4->move(-2, 0, graphic);

			if (enemy1->getPos().x >= screenWidth - 1 - graphic->getBuffer(enemy1->getBufferKey())[0].length()) {
				enemy1->clearOldPos(graphic);
				enemy1->resetPos(1, graphic);
			}

			if (enemy2->getPos().x <= 1) {
				enemy2->clearOldPos(graphic);
				enemy2->resetPos(2, graphic, false);
			}

			if (enemy3->getPos().x >= screenWidth - 1 - graphic->getBuffer(enemy3->getBufferKey())[0].length()) {
				enemy3->clearOldPos(graphic);
				enemy3->resetPos(3, graphic);
			}
			
			if (enemy4->getPos().x <= 1) {
				enemy4->clearOldPos(graphic);
				enemy4->resetPos(4, graphic, false);
			}
			

			graphic->render();
		}

	}
	void loadScreen() {};
	void settingsScreen() {
		graphic->clearBuffer();
		GameMenu* settingsTitle = new Button("settingsTitle");
		graphic->setBuffer(graphic->getBuffer(settingsTitle->getBufferKey()), 64, 19, 0, 7);

		GameMenu* backButton = new Button("back");
		GameMenu* soundButton = new Button("sound");
		GameMenu* on = new Button("on");
		GameMenu* off = new Button("off");


		int choice = 0; bool soundOn = true;
		bool* bKeyGame = new bool[key.size()]{ 0 }; // Check ingame input
		while (1) {
			//delay to slow down the speed
			delay(1000 / (FRAMERATE / 8));
			//default color
			graphic->setBuffer(graphic->getBuffer(soundButton->getBufferKey()), 68, 21, 0, 7);
			if (soundOn)
				graphic->setBuffer(graphic->getBuffer(on->getBufferKey()), 74, 21, 0, 7);
			else
				graphic->setBuffer(graphic->getBuffer(off->getBufferKey()), 74, 21, 0, 7);
			graphic->setBuffer(graphic->getBuffer(backButton->getBufferKey()), 68, 22, 0, 7);

			//input
			for (int i = 0; i < key.size(); i++)
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			if (GetAsyncKeyState(VK_RETURN)) {
				if (choice == 0) {
					soundOn = !soundOn;
					//sound stuff hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
				}
				else {
					graphic->clearBuffer();
					return;
				}
			}
			else if (bKeyGame[0] == 1) {
				choice = (choice + 2 - 1) % 2;
			}
			else if (bKeyGame[2] == 1) {
				choice = (choice + 1) % 2;
			}

			//change color depends on choice
			switch (choice) {
			case 0:
				graphic->setBuffer(graphic->getBuffer(soundButton->getBufferKey()), 68, 21, 7, 0); 
				if (soundOn)
					graphic->setBuffer(graphic->getBuffer(on->getBufferKey()), 74, 21, 7, 0);
				else
					graphic->setBuffer(graphic->getBuffer(off->getBufferKey()), 74, 21, 7, 0);
				break;
			case 1:
				graphic->setBuffer(graphic->getBuffer(backButton->getBufferKey()), 68, 22, 7, 0); break;
			default: break;
			}

			graphic->render();
		}
	};
	void pauseScreen() {
		graphic->clearBuffer();
		GameMenu* pauseTitle = new Button("pauseTitle");
		graphic->setBuffer(graphic->getBuffer(pauseTitle->getBufferKey()), 64, 17, 0, 7);


		GameMenu* resumeButton = new Button("resumeButton");
		GameMenu* restartButton = new Button("restartButton");
		GameMenu* backButton = new Button("back");
		GameMenu* soundButton = new Button("sound");
		GameMenu* on = new Button("on");
		GameMenu* off = new Button("off");


		int choice = 0; bool soundOn = true;
		bool* bKeyGame = new bool[key.size()]{ 0 }; // Check ingame input
		while (1) {
			//delay to slow down the speed
			delay(1000 / (FRAMERATE / 8));
			//default color
			graphic->setBuffer(graphic->getBuffer(resumeButton->getBufferKey()), 68, 19, 0, 7);
			graphic->setBuffer(graphic->getBuffer(restartButton->getBufferKey()), 68, 20, 0, 7);
			graphic->setBuffer(graphic->getBuffer(soundButton->getBufferKey()), 68, 21, 0, 7);
			if (soundOn)
				graphic->setBuffer(graphic->getBuffer(on->getBufferKey()), 74, 21, 0, 7);
			else
				graphic->setBuffer(graphic->getBuffer(off->getBufferKey()), 74, 21, 0, 7);

			//input
			for (int i = 0; i < key.size(); i++)
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			if (GetAsyncKeyState(VK_RETURN)) {
				if (choice == 2) {
					soundOn = !soundOn;
					//sound stuff hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
				}
				else if (choice == 0){
					graphic->clearBuffer();
					return;
				}
				else {
					return; //restart game hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
				}
			}
			else if (bKeyGame[0] == 1) {
				choice = (choice + 3 - 1) % 3;
			}
			else if (bKeyGame[2] == 1) {
				choice = (choice + 1) % 3;
			}

			//change color depends on choice
			switch (choice) {
			case 0:
				graphic->setBuffer(graphic->getBuffer(resumeButton->getBufferKey()), 68, 19, 7, 0); break;
			case 1:
				graphic->setBuffer(graphic->getBuffer(restartButton->getBufferKey()), 68, 20, 7, 0); break;
			case 2:
				graphic->setBuffer(graphic->getBuffer(soundButton->getBufferKey()), 68, 21, 7, 0);
				if (soundOn)
					graphic->setBuffer(graphic->getBuffer(on->getBufferKey()), 74, 21, 7, 0);
				else
					graphic->setBuffer(graphic->getBuffer(off->getBufferKey()), 74, 21, 7, 0);
				break;
			default: break;
			}

			graphic->render();
		}
	};
	void exitScreen() {
		graphic->clearBuffer();
		GameMenu* exitTitle = new Button("exitTitle");
		graphic->setBuffer(graphic->getBuffer(exitTitle->getBufferKey()), 46, 20, 0, 7);
		graphic->render();
		while (1) {
			delay(1000 / (FRAMERATE / 10));
			if (GetAsyncKeyState(VK_RETURN))
				exit(0);
		}
	}
};