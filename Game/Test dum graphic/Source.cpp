#include <Windows.h>
#include <string>
#include<iostream>
#include<vector>
using namespace std;
const wstring detail = L" ▄▀█▓░╚╝╔╗║═";
#define nScreenWidth 160
#define nScreenHeight 44
#define fps 20
const vector<char> key = { 'W', 'A', 'S', 'D' };
const vector<wstring> e1 = {
	L". '.  .' .",
	L"l.l'll'l.'",
	L" ll.ll.ll",
	L".l '  ' l."
};
const vector<wstring> e2 = {
	L" '...'",
	L" l'l'l",
	L".'l'l'.",
	L"' ' ' '"
};
const vector<wstring> e3 = {
	L"  '..'",
	L"l.'ll'.l",
	L"l'llll'l",
	L" .l  l."
};
const vector<wstring> e4 = {
	L" .l...l.",
	L"ll..l..ll",
	L"l'l'l'l'l",
	L" ' ' ' '"
};
const vector<wstring> Title = { // 52 x 8
	L".'''.  l'''.  .'''.  .'''   .'''   'l'  l.  l  .''''",
	L"l      l'''.  l   l   '''.   '''.   l   l '.l  l ''l",
	L"'...'  l   l  '...'  '...'  '...'  .l.  l   l  '...l",
	L" ",
	L" ",
	L"             l'''.  .'''.  .'''.  l'''.",
	L"             l'''.  l   l  l...l  l   l",
	L"             l   l  '...'  l   l  l...'",
};
const vector<wstring> GameOver = {
	L".'''.  .'''.  l. .l  l'''    .'''.  l   l  l'''  l'''.",
	L"l  ..  l'''l  l ' l  l''     l   l  '. .'  l''   l'''.",
	L"'...'  l   l  l   l  l...    '...'   '.'   l...  l   l"
};
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
	int X = 0, Y = 0;
	vector<wstring> Sketch;
