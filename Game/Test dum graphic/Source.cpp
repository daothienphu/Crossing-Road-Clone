#include <Windows.h>
#include <string>
#include<iostream>
#include<vector>
#pragma comment(lib, "winmm.lib")
using namespace std;
const wstring detail = L"▄▀█▓░╚╝╔╗║═";

#define nScreenWidth 100
#define nScreenHeight 40
const vector<char> key = { 'W', 'A', 'S', 'D' };

WORD* pColor = new WORD[nScreenWidth * nScreenHeight]; // Character array
wchar_t* pBuffer = new wchar_t[nScreenWidth * nScreenHeight]; // Color array

class cPlayer {
private:
	int X = 0, Y = 0;
	const vector<wstring> Sketch = {
		L"."
	};
public:
	int getX() { return X; }
	int getY() { return Y; }
	void setX(int x) { X = x; }
	void setY(int y) { Y = y; }
	void setXY(int x, int y) { X = x, Y = y; }
	void moveLeft() { X -= 2; } // Move 2 blocks
	void moveRight() { X += 2; } // Move 2 blocks
	void moveUp() { Y--; }
	void moveDown() { Y++; }
	vector<wstring> getSketch() { return Sketch; }
};
class cEnemy {
private:
	int prevX = 0, prevY = 0;
	int X = 0, Y = 0;
	const vector<wstring> Sketch = {
		L"..",
	};
	int color;
public:
	cEnemy() = default;
	cEnemy(int Color) {
		color = Color;
	}
	int getX() { return X; }
	int getY() { return Y; }
	int getColor() { return color; }
	void setX(int x) { X = x; }
	void setY(int y) { Y = y; }
	void setXY(int x, int y) { X = x, Y = y; }
	void moveLeft() { 
		prevX = X;
		X -= 2;
	} // Move 2 blocks
	void moveRight() { 
		prevX = X;
		X += 2; } // Move 2 blocks
	void moveUp() { Y--; }
	void moveDown() { Y++; }
	void draw() {

	}
	vector<wstring> getSketch() { return Sketch; }
};
const vector<wstring> Title = {
	L".'''.  l'''.  .'''.  .'''   .'''   'l'  l.  l  .''''",
	L"l      l'''.  l   l   '''.   '''.   l   l '.l  l ''l",
	L"'...'  l   l  '...'  '...'  '...'  .l.  l   l  '...l",
	L" ",
	L" ",
	L"             l'''.  .'''.  .'''.  l'''.",
	L"             l'''.  l   l  l...l  l   l",
	L"             l   l  '...'  l   l  l...'",
};

