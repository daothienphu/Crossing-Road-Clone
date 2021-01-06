#pragma once
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
#include "Utils.h"
#include "GameObject.h"
#include "Player.h"
#include "Obstacles.h"
#include "GameLane.h"
#include "Items.h"
#include "Menu.h"
#include "GameMenu.h"
#include "GraphicsController.h"

using namespace std;

const vector<char> key = { 'W', 'A', 'S', 'D', 'P', 'R' };

class GameCore {
protected:
	Player* player;
	GraphicsController* graphic;
	bool soundOn = true;
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
		graphic->createFrame(0, 0, 145, 40);

		//intro
		GameMenu* intro = new Button("intro");
		delay(500);
		/*graphic->setBuffer(graphic->getBuffer(intro->getBufferKey()), 10, 3, BG, blueDark);
		graphic->render();
		delay(50);
		graphic->setBuffer(graphic->getBuffer(intro->getBufferKey()), 10, 3, BG, blueLight);
		graphic->render();
		delay(75);
		graphic->setBuffer(graphic->getBuffer(intro->getBufferKey()), 10, 3, BG, blueDark);
		graphic->render();
		delay(25);*/
		graphic->setBuffer(graphic->getBuffer(intro->getBufferKey()), 21, 10, BG, blueLight);
		graphic->render();

		delay(500);

		//loading bar, cuz why not
		graphic->createFrame(30, 23, 85, 3);
		for (int i = 1; i < 82; ++i) {
			vector<wstring> tmp = { L"█" };
			graphic->setBuffer(tmp, 31 + i, 24, BG, whiteDark);
			graphic->render();
			delay(83 - i);
		}
		vector<wstring> tmp = { L"PRESS ENTER TO CONTINUE" };
		graphic->setBuffer(tmp, 58, 27, BG, whiteDark);
		graphic->render();

