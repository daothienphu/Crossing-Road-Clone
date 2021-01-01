#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>

#include "Header.h"
#include "GameObject.h"
#include "Player.h"
#include "GameObstacles.h"

#define MAX_OBJECTS_PER_LANE 10
#define LANE_HEIGHT 50

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

#pragma region GameCore

class GameCore {
	friend class GameObject;
private:
	//graphic
	static WORD* pColor; // Character array
	static wchar_t* pBuffer; // Color array
	HANDLE hConsole;
	DWORD dwBytesWritten;
	//end graphic

	GAMESTATE state;
	int level;
	
	GameObject* player;
public:
	GameCore() {
		state = GAMESTATE::PLAYING;

		//graphic
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		dwBytesWritten = 0;
	};
	~GameCore() = default;

#pragma region GRAPHIC
	void clearScreen(int colorBackground, int colorCharacter) {
		for (int i = 0; i < screenWidth; i++) {
			for (int j = 0; j < screenHeight; j++) {
				pBuffer[j * screenWidth + i] = L' '; // Fill screen with blank space
				pColor[j * screenWidth + i] = colorBackground * 16 + colorCharacter; // Set color
			}
		}
	}
	void charToBlock(vector<wstring> Sketch, int X, int Y, int colorBackground, int colorChar) {
		for (int i = 0; i < Sketch.size(); i++) {
			for (int j = 0; j < Sketch[i].length(); j++) {
				if (Sketch[i][j] == '.') {
					pBuffer[(Y + i) * screenWidth + X + j] = L'▄';
					pColor[(Y + i) * screenWidth + X + j] = colorBackground * 16 + colorChar;
				}
				if (Sketch[i][j] == '\'') {
					pBuffer[(Y + i) * screenWidth + X + j] = L'▀';
					pColor[(Y + i) * screenWidth + X + j] = colorBackground * 16 + colorChar;
				}
				if (Sketch[i][j] == 'l') {
					pBuffer[(Y + i) * screenWidth + X + j] = L'█';
					pColor[(Y + i) * screenWidth + X + j] = colorBackground * 16 + colorChar;
				}
			}
		}
	}
	void drawFrame(int x, int y, int width, int height, int colorBackground, int colorChar) {
		pBuffer[y * screenWidth + x] = L'╔';
		pBuffer[y * screenWidth + x + width - 1] = L'╗';
		pBuffer[(height - 1 + y) * screenWidth + x] = L'╚';
		pBuffer[(height - 1 + y) * screenWidth + x + width - 1] = L'╝';

		for (int i = 1; i < width - 1; ++i) {
			pBuffer[y * screenWidth + x + i] = L'=';
			pBuffer[(height - 1 + y) * screenWidth + x + i] = L'=';
		}

		for (int i = 1; i < height - 1; ++i) {
			pBuffer[y * screenWidth + x + i] = L'║';
			pBuffer[(width - 1 + y) * screenWidth + x + i] = L'║';
		}
	}