class cScreen {
private:
	//WORD* pColor = new WORD[nScreenWidth * nScreenHeight]; // Character array
	//wchar_t* pBuffer = new wchar_t[nScreenWidth * nScreenHeight]; // Color array
	HANDLE hConsole;
	DWORD dwBytesWritten = 0;
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
				if(pColor[j * nScreenWidth + i] != colorCharacter)
					pColor[j * nScreenWidth + i] = colorBackground * 16 + colorCharacter; // Set color
			}
		}
	}
	void drawScreen() {
		for (int i = 0; i < nScreenWidth; i++)
		{
			for (int j = 0; j < nScreenHeight; j++)
			{
				COORD cPos;
				cPos.X = i;
				cPos.Y = j;
				WriteConsoleOutputAttribute(hConsole, &pColor[j * nScreenWidth + i], 1, cPos, &dwBytesWritten);
				//Sleep(50);
			}
		}
		//Sleep(2000);
		WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		Sleep(3000);
	}
	//void drawScreenColor() {
	//	/*
	//	BOOL WINAPI WriteConsoleOutputAttribute(
	//		_In_        HANDLE  hConsoleOutput, // A handle to console screen buffer
	//		_In_  const WORD    *lpAttribute, // Color to print
	//		_In_        DWORD   nLength, // The number of character cells to be set to the specified color attributes.
	//		_In_        COORD   dwWriteCoord, // A COORD structure that specifies the character coordinates of the first cell whose attributes are to be set.
	//		_Out_       LPDWORD lpNumberOfAttrsWritten // A pointer to a variable that receives the number of character cells whose attributes were actually set.
	//	);
	//	If the function succeeds, the return value is nonzero.
	//	If the function fails, the return value is zero.
	//	*/

	//	for (int i = 0; i < nScreenWidth; i++) {
	//		for (int j = 0; j < nScreenHeight; j++) {
	//			COORD cPos;
	//			cPos.X = i;
	//			cPos.Y = j;
	//			WriteConsoleOutputAttribute(hConsole, &pColor[j * nScreenWidth + i], 1, cPos, &dwBytesWritten);
	//		}
	//	}
	//}
	//void drawScreenCharacter() {
	//	/*
	//	BOOL WINAPI WriteConsoleOutputCharacter(
	//		_In_  HANDLE  hConsoleOutput, // A handle to console screen buffer
	//		_In_  LPCTSTR lpCharacter, // Characters to write on screen
	//		_In_  DWORD   nLength, // Number of characters to write
	//		_In_  COORD   dwWriteCoord, // Coordinate of first character to write
	//		_Out_ LPDWORD lpNumberOfCharsWritten // A pointer to a variable that contains number of chars written
	//	);
	//	If the function succeeds, the return value is nonzero.
	//	If the function fails, the return value is zero.
	//	*/
	//	//DWORD dwBytesWritten = 0;
	//	WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	//}
	void gotoXY(int x, int y) {  // Place the cursor at (x, y)
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
	void drawText(wstring content, int nPosX, int nPosY, int colorBackground, int colorCharacter) {
		for (int i = 0; i < content.length(); i++) {
			pBuffer[nPosY * nScreenWidth + nPosX + i] = content.at(i);
			pColor[nPosY * nScreenWidth + nPosX + i] = colorBackground * 16 + colorCharacter;
		}
	}
	void drawBlock(vector<wstring> Sketch, int X, int Y, int colorBackground, int colorChar) {
		for (int i = 0; i < Sketch.size(); i++) {
			for (int j = 0; j < Sketch[i].length(); j++) {
				if (Sketch[i][j] == '.') {
					pBuffer[(Y + i) * nScreenWidth + X + j] = L'▄';
					pColor[(Y + i) * nScreenWidth + X + j] = colorBackground * 16 + colorChar;
				}
				if (Sketch[i][j] == '\'') {
					pBuffer[(Y + i) * nScreenWidth + X + j] = L'▀';
					pColor[(Y + i) * nScreenWidth + X + j] = colorBackground * 16 + colorChar;
				}
				if (Sketch[i][j] == 'l') {
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
	void startMenuScreen() {
		// CONFIGURE SCREEN
		configure();
		HANDLE hConsole1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole1);
		hConsole = hConsole1;

		// SOUND
		//PlaySound(TEXT("Eric Skiff - A Night Of Dizzy Spells.wav"), NULL, SND_ASYNC);


		int choiceMenu = 0; // 0 - Start game, 1 - Load game, 2 - Settings, 3 - Exit
		// MENU SCREEN
		while (true) {
			// CLEAR SCREEN
			clearScreen(0, 1);

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
			drawText(L"  LOAD GAME ", 0, 1, 0, 7);
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
					glitchEffect(L" START GAME ", 0, 0, 7, 6, 0, 7);
					startGameScreen();
				}
				else if (choiceMenu == 1) {
					// LOAD GAME
					glitchEffect(L"  LOAD GAME ", 0, 1, 7, 6, 0, 7);
				}
				else if (choiceMenu == 2) {
					// SETTINGS
					glitchEffect(L"  SETTINGS  ", 0, 2, 7, 6, 0, 7);
				}
				else if (choiceMenu == 3) {
					// EXIT
					glitchEffect(L"    EXIT    ", 0, 3, 7, 6, 0, 7);
				}
			}
		}
	}
	void startGameScreen() {
		cPlayer Player;
		Player.setXY(2, 1); // Player spawns at (0, 0)
		cEnemy Enemy1;//, Enemy2;
		Enemy1.setXY(15, 10);
		//Enemy2.setXY(70, 20);
		int count = 0;
		bool gameOver = false;
		while (gameOver == false) {
			cout << count << endl;
			count++;
			// CLEAR SCREEN
			int bg = 0, ch = 7;
			clearScreen(bg, ch);
			Sleep(50);

			// READ INPUT
			bool* bKeyGame = new bool[key.size()]; // Check ingame input
			for (int i = 0; i < key.size(); i++) { 	// Read input
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}
			// W - Move up
			if (bKeyGame[0] == 1) {
				Player.moveUp();
			}
			// A - Move left
			if (bKeyGame[1] == 1) {
				Player.moveLeft();
			}
			// S - Move down
			if (bKeyGame[2] == 1) {
				Player.moveDown();
			}
			// D - Move right
			if (bKeyGame[3] == 1) {
				Player.moveRight();
			}

			// UPDATE 
			if (Enemy1.getX() >= nScreenWidth)Enemy1.setX(15);
			Enemy1.moveRight();
			//if (Enemy2.getX() <= 0) Enemy2.setX(70);
			//Enemy2.moveLeft();

			// DISPLAY
			Sleep(990);
			drawBlock(Player.getSketch(), Player.getX(), Player.getY(), bg, 2);
			drawBlock(Enemy1.getSketch(), Enemy1.getX(), Enemy1.getY(), bg, 6); // Red enemy
			//drawBlock(Enemy2.getSketch(), Enemy2.getX(), Enemy2.getY(), bg, 3); // Yellow enemy
			drawScreen();
		}
	}

};

int main() {
	cScreen Screen;
	Screen.startMenuScreen();
	return 0;
}




