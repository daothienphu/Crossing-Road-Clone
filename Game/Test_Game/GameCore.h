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
	GameObject* player;
	GraphicsController* graphic;
public:
	GameCore() {
		graphic = new GraphicsController;
		player = new Player(70, 37, graphic);
		srand(time(0));
	}
	~GameCore() {
		delete graphic;
		delete player;
	}

	void start() {
		introScreen();
		titleScreen();
	}
	void introScreen() {
#pragma region intro
		GameMenu* intro = new Button("intro");
		delay(500);
		/*graphic->setBuffer(graphic->getBuffer(intro->getBufferKey()), 10, 3, black, blueDark);
		graphic->render();
		delay(50);
		graphic->setBuffer(graphic->getBuffer(intro->getBufferKey()), 10, 3, black, blueLight);
		graphic->render();
		delay(75);
		graphic->setBuffer(graphic->getBuffer(intro->getBufferKey()), 10, 3, black, blueDark);
		graphic->render();
		delay(25);*/
		graphic->setBuffer(graphic->getBuffer(intro->getBufferKey()), 21, 10, black, blueLight);
		graphic->render();
#pragma endregion
		delay(1000);
#pragma region loading bar, cuz why not
		graphic->createFrame(30, 23, 85, 3);
		for (int i = 1; i < 82; ++i) {
			vector<wstring> tmp = { L"█" };
			graphic->setBuffer(tmp, 31 + i, 24, black, whiteDark);
			graphic->render();
			delay(83 - i);
		}
		vector<wstring> tmp = { L"PRESS ENTER TO CONTINUE" };
		graphic->setBuffer(tmp, 58, 27, black, whiteDark);
		graphic->render();
#pragma endregion
		while (!GetAsyncKeyState(VK_RETURN)) { ; }
		graphic->clearBuffer();
	}
	void titleScreen() {
		GameMenu* title = new Button(46, 8, "title");
		GameMenu* startButton = new Button("start");
		GameMenu* loadButton = new Button("load");
		GameMenu* settingButton = new Button("settings");
		GameMenu* exitButton = new Button("exit");
		Obstacles* enemy1 = new Obstacles(20, 5, 9, black, 1, "enemy1", graphic);
		Obstacles* enemy2 = new Obstacles(10, 25, 8, black, 3, "enemy2", graphic);
		Obstacles* enemy3 = new Obstacles(30, 30, 10, black, 4, "enemy3", graphic);
		Obstacles* enemy4 = new Obstacles(40, 35, 7, black, 6, "enemy4", graphic);
		
		int choice = 0;
		bool* bKeyGame = new bool[key.size()]{ 0 };
		
		while (1) {
			//slow down the speed for "sensible" input
			delay(1000 / (FRAMERATE / 6));
			graphic->clearStars();

#pragma region input
			for (int i = 0; i < key.size(); i++)
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			if (GetAsyncKeyState(VK_RETURN)) {
				if (choice == 0)
					playScreen(1);
				else if (choice == 1)
					loadScreen();
				else if (choice == 2)
					settingsScreen();
				else
					exitScreen();
			}
			else if (bKeyGame[0] == 1) {
				choice = (choice + 4 - 1) % 4;
			}
			else if (bKeyGame[2] == 1) {
				choice = (choice + 1) % 4;
			}
#pragma endregion

#pragma region enemies and stars
			graphic->randomStars();

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
				enemy2->resetPos(5, graphic, false);
			}
			if (enemy3->getPos().x >= screenWidth - 1 - graphic->getBuffer(enemy3->getBufferKey())[0].length()) {
				enemy3->clearOldPos(graphic);
				enemy3->resetPos(6, graphic);
			}
			if (enemy4->getPos().x <= 1) {
				enemy4->clearOldPos(graphic);
				enemy4->resetPos(7, graphic, false);
			}
#pragma endregion

			//default color
			graphic->setBufferWhite(graphic->getBuffer(title->getBufferKey()), 46, 11, black, whiteDark);
			graphic->setBuffer(graphic->getBuffer(startButton->getBufferKey()), 68, 20, black, whiteDark);
			graphic->setBuffer(graphic->getBuffer(loadButton->getBufferKey()), 68, 21, black, whiteDark);
			graphic->setBuffer(graphic->getBuffer(settingButton->getBufferKey()), 68, 22, black, whiteDark);
			graphic->setBuffer(graphic->getBuffer(exitButton->getBufferKey()), 68, 23, black, whiteDark);

			//change color depends on choice
			switch (choice) {
			case 0: 
				graphic->setBuffer(graphic->getBuffer(startButton->getBufferKey()), 68, 20, whiteDark, black); break;
			case 1: 
				graphic->setBuffer(graphic->getBuffer(loadButton->getBufferKey()), 68, 21, whiteDark, black); break;
			case 2:
				graphic->setBuffer(graphic->getBuffer(settingButton->getBufferKey()), 68, 22, whiteDark, black); break;
			case 3:
				graphic->setBuffer(graphic->getBuffer(exitButton->getBufferKey()), 68, 23, whiteDark, black); break;
			default: break;
			}

			graphic->render();
		}		
	}
	void playScreen(int Level)
	{
		graphic->clearBuffer();
		Obstacles* enemy1 = new Obstacles(20, 5, 2, black, 1, "enemy1", graphic);
		Obstacles* enemy2 = new Obstacles(10, 10, 3, black, 3, "enemy2", graphic);
		Obstacles* enemy3 = new Obstacles(30, 15, 2, black, 4, "enemy3", graphic);
		Obstacles* enemy4 = new Obstacles(40, 20, 3, black, 6, "enemy4", graphic);

		GameMenu* score = new Button("score");
		GameMenu* level = new Button("level");
		vector<wstring> scoreCounter, levelCounter;

		int num = 0;
		bool* bKeyGame = new bool[key.size()]{ 0 };

		while (1)
		{
			delay(1000/(FRAMERATE - 20));
			graphic->clearStars();
			player->render(graphic, black, 7);

#pragma region Controls
			for (int i = 0; i < key.size(); i++) { 	// Read input
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}
			if (bKeyGame[4] == 1 || GetAsyncKeyState(VK_ESCAPE))
				pauseScreen();
			else if (bKeyGame[0] == 1 && player->getPos().y > 0) {
				player->move(0, -1, graphic);
			}
			else if (bKeyGame[1] == 1 && player->getPos().x > 0) {
				player->move(-1, 0, graphic);
			}
			else if (bKeyGame[2] == 1 && player->getPos().y < screenHeight - 2 - graphic->getBuffer(player->getBufferKey()).size()) {
				player->move(0, 1, graphic);
			}
			else if (bKeyGame[3] == 1 && player->getPos().x < screenWidth - 1 - graphic->getBuffer(player->getBufferKey())[0].length()) {
				player->move(1, 0, graphic);
			}
#pragma endregion

			graphic->randomStars();

#pragma region Score and Level
			toVwstring(num++, scoreCounter);
			toVwstring(Level, levelCounter);
			graphic->setBuffer(graphic->getBuffer(score->getBufferKey()), 2, 1, black, 7);
			graphic->setBuffer(scoreCounter, 9, 1, black, 7);
			graphic->setBuffer(graphic->getBuffer(level->getBufferKey()), 2, 2, black, 7);
			graphic->setBuffer(levelCounter, 9, 2, black, 7);
#pragma endregion

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
			
			graphic->createFrame(0, 0, 145, 40);
			graphic->render();
		}

	}
	void loadScreen() {};
	void settingsScreen() {
		int top = 19;
		int left = 58;
		graphic->openFrame(left, top, 28, 8);
		GameMenu* settingsTitle = new Button("settingsTitle");
		graphic->setBufferWhite(graphic->getBuffer(settingsTitle->getBufferKey()), left + 1, top + 2, 0, 7);

		GameMenu* backButton = new Button("back");
		GameMenu* soundButton = new Button("sound");
		GameMenu* on = new Button("on");
		GameMenu* off = new Button("off");


		int choice = 0; bool soundOn = true;
		bool* bKeyGame = new bool[key.size()]{ 0 }; // Check ingame input
		while (1) {
			delay(1000 / (FRAMERATE / 8));

			//default color
			graphic->setBuffer(graphic->getBuffer(soundButton->getBufferKey()), left + 9, top + 4, 0, 7);
			if (soundOn)
				graphic->setBuffer(graphic->getBuffer(on->getBufferKey()), left + 9 + 6, top + 4, 0, 7);
			else
				graphic->setBuffer(graphic->getBuffer(off->getBufferKey()), left + 9 + 6, top + 4, 0, 7);
			graphic->setBuffer(graphic->getBuffer(backButton->getBufferKey()), left + 9, top + 5, 0, 7);

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
				graphic->setBuffer(graphic->getBuffer(soundButton->getBufferKey()), left + 9, top + 4, 7, 0);
				if (soundOn)
					graphic->setBuffer(graphic->getBuffer(on->getBufferKey()), left + 9 + 6, top + 4, 7, 0);
				else
					graphic->setBuffer(graphic->getBuffer(off->getBufferKey()), left + 9 + 6, top + 4, 7, 0);
				break;
			case 1:
				graphic->setBuffer(graphic->getBuffer(backButton->getBufferKey()), left + 9, top + 5, 7, 0); break;
			default: break;
			}

			graphic->render();
		}
	};
	void pauseScreen() {
		int top = 15;
		int left = 60;
		graphic->openFrame(left, top, 25, 10);
		GameMenu* pauseTitle = new Button("pauseTitle");
		graphic->setBufferWhite(graphic->getBuffer(pauseTitle->getBufferKey()), left + 1, top + 2, 0, 7);


		GameMenu* resumeButton = new Button("resumeButton");
		GameMenu* restartButton = new Button("restartButton");
		GameMenu* saveButton = new Button("saveButton");
		GameMenu* soundButton = new Button("sound");
		GameMenu* on = new Button("on");
		GameMenu* off = new Button("off");


		int choice = 0; bool soundOn = true;
		bool* bKeyGame = new bool[key.size()]{ 0 }; // Check ingame input
		while (1) {
			delay(1000 / (FRAMERATE / 8));
			//default color
			graphic->setBuffer(graphic->getBuffer(resumeButton->getBufferKey()), left + 7, top + 4, 0, 7);
			graphic->setBuffer(graphic->getBuffer(restartButton->getBufferKey()), left + 7, top + 5, 0, 7);
			graphic->setBuffer(graphic->getBuffer(saveButton->getBufferKey()), left + 7, top + 6, 0, 7);
			graphic->setBuffer(graphic->getBuffer(soundButton->getBufferKey()), left + 7, top + 7, 0, 7);
			if (soundOn)
				graphic->setBuffer(graphic->getBuffer(on->getBufferKey()), left + 13, top + 7, 0, 7);
			else
				graphic->setBuffer(graphic->getBuffer(off->getBufferKey()), left + 13, top + 7, 0, 7);

			//input
			for (int i = 0; i < key.size(); i++)
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			if (GetAsyncKeyState(VK_RETURN)) {
				if (choice == 3) {
					soundOn = !soundOn;
					//sound stuff hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
				}
				else if (choice == 0){
					graphic->clearBuffer();
					return;
				}
				else if (choice == 2) {
					//save stuff hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
					return;
				}
				else {
					return; //restart game hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
				}
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
				graphic->setBuffer(graphic->getBuffer(resumeButton->getBufferKey()), left + 7, top + 4, 7, 0); break;
			case 1:
				graphic->setBuffer(graphic->getBuffer(restartButton->getBufferKey()), left + 7, top + 5, 7, 0); break;
			case 2:
				graphic->setBuffer(graphic->getBuffer(saveButton->getBufferKey()), left + 7, top + 6, 7, 0); break;
			case 3:
				graphic->setBuffer(graphic->getBuffer(soundButton->getBufferKey()), left + 7, top + 7, 7, 0);
				if (soundOn)
					graphic->setBuffer(graphic->getBuffer(on->getBufferKey()), left + 13, top + 7, 7, 0);
				else
					graphic->setBuffer(graphic->getBuffer(off->getBufferKey()), left + 13, top + 7, 7, 0);
				break;
			default: break;
			}

			graphic->render();
		}
	};
	void exitScreen() {
		graphic->clearBuffer();
		GameMenu* exitTitle = new Button("exitTitle");
		graphic->setBuffer(graphic->getBuffer(exitTitle->getBufferKey()), 46, 19, black, 7);
		graphic->render();
		while (1) {
			delay(1000 / (FRAMERATE / 10));
			if (GetAsyncKeyState(VK_RETURN))
				exit(0);
		}
	}
};