		int count = 0;
		while (!GetAsyncKeyState(VK_RETURN)) {
			delay(1000 / FRAMERATE);
			count++;
			if (count == 480) {
				GameMenu* easterEgg1 = new Button("easterEgg1");
				graphic->setBuffer(graphic->getBuffer(easterEgg1->getBufferKey()), 28, 29, BG, 7);
				graphic->render();
			}
		}
		graphic->clearBuffer();
	}
	void titleScreen() {
		GameMenu* title = new Button(46, 8, "title");
		GameMenu* startButton = new Button("start");
		GameMenu* loadButton = new Button("load");
		GameMenu* settingButton = new Button("settings");
		GameMenu* exitButton = new Button("exit");
		Obstacles* enemy1 = new Obstacles(20, 5, 1, BG, 1, "enemy1", graphic);
		Obstacles* enemy2 = new Obstacles(135, 25, 2, BG, 3, "enemy2", graphic);
		Obstacles* enemy3 = new Obstacles(30, 30, 2, BG, 4, "enemy3", graphic);
		Obstacles* enemy4 = new Obstacles(115, 35, 3, BG, 6, "enemy4", graphic);

		int choice = 0;
		bool* bKeyGame = new bool[key.size()]{ 0 };
		if (soundOn)
			PlaySound(TEXT("intro.wav"), NULL, SND_ASYNC);
		while (1) {
			
			//slow down the speed for "sensible" input
			delay(1000 / (FRAMERATE / 6));
			graphic->clearStars();

			//input
			for (int i = 0; i < key.size(); i++)
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			if (GetAsyncKeyState(VK_RETURN)) {
				if (soundOn)
					PlaySound(TEXT("menuClick.wav"), NULL, SND_ASYNC);
				if (choice == 0) {
					loadingScreen();
					int level = 1;
					while(level)
						level = playScreen(level);
					if (soundOn)
						PlaySound(TEXT("intro.wav"), NULL, SND_ASYNC);
				}
				else if (choice == 1)
					loadScreen();
				else if (choice == 2) {
					settingsScreen();
					if (soundOn)
						PlaySound(TEXT("intro.wav"), NULL, SND_ASYNC);
				}
				else
					exitScreen();
			}
			else if (bKeyGame[0] == 1) {
				if (soundOn)
					PlaySound(TEXT("menuClick.wav"), NULL, SND_ASYNC);
				choice = (choice + 4 - 1) % 4;
			}
			else if (bKeyGame[2] == 1) {
				if (soundOn)
					PlaySound(TEXT("menuClick.wav"), NULL, SND_ASYNC);
				choice = (choice + 1) % 4;
			}
			
			//enemies and stars
			graphic->randomStars();

			enemy1->render(graphic);
			enemy2->render(graphic);
			enemy3->render(graphic);
			enemy4->render(graphic);

			enemy1->move(2, 0);
			enemy2->move(-2, 0);
			enemy3->move(2, 0);
			enemy4->move(-2, 0);

			//default color
			graphic->setBufferWhite(graphic->getBuffer(title->getBufferKey()), 46, 11, BG, whiteDark);
			graphic->setBuffer(graphic->getBuffer(startButton->getBufferKey()), 68, 20, BG, whiteDark);
			graphic->setBuffer(graphic->getBuffer(loadButton->getBufferKey()), 68, 21, BG, whiteDark);
			graphic->setBuffer(graphic->getBuffer(settingButton->getBufferKey()), 68, 22, BG, whiteDark);
			graphic->setBuffer(graphic->getBuffer(exitButton->getBufferKey()), 68, 23, BG, whiteDark);

			//change color depends on choice
			switch (choice) {
			case 0:
				graphic->setBuffer(graphic->getBuffer(startButton->getBufferKey()), 68, 20, whiteDark, BG); break;
			case 1:
				graphic->setBuffer(graphic->getBuffer(loadButton->getBufferKey()), 68, 21, whiteDark, BG); break;
			case 2:
				graphic->setBuffer(graphic->getBuffer(settingButton->getBufferKey()), 68, 22, whiteDark, BG); break;
			case 3:
				graphic->setBuffer(graphic->getBuffer(exitButton->getBufferKey()), 68, 23, whiteDark, BG); break;
			default: break;
			}

			graphic->createFrame(0, 0, 145, 40);
			graphic->render();
		}
	}
	int playScreen(int Level)
	{
		if (soundOn)
			PlaySound(TEXT("GameSong2.wav"), NULL, SND_ASYNC);
		graphic->clearBuffer();
		player->setPos(72, 2);
		player->clearOldPos(graphic);
		GameLane* lane1 = new GameLane(1, 1, 1, graphic);
		GameLane* lane2 = new GameLane(2, 2, 1, graphic);
		GameLane* lane3 = new GameLane(3, 3, 1, graphic);

		vector<GameLane*> lanes = { lane1, lane2, lane3 };

		GameMenu* score = new Button("score");
		GameMenu* level = new Button("level");
		GameMenu* laneIndex = new Button("score");
		vector<wstring> scoreCounter, levelCounter, laneCounter;

		int lc = 0;

		int num = 0;
		bool* bKeyGame = new bool[key.size()]{ 0 };

		while (1)
		{
			delay(1000 / (FRAMERATE - 20));

			graphic->clearStars();
			player->render(graphic);

			//Controls
			for (int i = 0; i < key.size(); i++) { 	// Read input
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}
			if (bKeyGame[4] == 1 || GetAsyncKeyState(VK_ESCAPE)) {
				if (!pauseScreen())
					return Level;
				if (soundOn)
					PlaySound(TEXT("GameSong2.wav"), NULL, SND_ASYNC);
			}
			else if (bKeyGame[0] == 1 && player->getPos().y > 1) {
				player->move(0, -1);
			}
			else if (bKeyGame[1] == 1 && player->getPos().x > 1) {
				player->move(-1, 0);
			}
			else if (bKeyGame[2] == 1 && player->getPos().y < screenHeight - 2 - graphic->getBuffer(player->getBufferKey()).size()) {
				player->move(0, 1);
			}
			else if (bKeyGame[3] == 1 && player->getPos().x < screenWidth - 1 - graphic->getBuffer(player->getBufferKey())[0].length()) {
				player->move(1, 0);
			}

			graphic->randomStars();

			//Score and Level
			toVwstring(num++, scoreCounter);
			toVwstring(Level, levelCounter);

			toVwstring(lc, laneCounter);
			graphic->setBuffer(graphic->getBuffer(score->getBufferKey()), 2, 1, BG, 7);
			graphic->setBuffer(scoreCounter, 9, 1, BG, 7);
			graphic->setBuffer(graphic->getBuffer(level->getBufferKey()), 2, 2, BG, 7);
			graphic->setBuffer(levelCounter, 9, 2, BG, 7);
			graphic->setBuffer(graphic->getBuffer(laneIndex->getBufferKey()), 2, 4, BG, 7);
			graphic->setBuffer(laneCounter, 9, 4, BG, 7);


			for (auto l : lanes) l->logic();
			for (auto l : lanes) l->render(graphic);
			if (this->checkCollision(lanes, lc)) {
				graphic->glitch();
				gameoverScreen();
				graphic->clearBuffer();
				return 0;
			}

			player->render(graphic);

			graphic->createFrame(0, 0, 145, 40);

			graphic->render();
		}

	}
	void loadingScreen() {//cuz why not
		graphic->clearBuffer();
		graphic->createFrame(31, 27, 84, 3);
		for (int i = 1; i < 81; i += 5) {
			vector<wstring> tmp = { L"█████" };
			graphic->setBuffer(tmp, 32 + i, 28, BG, whiteDark);
			graphic->render();
			delay(83 - i);
		}
	}
	void saveScreen() {};
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


		int choice = 0;
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
				if (soundOn)
					PlaySound(TEXT("menuClick.wav"), NULL, SND_ASYNC);
				if (choice == 0) {
					soundOn = !soundOn;
				}
				else {
					graphic->clearBuffer();
					return;
				}
			}
			else if (bKeyGame[0] == 1) {
				if (soundOn)
					PlaySound(TEXT("menuClick.wav"), NULL, SND_ASYNC);
				choice = (choice + 2 - 1) % 2;
			}
			else if (bKeyGame[2] == 1) {
				if (soundOn)
					PlaySound(TEXT("menuClick.wav"), NULL, SND_ASYNC);
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
	bool pauseScreen() {
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


		int choice = 0;
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
				if (soundOn)
					PlaySound(TEXT("menuClick.wav"), NULL, SND_ASYNC);
				if (choice == 3) {
					soundOn = !soundOn;
				}
				else if (choice == 0){
					graphic->clearBuffer();
					return 1;
				}
				else if (choice == 2) {
					//save stuff hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
					return 1;
				}
				else {
					return 0;
				}
			}
			else if (bKeyGame[0] == 1) {
				if (soundOn)
					PlaySound(TEXT("menuClick.wav"), NULL, SND_ASYNC);
				choice = (choice + 4 - 1) % 4;
			}
			else if (bKeyGame[2] == 1) {
				if (soundOn)
					PlaySound(TEXT("menuClick.wav"), NULL, SND_ASYNC);
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
		graphic->setBuffer(graphic->getBuffer(exitTitle->getBufferKey()), 46, 19, BG, 7);
		graphic->createFrame(0, 0, 145, 40);
		graphic->render();
		while (1) {
			delay(1000 / (FRAMERATE / 10));
			if (GetAsyncKeyState(VK_RETURN))
				exit(0);
		}
	}
	void gameoverScreen() {
		graphic->clearBuffer();
		if (soundOn)
			PlaySound(TEXT("gameOver.wav"), NULL, SND_ASYNC);
		GameMenu* gameoverTitle = new Button("gameoverTitle");
		GameMenu* inspirationalText = new Button("inspirationalText");
		GameMenu* backButton = new Button("back");

		graphic->setBuffer(graphic->getBuffer(gameoverTitle->getBufferKey()), 58, 8, 7, BG);
		graphic->setBuffer(graphic->getBuffer(inspirationalText->getBufferKey()), 58, 28, BG, 7);
		graphic->setBuffer(graphic->getBuffer(backButton->getBufferKey()), 68, 31, 7, BG);

		graphic->createFrame(0, 0, 145, 40);
		graphic->render();
		int count = 0;
		while(!GetAsyncKeyState(VK_RETURN)){
			delay(1000 / (FRAMERATE / 8));
			if (GetAsyncKeyState('W') || GetAsyncKeyState('S'))
				count++;
			if (count == 10) {
				GameMenu* easterEgg2 = new Button("easterEgg2");
				graphic->setBuffer(graphic->getBuffer(easterEgg2->getBufferKey()), 57, 33, BG, 7);
				graphic->render();
			}
		}
		if (soundOn)
			PlaySound(TEXT("menuClick.wav"), NULL, SND_ASYNC);
	}

	bool checkCollision(vector<GameLane*> lanes, int &lc)
	{
		BOUNDINGBOX pla = player->getBoundingBox();
		int lane = pla.y / LANE_HEIGHT;
		lc = lane;
		if(lane - 1 < 0 || lane > lanes.size()) return false;
		GameLane* tmp = lanes[lane - 1];
		if (tmp->checkCollision(pla))
		{
			return true;
		}
		return false;
	}
};