public:
	cEnemy(int x, int y, vector<wstring> sketch) {
		X = x;
		Y = y;
		Sketch = sketch;
	}
	int getX() { return X; }
	int getY() { return Y; }
	void setX(int x) { X = x; }
	void setY(int y) { Y = y; }
	void setXY(int x, int y) { X = x, Y = y; }
	void moveLeft() { X -= 2; } // Move 2 blocks
	void moveRight() { X += 2; } // Move 2 blocks
	void moveUp() { Y--; }
	void moveDown() { Y++; }
	int width() {
		int max = Sketch[0].length();
		for (int i = 0; i < Sketch.size(); i++)
			if (Sketch[i].length() > max)
				max = Sketch[i].length();
		return max;
	}
	int height() { return Sketch.size(); }
	vector<wstring> getSketch() { return Sketch; }
	void setSketch(vector<wstring> sketch) { Sketch = sketch; }
};
bool checkCollision(cPlayer player, cEnemy* enemy) {
	if (player.getX() >= enemy->getX() && player.getX() <= enemy->getX() + enemy->width() &&
		player.getY() >= enemy->getY() && player.getY() <= enemy->getY() + enemy->height())
		return true;
	return false;
}
class cScreen {
private:
	WORD* pColor = new WORD[nScreenWidth * nScreenHeight]; // Character array
	wchar_t* pBuffer = new wchar_t[nScreenWidth * nScreenHeight]; // Color array
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
		system("MODE 160, 45"); // Set screen size (width, height + 1)
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
		Sleep(1000 / fps); //Rate
		WriteConsoleOutputAttribute(hConsole, pColor, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
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
	void glitchEffectText(wstring content, int X, int Y, int colorBackground1, int colorBackground2, int colorCharacter1, int colorCharacter2) {
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


		int choiceMenu = 0; // 0 - Start game, 1 - Load game, 2 - Settings, 3 - Exit
		// MENU SCREEN
		while (true) {
			// CLEAR SCREEN
			clearScreen(0, 0);

			// READING INPUT
			bool* bKey = new bool[key.size()];
			for (int i = 0; i < key.size(); i++) { 	// Read input
				bKey[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}
			// W - Move up
			if (bKey[0] == 1 ) {
				choiceMenu = (choiceMenu - 1) % 4;
			}
			// S - Move down
			if (bKey[2] == 1) {
				choiceMenu = (choiceMenu + 1) % 4;
			}

			// DISPLAY CURRENT MENU
			drawBlock(Title, 54, 15, 0, 7);
			int xMenu = 74, yMenu = 25;
			//drawText(L"Press W to move up, S to move down", xMenu, yMenu+4, 0, 7);
			drawText(L" START GAME ", xMenu, yMenu, 0, 7);
			drawText(L"  LOAD GAME ", xMenu, yMenu + 1, 0, 7);
			drawText(L"  SETTINGS  ", xMenu, yMenu + 2, 0, 7);
			drawText(L"    EXIT    ", xMenu, yMenu + 3, 0, 7);
			if (choiceMenu == 0) {
				drawText(L" START GAME ", xMenu, yMenu, 7, 0);

			}
			else if (choiceMenu == 1 || choiceMenu == -3) {
				drawText(L"  LOAD GAME ", xMenu, yMenu + 1, 7, 0);

			}
			else if (choiceMenu == 2 || choiceMenu==-2) {
				drawText(L"  SETTINGS  ", xMenu, yMenu + 2, 7, 0);

			}
			else if (choiceMenu == 3 || choiceMenu ==-1) {
				drawText(L"    EXIT    ", xMenu, yMenu + 3, 7, 0);

			}
			drawText(L"choice: " + to_wstring(choiceMenu), xMenu, yMenu + 4, 0, 7);
			drawScreen();

			// ENTER - Select
			if (GetAsyncKeyState(VK_RETURN)) {
				if (choiceMenu == 0) {
					// START GAME
					glitchEffectText(L" START GAME ", xMenu, yMenu, 7, 6, 0, 7);
					startGameScreen();
				}
				else if (choiceMenu == 1) {
					// LOAD GAME
					glitchEffectText(L"  LOAD GAME ", xMenu, yMenu + 1, 7, 6, 0, 7);
				}
				else if (choiceMenu == 2) {
					// SETTINGS
					glitchEffectText(L"  SETTINGS  ", xMenu, yMenu + 2, 7, 6, 0, 7);
				}
				else if (choiceMenu == 3) {
					// EXIT
					glitchEffectText(L"    EXIT    ", xMenu, yMenu + 3, 7, 6, 0, 7);
				}
			}
		}
	}
	void startGameScreen() {
		//INITIALISE PLAYER
		cPlayer Player;
		Player.setXY(80, 1);
		//INITIALISE ENEMIES
		cEnemy* Enemy[4];
		Enemy[0] = new cEnemy(0, 10, e1);
		Enemy[1] = new cEnemy(nScreenWidth, 15, e2);
		Enemy[2] = new cEnemy(50, 20, e3);
		Enemy[3] = new cEnemy(nScreenWidth - 30, 25, e4);

		bool gameOver = false;
		while (gameOver == false) {
			// CLEAR SCREEN
			int bg = 0, ch = 0;
			clearScreen(bg, 7);
			pBuffer[Player.getY() * nScreenWidth + Player.getX()] = L'.';

			// READ INPUT
			bool* bKeyGame = new bool[key.size()]; // Check ingame input
			for (int i = 0; i < key.size(); i++) { 	// Read input
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}

			// UPDATE 
			// Player
			if (bKeyGame[0] == 1) // W - Move up
			{
				Player.moveUp();
			}
			if (bKeyGame[1] == 1) // A - Move left
			{
				Player.moveLeft();
			}
			if (bKeyGame[2] == 1) 	// S - Move down
			{
				Player.moveDown();
			}
			if (bKeyGame[3] == 1) // D - Move right
			{
				Player.moveRight();
			}
			// Enemies
			if (Enemy[0]->getX() + 10 >= nScreenWidth) Enemy[0]->setX(0);
			else Enemy[0]->moveRight();
			if (Enemy[1]->getX() <= 0) Enemy[1]->setX(nScreenWidth - 10);
			else Enemy[1]->moveLeft();
			if (Enemy[2]->getX() + 10 >= nScreenWidth) Enemy[2]->setX(0);
			else Enemy[2]->moveRight();
			if (Enemy[3]->getX() <= 0) Enemy[3]->setX(nScreenWidth - 10);
			else Enemy[3]->moveLeft();
			int score = 0;
			// GAME LOGIC
			for (int i = 0; i < 4; i++) {
				if (checkCollision(Player, Enemy[i]) == true) {
					clearScreen(0, 7);
					drawBlock(GameOver, 50, 10, 0, 6);
					drawText(L"YOUR SCORE: " + to_wstring(score), 70, 20, 0, 7);
					drawScreen();
					Sleep(5000);
					exit(0);
				}
			}

			// DISPLAY GAME SCREEN
			drawFrame(0, 0, nScreenWidth, nScreenHeight - 1, 0, 7);
			drawBlock(Player.getSketch(), Player.getX(), Player.getY(), bg, 7);
			drawBlock(Enemy[0]->getSketch(), Enemy[0]->getX(), Enemy[0]->getY(), bg, 6); // Red enemy
			drawBlock(Enemy[1]->getSketch(), Enemy[1]->getX(), Enemy[1]->getY(), bg, 3); // Yellow enemy
			drawBlock(Enemy[2]->getSketch(), Enemy[2]->getX(), Enemy[2]->getY(), bg, 4); // Green
			drawBlock(Enemy[3]->getSketch(), Enemy[3]->getX(), Enemy[3]->getY(), bg, 1); // Blue
			drawText(L"SCORE: " + to_wstring(score), 4, 2, 0, 7);
			drawScreen();
		}
	}

};

int main() {
	cScreen Screen;
	Screen.startMenuScreen();
	return 0;
}