	void drawScreen(int x, int y, int w, int h) {
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				COORD tmp;
				tmp.X = j; tmp.Y = i;
				WriteConsoleOutputAttribute(hConsole, &pColor[i * screenWidth + j], 1, tmp, &dwBytesWritten);
			}
		}
		WriteConsoleOutputCharacter(hConsole, pBuffer, screenWidth * screenHeight, { 0, 0 }, &dwBytesWritten);
	}
	void drawScreen() {
		for (int i = 0; i < screenHeight; i++)
		{
			for (int j = 0; j < screenWidth; j++)
			{
				COORD cPos;
				cPos.X = j;
				cPos.Y = i;
				WriteConsoleOutputAttribute(hConsole, &pColor[i * screenWidth + j], 1, cPos, &dwBytesWritten);
			}
		}
		WriteConsoleOutputCharacter(hConsole, pBuffer, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
	}
	void drawText(wstring content, int nPosX, int nPosY, int colorBackground, int colorCharacter) {
		for (int i = 0; i < content.length(); i++) {
			pBuffer[nPosY * screenWidth + nPosX + i] = content.at(i);
			pColor[nPosY * screenWidth + nPosX + i] = colorBackground * 16 + colorCharacter;
		}
	}
	void glitchEffect(wstring content, int X, int Y, int colorBackground1, int colorBackground2, int colorCharacter1, int colorCharacter2) {
		drawText(content, X, Y, colorBackground2, colorCharacter2); drawScreen(X, Y, content.length(), 1);
		drawText(content, X, Y, colorBackground1, colorCharacter1); drawScreen(X, Y, content.length(), 1);
		drawText(content, X, Y, colorBackground2, colorCharacter2); drawScreen(X, Y, content.length(), 1);
	}
	int renderStartScreen() {
		// CONFIGURE SCREEN
		HANDLE hConsole1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole1);
		hConsole = hConsole1;

		int choiceMenu = 0; // 0 - Start game, 1 - Load game, 2 - Settings, 3 - Exit
		// MENU SCREEN
		while (true) {
			delay(50);
			// CLEAR SCREEN
			clearScreen(0, 1);
			charToBlock(Title, 46, 10, 0, 7);
			drawText(L"1", 144, 39, 0, 7);
			// READING INPUT
			bool* bKey = new bool[key.size()];
			for (int i = 0; i < key.size(); i++) {
				bKey[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}
			if (bKey[0] == 1) {
				choiceMenu = (choiceMenu + 4 - 1) % 4;
			}
			if (bKey[2] == 1) {
				choiceMenu = (choiceMenu + 1) % 4;
			}

			// DISPLAY CURRENT MENU
			drawText(L"(Press W to move up, S to move down)", 55, 23, 0, 7);
			drawText(L" START GAME ", 66, 19, 0, 7);
			drawText(L"  LOAD GAME ", 66, 20, 0, 7);
			drawText(L"  SETTINGS  ", 66, 21, 0, 7);
			drawText(L"    EXIT    ", 66, 22, 0, 7);
			switch (choiceMenu)
			{
			case 0: drawText(L" START GAME ", 66, 19, 7, 0); break;
			case 1: drawText(L"  LOAD GAME ", 66, 20, 7, 0); break;
			case 2: drawText(L"  SETTINGS  ", 66, 21, 7, 0); break;
			case 3: drawText(L"    EXIT    ", 66, 22, 7, 0); break;
			default: break;
			}
			drawScreen();

			// ENTER - Select
			if (GetAsyncKeyState(VK_RETURN)) {
				if (choiceMenu == 0) {
					glitchEffect(L" START GAME ", 66, 19, 7, 6, 0, 7);
					return 0;
				}
				else if (choiceMenu == 1) {
					glitchEffect(L"  LOAD GAME ", 66, 20, 7, 6, 0, 7);
					return 1;
				}
				else if (choiceMenu == 2) {
					glitchEffect(L"  SETTINGS  ", 66, 21, 7, 6, 0, 7);
					//setting screen
				}
				else if (choiceMenu == 3) {
					glitchEffect(L"    EXIT    ", 66, 22, 7, 6, 0, 7);
					return 3;
				}
			}
		}
	}


#pragma endregion

	void start()
	{
		thread t1(&GameCore::renderStartScreen, this);
		//thread t2(&GameCore::gameLogic, this);

		t1.join();
		//t2.join();
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
			//pause and resume missing.
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
			//following these rules:
			//	1: each lanes will have maximum MAX_OBJECTS_PER_LANE = 10(by defualt) obstacles
			//	2: each level will have __(fill in this) lanes
			//	3: the 1st ROW will hold objects of the 1st lane. 
			//	   If there are less objects than the MAX, the rest of that lane will be fill will NULL
			//	4: Continue for lane 2nd (by default)
			//	5: Keep do until out of lanes
			//theses rules help us optimize the check collision
		}
	}


	bool checkCollision(vector<vector<GameObject*>> &obs, int level)
	{
		//calculate the player in which lane
		BOUNDINGBOX pla = player->getBoundingBox();
		int lane = (pla.x / LANE_HEIGHT) + 1;

		for (int i = lane - 1; i < lane; i++)
		{
			for (int j = 0; i < MAX_OBJECTS_PER_LANE; i++)
			{
				if (obs[i][j] == nullptr) break;
				BOUNDINGBOX ob = obs[i][j]->getBoundingBox();
				if (checkCollisionOnHorizontal(pla, ob) && checkCollisionOnVerticle(pla, ob)) return true;
				else continue;
			}
		}
	}

	bool checkCollisionOnHorizontal(BOUNDINGBOX &a, BOUNDINGBOX &b)
	{
		if(a.x > b.x) return this->checkCollisionOnHorizontal(b, a);
		if (a.x + a.w > b.x) return true;
		else return false;
	}

	bool checkCollisionOnVerticle(BOUNDINGBOX& a, BOUNDINGBOX& b)
	{
		if (a.y > b.y) return this->checkCollisionOnHorizontal(b, a);
		if (a.y + a.h > b.y) return true;
		else return false;
	}
};

WORD* GameCore::pColor = new WORD[screenWidth * screenHeight];
wchar_t* GameCore::pBuffer = new wchar_t[screenWidth * screenHeight];
#pragma endregion
