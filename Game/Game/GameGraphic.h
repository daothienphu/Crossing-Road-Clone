#pragma once

#include <Windows.h>
#include <string>
#include<iostream>
#include<vector>
using namespace std;
const wstring detail = L" ▄▀█▓░╚╝╔╗║═";

#define nScreenWidth 100
#define nScreenHeight 40

#pragma region GameGraphic

class cPlayer {
public:
	int X = 0, Y = 0;
	const vector<wstring> Sketch = {
		L"."
	};
};
class Enemy {
public:
	COORD Position;
	const vector<wstring> Sketch = {
		L"llll",
		L"llll"
	};
};
const vector<wstring> title = {
L".'''.  l'''.  .'''.  .'''   .'''   'l'  l.  l  .''''",
L"l      l'''.  l   l   '''.   '''.   l   l '.l  l ''l",
L"'...'  l   l  '...'  '...'  '...'  .l.  l   l  '...l",
L" ",
L" ",
L"             l'''.  .'''.  .'''.  l'''.",
L"             l'''.  l   l  l...l  l   l",
L"             l   l  '...'  l   l  l...'",
};
class GameGraphic
{
private:
	WORD* pColor = new WORD[nScreenWidth * nScreenHeight]; // Character array
	wchar_t* pBuffer = new wchar_t[nScreenWidth * nScreenHeight]; // Color array
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
public:
	void FixConsoleWindow() {
		HWND consoleWindow = GetConsoleWindow();
		LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
		style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
		SetWindowLong(consoleWindow, GWL_STYLE, style);
	}
	void configure() {
		system("MODE 100, 41"); // Set screen size (width, height + 1)
		FixConsoleWindow(); //Fix window size

		// Make custom color palette - up to 16 colors, will update later
		HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); // A hanle to console screen buffer.
		CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
		csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		GetConsoleScreenBufferInfoEx(hConsoleOutput, &csbiex);
		csbiex.ColorTable[0] = RGB(16, 16, 60); // Default background color - dark blue
		csbiex.ColorTable[1] = RGB(63, 81, 181); // Light blue
		csbiex.ColorTable[2] = RGB(255, 87, 34); // Orange
		csbiex.ColorTable[3] = RGB(255, 235, 59); // Yellow
		csbiex.ColorTable[4] = RGB(76, 175, 80); // Green
		csbiex.ColorTable[5] = RGB(156, 39, 176); // Purple
		csbiex.ColorTable[6] = RGB(237, 28, 36); // Red
		csbiex.ColorTable[7] = RGB(242, 242, 242); // Dark white
		csbiex.ColorTable[8] = RGB(248, 248, 248); // White
		csbiex.ColorTable[9] = RGB(20, 20, 20); // Black
		SetConsoleScreenBufferInfoEx(hConsoleOutput, &csbiex);
	}
	void clearScreen(int colorBackground, int colorCharacter) {
		for (int i = 0; i < nScreenWidth; i++) {
			for (int j = 0; j < nScreenHeight; j++) {
				pBuffer[j * nScreenWidth + i] = L' '; // Fill screen with blank space
				pColor[j * nScreenWidth + i] = colorBackground * 16 + colorCharacter; // Set color
			}
		}
	}
	void drawScreen() {
		drawScreenColor();
		drawScreenCharacter();
	}
	void drawScreenColor() {
		/*
		BOOL WINAPI WriteConsoleOutputAttribute(
			_In_        HANDLE  hConsoleOutput, // A handle to console screen buffer
			_In_  const WORD    *lpAttribute, // Color to print
			_In_        DWORD   nLength, // The number of character cells to be set to the specified color attributes.
			_In_        COORD   dwWriteCoord, // A COORD structure that specifies the character coordinates of the first cell whose attributes are to be set.
			_Out_       LPDWORD lpNumberOfAttrsWritten // A pointer to a variable that receives the number of character cells whose attributes were actually set.
		);
		If the function succeeds, the return value is nonzero.
		If the function fails, the return value is zero.
		*/
		DWORD dwBytesWritten = 0;
		for (int i = 0; i < nScreenWidth; i++) {
			for (int j = 0; j < nScreenHeight; j++) {
				COORD cPos;
				cPos.X = i;
				cPos.Y = j;
				WriteConsoleOutputAttribute(hConsole, &pColor[j * nScreenWidth + i], 1, cPos, &dwBytesWritten);
			}
		}
	}
	void drawScreenCharacter() {
		/*
		BOOL WINAPI WriteConsoleOutputCharacter(
			_In_  HANDLE  hConsoleOutput, // A handle to console screen buffer
			_In_  LPCTSTR lpCharacter, // Characters to write on screen
			_In_  DWORD   nLength, // Number of characters to write
			_In_  COORD   dwWriteCoord, // Coordinate of first character to write
			_Out_ LPDWORD lpNumberOfCharsWritten // A pointer to a variable that contains number of chars written
		);
		If the function succeeds, the return value is nonzero.
		If the function fails, the return value is zero.
		*/
		DWORD dwBytesWritten = 0;
		WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
	void gotoXY(int x, int y) {
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Place the cursor at (x, y)
	}
	void drawText(wstring content, int nPosX, int nPosY, int colorBackground, int colorCharacter) {
		for (int i = 0; i < content.length(); i++, nPosX++) {
			pBuffer[nPosY * nScreenWidth + nPosX] = content.at(i);
			pColor[nPosY * nScreenWidth + nPosX] = colorBackground * 16 + colorCharacter;
		}
	}
	void drawBlock(int X, int Y, vector<wstring> str, int colorBackground, int colorChar) {
		for (int i = 0; i < str.size(); i++) {
			for (int j = 0; j < str[i].length(); j++) {
				if (str[i][j] == '.') {
					pBuffer[(Y + i) * nScreenWidth + X + j] = L'▄';
					pColor[(Y + i) * nScreenWidth + X + j] = colorBackground * 16 + colorChar;
				}
				if (str[i][j] == '\'') {
					pBuffer[(Y + i) * nScreenWidth + X + j] = L'▀';
					pColor[(Y + i) * nScreenWidth + X + j] = colorBackground * 16 + colorChar;
				}
				if (str[i][j] == 'l') {
					pBuffer[(Y + i) * nScreenWidth + X + j] = L'█';
					pColor[(Y + i) * nScreenWidth + X + j] = colorBackground * 16 + colorChar;
				}
			}
		}
	}
	void drawFrame(int x, int y, int width, int height, int colorBackground, int colorChar) {
		for (int i = 0; i < height; i++) { // y iterator
			for (int j = 0; j < width; j++) { // x iterator
				if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
					// Corners
					if (i == 0 && j == 0)
						pBuffer[(i + y) * nScreenWidth + x + j] = L'╔';
					else if (i == 0 && j == width - 1)
						pBuffer[(i + y) * nScreenWidth + x + j] = L'╗';
					else if (i == height - 1 && j == 0)
						pBuffer[(i + y) * nScreenWidth + x + j] = L'╚';
					else if (i == height - 1 && j == width - 1)
						pBuffer[(i + y) * nScreenWidth + x + j] = L'╝';
					// Sides
					if ((i == 0 && (j >= 1 && j < width - 1)) || (i == height - 1 && (j >= 1 && j < width - 1)))
						pBuffer[(i + y) * nScreenWidth + x + j] = L'═';
					if ((j == 0 && (i >= 1 && i < height - 1)) || (j == width - 1 && (i >= 1 && i < height - 1)))
						pBuffer[(i + y) * nScreenWidth + x + j] = L'║';
					pColor[(i + y) * nScreenWidth + x + j] = colorBackground * 16 + colorChar;
				}
			}
		}
	}

	void glitchEffect(wstring content, int X, int Y, int colorBackground1, int colorBackground2, int colorCharacter1, int colorCharacter2) {
		drawText(content, X, Y, colorBackground2, colorCharacter2); drawScreen();
		drawText(content, X, Y, colorBackground1, colorCharacter1); drawScreen();
		drawText(content, X, Y, colorBackground2, colorCharacter2); drawScreen();
	}

	void game() {
		system("MODE 100, 41"); // Set screen size (width, height + 1)
		//system("color 89"); // Set background color

		HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
		csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		GetConsoleScreenBufferInfoEx(hConsoleOutput, &csbiex);

		csbiex.ColorTable[0] = RGB(16, 16, 60); // Default background color - dark blue
		csbiex.ColorTable[1] = RGB(63, 81, 181);
		csbiex.ColorTable[2] = RGB(255, 87, 34);
		csbiex.ColorTable[3] = RGB(255, 235, 59);
		csbiex.ColorTable[4] = RGB(76, 175, 80);
		csbiex.ColorTable[5] = RGB(156, 39, 176);
		csbiex.ColorTable[6] = RGB(237, 28, 36);
		csbiex.ColorTable[7] = RGB(242, 242, 242);
		csbiex.ColorTable[8] = RGB(248, 248, 248);
		csbiex.ColorTable[9] = RGB(20, 20, 20);

		SetConsoleScreenBufferInfoEx(hConsoleOutput, &csbiex);

		HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);

		WORD* pColor = new WORD[nScreenWidth * nScreenHeight];
		wchar_t* pBuffer = new wchar_t[nScreenWidth * nScreenHeight];



		cPlayer Player;
		const vector<char> key = { 'W', 'A', 'S', 'D' };
		bool gameOver = false;
		int eX = 0, eY = 0;//Enemy test

		while (1) {
			while (gameOver == false) {
				//Sleep(100); // Affects player's moving speed

				for (int i = 0; i < nScreenWidth; i++) {
					for (int j = 0; j < nScreenHeight; j++) {
						pBuffer[j * nScreenWidth + i] = L' '; // Why won't it refill with the space? It creates a lagging when objects move
						pColor[j * nScreenWidth + i] = 0 * 16 + 0; // Set background color
					}
				}

				int curX = Player.X, curY = Player.Y;
				pBuffer[curY * nScreenWidth + curX] = '.'; // Show player's previous potition

				//CHANGE TO: LOAD INFO FROM GAMELOGIC -> RENDER;

				// INPUT
				bool* bKey = new bool[key.size()];
				// Read input
				for (int i = 0; i < key.size(); i++) {
					bKey[i] = (GetAsyncKeyState(key.at(i))) != 0;
				}
				// Move up
				if (bKey[0] == 1) {
					Player.Y--;
				}
				// Move down
				if (bKey[2] == 1) {
					Player.Y++;
				}
				// Move left
				if (bKey[1] == 1) {
					Player.X -= 2;
				}
				// Move right
				if (bKey[3] == 1) {
					Player.X += 2;
				}
				//Player.drawCurrentPos();
				// Adjust player's position in buffer
				//pBuffer[Player.Y * nScreenWidth + Player.X] = L'▄';

				draw(pBuffer, pColor, Player.X, Player.Y, Player.show, 0, 4);
				draw(pBuffer, pColor, 20, 16, title, 0, 2); //<<-----Worksssssssss
				drawFrame(pBuffer, pColor, 0, 0, 9, 10);
				if (eX < nScreenWidth) { draw(pBuffer, pColor, eX, eY, enemy, 0, 5); eX++; }
				else eX = 0;
				// DISPLAY
				// Print color
				DWORD dwBytesWritten = 0;
				for (int i = 0; i < nScreenWidth; i++) {
					for (int j = 0; j < nScreenHeight; j++) {
						COORD cPos;
						cPos.X = i;
						cPos.Y = j;
						WriteConsoleOutputAttribute(hConsole, &pColor[j * nScreenWidth + i], 1, cPos, &dwBytesWritten);// Takes too much time because it draws char by char (?)
					}
				}
				// Print character
				WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
				//Sleep(5000);
			}
		}
	}

	void startMenu() {
		configure();
		const vector<char> key = { 'W', 'A', 'S', 'D' };
		int choiceMenu = 0; // 0 - Start game, 1 - Load game, 2 - Settings, 3 - Exit
		// MENU SCREEN
		while (true) {
			// CLEAR SCREEN
			clearScreen(0, 7);

			// READING INPUT
			bool* bKey = new bool[key.size()];
			for (int i = 0; i < key.size(); i++) { 	// Read input
				bKey[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}
			// W - Move up
			if (bKey[0] == 1) {
				choiceMenu = (choiceMenu - 1) % 4;
			}
			// S - Move down
			if (bKey[2] == 1) {
				choiceMenu = (choiceMenu + 1) % 4;
			}

			// DISPLAY CURRENT MENU
			drawText(L"Press W to move up, S to move down", 0, 4, 0, 7);
			drawText(L" START GAME ", 0, 0, 0, 7);
			drawText(L"  LOADGAME  ", 0, 1, 0, 7);
			drawText(L"  SETTINGS  ", 0, 2, 0, 7);
			drawText(L"    EXIT    ", 0, 3, 0, 7);
			if (choiceMenu == 0) {
				drawText(L" START GAME ", 0, 0, 7, 0);
			}
			else if (choiceMenu == 1) {
				drawText(L"  LOAD GAME ", 0, 1, 7, 0);
			}
			else if (choiceMenu == 2) {
				drawText(L"  SETTINGS  ", 0, 2, 7, 0);
			}
			else if (choiceMenu == 3) {
				drawText(L"    EXIT    ", 0, 3, 7, 0);
			}
			drawScreen();

			// ENTER - Select
			if (GetAsyncKeyState(VK_RETURN)) {
				if (choiceMenu == 0) {
					// START GAME
					glitchEffect(L" START GAME ", 0, 0, 7, 5, 0, 7);
				}
				else if (choiceMenu == 1) {
					// LOAD GAME
					glitchEffect(L"  LOAD GAME ", 0, 1, 0, 5, 7, 7);
				}
				else if (choiceMenu == 2) {
					// SETTINGS
					glitchEffect(L"  SETTINGS  ", 0, 2, 0, 5, 7, 7);
				}
				else if (choiceMenu == 3) {
					// EXIT
					glitchEffect(L"    EXIT    ", 0, 3, 0, 5, 7, 7);
				}
			}
		}
	}

};

#pragma endregion






