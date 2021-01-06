#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <chrono> // Time
#include <ctime>  // Time
#include <Windows.h>
#include <string>
#include<iostream>
#include<vector>
#include<cstdlib>
#include <windows.h>
using namespace std;
const wstring detail = L" ▄▀█▓░╚╝╔╗║═";
#define nScreenWidth 160
#define nScreenHeight 44
#define fps 20
enum { darkblue, lightblue, orange, yellow, green, purple, red, darkwhite, white, black };
const vector<char> key = { 'W', 'A', 'S', 'D' };
// For graphics
const vector<wstring> e1 = { // 10 x 4
	L". '.  .' .",
	L"l.l'll'l.'",
	L" ll.ll.ll",
	L".l '  ' l."
};
const vector<wstring> e2 = { // 7 x 4
	L" '...'",
	L" l'l'l",
	L".'l'l'.",
	L"' ' ' '"
};
const vector<wstring> e3 = {  // 8 x 4
	L"  '..'",
	L"l.'ll'.l",
	L"l'llll'l",
	L" .l  l."
};
const vector<wstring> e4 = { // 9 x 4
	L" .l...l.",
	L"ll..l..ll",
	L"l'l'l'l'l",
	L" ' ' ' '"
};
const vector<wstring> e5 = {
	L"	.l..l.",
	L".ll'll'll.",
	L"l llllll l",
	L"  .l  l."
};
const vector<vector<wstring>> e = {
	e1, e2, e3, e4, e5
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
const vector<wstring> GameOver = { // 54 x 3
	L".'''.  .'''.  l. .l  l'''    .'''.  l   l  l'''  l'''.",
	L"l  ..  l'''l  l ' l  l''     l   l  '. .'  l''   l'''.",
	L"'...'  l   l  l   l  l...    '...'   '.'   l...  l   l"
};
const vector<wstring> Skull = { // 22 x 12
	L"      ..........",
	L"   .llllllllllllll.",
	L" .llllllllllllllllll.",
	L"llllllllllllllllllllll",
	L"llllllllllllllllllllll",
	L"llll      ll      llll",
	L"ll        ll        ll",
	L"llllllllll''llllllllll",
	L" 'llllll      llllll'",
	L"   'llllllllllllll'",
	L"    ll  llllll  ll",
	L"        ''  '' "
};
// For playing sound
LPCWSTR song_intro{ L"play song_intro.wav" };
LPCWSTR song_game_1{ L"play song_game_1.wav" };
LPCWSTR song_game_2{ L"play song_game_2.wav" };
LPCWSTR song_game_3{ L"play song_game_3.wav" };
LPCWSTR song_game_4{ L"play song_game_4.wav" };
LPCWSTR song_game_5{ L"play song_game_5.wav" };
LPCWSTR click_menu{ L"play menu_click.wav" };
LPCWSTR start_level{ L"play start_level.wav" };
LPCWSTR pass_lane{ L"play pass_lane.wav" };
LPCWSTR pass_level{ L"play pass_level.wav" };
LPCWSTR game_over{ L"play game_over.wav" };
#define playSoundLoop(file_name) mciSendString(file_name, NULL, 0, NULL);
vector<int> duration = { 101, 119, 126, 145, 254 };
// Time
auto start = chrono::system_clock::now();
class cPlayer {
private:
	int X = 0, Y = 0;
	const vector<wstring> Sketch = {
		L"ll"
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
	int direction; // -1 left, 1 right
	int color;
	int X = 0, Y = 0;
	vector<wstring> Sketch;
public:
	cEnemy(int x, int y, vector<wstring> sketch) {
		X = x;
		Y = y;
		Sketch = sketch;
	}
	cEnemy(int x, int y, vector<wstring> sketch, int d, int c) {
		X = x;
		Y = y;
		Sketch = sketch;
		direction = d;
		color = c;
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
		int max = 0;
		for (int i = 0; i < Sketch.size(); i++)
			if (Sketch[i].length() > max)
				max = Sketch[i].length();
		return max;
	}
	int height() { return Sketch.size(); }
	vector<wstring> getSketch() { return Sketch; }
	void setSketch(vector<wstring> sketch) { Sketch = sketch; }
	void updatePos() {
		if (direction == -1) {
			if (X < 0)
				X = nScreenWidth;
			else moveLeft();
		}
		else if (direction == 1) {
			if (X + width() >= nScreenWidth)
				X = 0;
			else moveRight();
		}
	}
	int getColor() { return color; }
};
// Other utility functions
bool checkCollision(cPlayer player, cEnemy* enemy) {
	if (player.getX() >= enemy->getX() && player.getX() <= enemy->getX() + enemy->width() - 1 &&
		player.getY() >= enemy->getY() && player.getY() <= enemy->getY() + enemy->height() - 1)
		return true;
	return false;
}
wstring time_to_wstring(int t) {
	int m = t / 60;
	int s = t % 60;
	wstring res = L"0";
	res += L'0' + m;
	res += ':';
	res += L'0' + s / 10;
	res += L'0' + s % 10;
	return res;
}
// Global variables
int frame = 0;
int score = 0;
class cScreen {
private:
	// Character array for display
	WORD* pColor = new WORD[nScreenWidth * nScreenHeight];
	// Color array for display
	wchar_t* pBuffer = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole;
	DWORD dwBytesWritten = 0;
public:
	void gotoXY(int x, int y) {  // Place the cursor at (x, y)
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
	void FixConsoleWindow() {
		HWND consoleWindow = GetConsoleWindow();
		LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
		style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
		SetWindowLong(consoleWindow, GWL_STYLE, style);
	}
	void configure() {
		system("MODE 160, 46"); // Set screen size (width, height + 1)
		FixConsoleWindow(); //Fix window size
		// Make custom color palette - up to 16 colors, may update later
		HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); // A handle to console screen buffer.
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
	void drawScreenColor() {
		WriteConsoleOutputAttribute(hConsole, pColor, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
	void drawScreenBuffer() {
		WriteConsoleOutputCharacter(hConsole, pBuffer, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
	void gameOverEffect() {
		for (int i = 0; i < nScreenWidth; i++)
			for (int j = 0; j < nScreenHeight; j++)
				pColor[j * nScreenWidth + i] = 7 * 16 + 0;
		WriteConsoleOutputAttribute(hConsole, pColor, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		Sleep(100);
		for (int i = 0; i < nScreenWidth; i++)
			for (int j = 0; j < nScreenHeight; j++)
				pColor[j * nScreenWidth + i] = 0 * 16 + 7;
		WriteConsoleOutputAttribute(hConsole, pColor, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		Sleep(100);
		for (int i = 0; i < nScreenWidth; i++)
			for (int j = 0; j < nScreenHeight; j++)
				pColor[j * nScreenWidth + i] = 7 * 16 + 0;
		WriteConsoleOutputAttribute(hConsole, pColor, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		Sleep(100);
		for (int i = 0; i < nScreenWidth; i++)
			for (int j = 0; j < nScreenHeight; j++)
				pColor[j * nScreenWidth + i] = 0 * 16 + 7;
		WriteConsoleOutputAttribute(hConsole, pColor, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		Sleep(500);
	}
	void drawText(wstring content, int x, int y, int colorBackground, int colorCharacter) {
		for (int i = 0; i < content.length(); i++) {
			if (x + i < nScreenWidth && y < nScreenHeight) {
				pBuffer[y * nScreenWidth + x + i] = content[i];
				pColor[y * nScreenWidth + x + i] = colorBackground * 16 + colorCharacter;
			}
		}
	}
	void drawBlock(vector<wstring> Sketch, int X, int Y, int colorBackground, int colorChar) {
		for (int i = 0; i < Sketch.size(); i++) {
			for (int j = 0; j < Sketch[i].length(); j++) {
				if (X >= 0 && X < nScreenWidth && Y >= 0 && Y < nScreenHeight) { // Only draw if x, y is within screen
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
	}
	void drawProgressBar(int elapsed, int duration, int x, int y) {
		// Draw bar
		wstring bar;
		bar += L'[';
		for (int i = 0; i < 100; i++)
			bar += L' ';
		bar += L']';
		drawText(bar, x, y, darkblue, white);
		// Draw progress
		for (int i = 1; i <= elapsed * 100 / duration; i++) {
			drawBlock(L"l", x + i, y, black, white);
		}
		// Draw time
		drawText(time_to_wstring(elapsed), x - 6, y, black, white);
		drawText(time_to_wstring(duration), x + 104, y, black, white);
	}
	void drawBlock(wstring Sketch, int X, int Y, int colorBackground, int colorChar) {
		for (int j = 0; j < Sketch.length(); j++) {
			if (X >= 0 && X < nScreenWidth && Y >= 0 && Y < nScreenHeight) {
				if (Sketch[j] == '.') {
					pBuffer[(Y)*nScreenWidth + X + j] = L'▄';
					pColor[(Y)*nScreenWidth + X + j] = colorBackground * 16 + colorChar;
				}
				if (Sketch[j] == '\'') {
					pBuffer[(Y)*nScreenWidth + X + j] = L'▀';
					pColor[(Y)*nScreenWidth + X + j] = colorBackground * 16 + colorChar;
				}
				if (Sketch[j] == 'l') {
					pBuffer[(Y)*nScreenWidth + X + j] = L'█';
					pColor[(Y)*nScreenWidth + X + j] = colorBackground * 16 + colorChar;
				}
			}
		}
	}
	void drawFrame(int x, int y, int width, int height, int colorBackground, int colorChar) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (y + i >= 0 && y + i <= height - 1 && x + j >= 0 && j + x <= width - 1) {
					//// Conrners
					//pBuffer[y * nScreenWidth + x] = L'╔';
					//pBuffer[y * nScreenWidth + x + width - 1] = L'╗';
					//pBuffer[(y + height - 1) * nScreenWidth + x ] = L'╚';
					//pBuffer[(y + height - 1) * nScreenWidth + x + width - 1] = L'╝';
					//if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
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
	void animationWiggleUpDown(vector<wstring> content, int frame, int x, int y, int colorBackground, int colorCharacter) {
		int rate = 30;
		if (frame % rate >= 0 && frame % rate < rate / 4)
			drawBlock(content, x, y, colorBackground, colorCharacter);
		if (frame % rate >= rate / 4 && frame % rate < rate / 2)
			drawBlock(content, x, y - 1, colorBackground, colorCharacter);
		if (frame % rate >= rate / 2 && frame % rate < rate * 3 / 4)
			drawBlock(content, x, y, colorBackground, colorCharacter);
		if (frame % rate >= rate * 3 / 4 && frame % rate < rate)
			drawBlock(content, x, y + 1, colorBackground, colorCharacter);
	}
	void makeNewStarMap(int* starmap) {
		for (int i = 0; i < nScreenHeight; i++)
			for (int j = 0; j < nScreenWidth; j++)
				starmap[i * nScreenWidth + j] = 0;
		for (int i = 0; i < 50; i++) {
			int x = rand() % nScreenWidth, y = rand() % nScreenHeight;
			pBuffer[y * nScreenWidth + x] = L'.';
			starmap[y * nScreenWidth + x] = 1;
		}
	}
	void drawRectangle(int x, int y, int width, int height, int colorBackground, int colorChar) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pColor[i * nScreenHeight + j] = colorBackground * 16 + colorChar;
			}
		}
	}
	void drawStars(int* starmap) {
		for (int i = 0; i < nScreenHeight; i++) {
			for (int j = 0; j < nScreenWidth; j++) {
				if (starmap[i * nScreenWidth + j] == 1)
					pBuffer[i * nScreenWidth + j] = L'.';
			}
		}
	}
	// line: ═══════════
	void drawHorizontalLine1(int x, int y, int length, int colorBackground, int colorChar) {
		for (int i = 0; i < length; i++) {
			pBuffer[y * nScreenWidth + x + i] = L'═';
			pColor[y * nScreenWidth + x + i] = colorBackground * 16 + colorChar;
		}
	}
	// line: o o o o o o
	void drawHorizontalLine2(int x, int y, int length, int colorBackground, int colorChar) {
		for (int i = 0; i < length; i++) {
			if (i % 2 == 0)pBuffer[y * nScreenWidth + x + i] = L'o';
			else pBuffer[y * nScreenWidth + x + i] = L' ';
			pColor[y * nScreenWidth + x + i] = colorBackground * 16 + colorChar;
		}
	}
	// line: ------------
	void drawHorizontalLine3(int x, int y, int length, int colorBackground, int colorChar) {
		if (x >= 0 && x < nScreenWidth && y >= 0 && y < nScreenHeight) {
			for (int i = 0; i < length; i++) {
				if (i % 2 == 0)pBuffer[y * nScreenWidth + x + i] = L'-';
				else pBuffer[y * nScreenWidth + x + i] = L' ';
				pColor[y * nScreenWidth + x + i] = colorBackground * 16 + colorChar;
			}
		}
	}
	void glitchEffectText(wstring content, int X, int Y, int colorBackground1, int colorBackground2, int colorCharacter1, int colorCharacter2) {
		drawText(content, X, Y, colorBackground2, colorCharacter2); drawScreen();
		drawText(content, X, Y, colorBackground1, colorCharacter1); drawScreen();
		drawText(content, X, Y, colorBackground2, colorCharacter2); drawScreen();
	}
	void startMenuScreen() {
		// Intro song
		PlaySound(TEXT("song_intro.wav"), NULL, SND_ASYNC);
		// Configure screen
		configure();
		HANDLE hConsole1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole1);
		hConsole = hConsole1;
		// Make a starmap for background effect
		int* starmap = new int[nScreenWidth * nScreenHeight];
		// For menu option
		int choiceMenu = 0; // 0 - Start game, 1 - Load game, 2 - Settings, 3 - Exit

		// MENU SCREEN
		while (true) {
			// Background
			clearScreen(9, 7);
			if (frame % 15 == 0) makeNewStarMap(starmap);
			drawStars(starmap);
			// Reading input
			bool* bKey = new bool[key.size()];
			for (int i = 0; i < key.size(); i++) {
				bKey[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}
			// W - Move up
			if (bKey[0] == 1) {
				choiceMenu = (choiceMenu - 1) % 4;
				mciSendString(click_menu, NULL, 0, NULL);

			}
			// S - Move down
			if (bKey[2] == 1) {
				choiceMenu = (choiceMenu + 1) % 4;
				mciSendString(click_menu, NULL, 0, NULL);
			}
			// Display current menu
			int bg = black, ch = white;
			drawBlock(Title, 54, 15, bg, ch);
			int xMenu = 74, yMenu = 27;
			drawText(L" START GAME ", xMenu, yMenu, bg, ch);
			drawText(L"  LOAD GAME ", xMenu, yMenu + 1, bg, ch);
			drawText(L"  SETTINGS  ", xMenu, yMenu + 2, bg, ch);
			drawText(L"    EXIT    ", xMenu, yMenu + 3, bg, ch);
			drawText(L"Press W to move up, S to move down", xMenu - 10, yMenu + 5, 0, 7);
			if (choiceMenu == 0) {
				drawText(L" START GAME ", xMenu, yMenu, ch, bg);
			}
			else if (choiceMenu == 1 || choiceMenu == -3) {
				drawText(L"  LOAD GAME ", xMenu, yMenu + 1, ch, bg);
			}
			else if (choiceMenu == 2 || choiceMenu == -2) {
				drawText(L"  SETTINGS  ", xMenu, yMenu + 2, ch, bg);
			}
			else if (choiceMenu == 3 || choiceMenu == -1) {
				drawText(L"    EXIT    ", xMenu, yMenu + 3, ch, bg);
			}
			drawText(L"choice: " + to_wstring(choiceMenu), xMenu, yMenu + 6, 0, 7);
			drawText(L"Frame: " + to_wstring(frame), 2, nScreenHeight - 1, bg, ch);
			animationWiggleUpDown(e1, frame, 10, 20, black, red);
			animationWiggleUpDown(e2, frame, 22, 20, black, lightblue);
			animationWiggleUpDown(e3, frame, 30, 20, black, yellow);
			animationWiggleUpDown(e4, frame, 40, 20, black, green);
			drawScreen();
			// ENTER - Select
			if (GetAsyncKeyState(VK_RETURN)) {
				if (choiceMenu == 0) {
					glitchEffectText(L" START GAME ", xMenu, yMenu, 7, 6, 0, 7);
					startLoadScreen();
					startStage(1);
				}
				else if (choiceMenu == 1) {
					glitchEffectText(L"  LOAD GAME ", xMenu, yMenu + 1, 7, 6, 0, 7);
				}
				else if (choiceMenu == 2) {
					glitchEffectText(L"  SETTINGS  ", xMenu, yMenu + 2, 7, 6, 0, 7);
				}
				else if (choiceMenu == 3) {
					glitchEffectText(L"    EXIT    ", xMenu, yMenu + 3, 7, 6, 0, 7);
				}
			}
			frame++;
		}
	}
	void startLoadScreen() {
		clearScreen(darkblue, white);
		drawBlock(L"ll", 75, 22, darkblue, white);
		drawScreen();
		//mciSendString(menu_click, NULL, 0, NULL);
		Sleep(800);
		//clearScreen(darkblue, white);
		drawBlock(L"ll", 79, 22, darkblue, white);
		drawScreen();
		//mciSendString(menu_click, NULL, 0, NULL);
		Sleep(800);
		//clearScreen(darkblue, white);
		drawBlock(L"ll", 83, 22, darkblue, white);
		drawScreen();
		//mciSendString(menu_click, NULL, 0, NULL);
		Sleep(800);
	}
	void startStage(int stage) {
		start = chrono::system_clock::now();
		switch (stage) {
		case 1:		PlaySound(TEXT("song_game_1.wav"), NULL, SND_ASYNC); break;
		case 2:		PlaySound(TEXT("song_game_2.wav"), NULL, SND_ASYNC); break;
		case 3:		PlaySound(TEXT("song_game_3.wav"), NULL, SND_ASYNC); break;
		case 4:		PlaySound(TEXT("song_game_4.wav"), NULL, SND_ASYNC); break;
		case 5:		PlaySound(TEXT("song_game_5.wav"), NULL, SND_ASYNC); break;
		default: break;
		}
		startGameScreen(1, stage);
	}
	void startGameScreen(int level, int stage) {
		Sleep(400);
		// INITALISE GAME SCREEN
		// Sound
		mciSendString(start_level, NULL, 0, NULL);
		// Lane
		int nLane = 5 + level * 2; // Number of lanes
		int laneY = 10; // Y of lane1
		int laneSize = 5;
		bool* passed = new bool[nLane]; // Check passed lanes
		for (int i = 0; i < nLane; i++)
			passed[i] = false;
		//Initialise player
		cPlayer Player;
		Player.setXY(80, 1);
		//Initialise random enemies
		cEnemy** Enemy = new cEnemy * [nLane];
		for (int i = 0; i < nLane; i++) {
			int x = rand() % nScreenWidth;
			int y = laneY + i * laneSize;
			int en = rand() % 4;
			int c;
			switch (en) {
			case 0:
				c = red;
				break;
			case 1:
				c = yellow;
				break;
			case 2:
				c = lightblue;
				break;
			case 3:
				c = green;
				break;
			default:
				break;
			}
			int dir = (rand() % 2) * 2 - 1;
			Enemy[i] = new cEnemy(x, y, e[en], dir, c);
		}
		// For scrolling display
		int offset = 0;
		bool gameOver = false;
		// Starmap for background
		int* starmap = new int[nScreenWidth * nScreenHeight];
		int bg = 0, ch = 7; // Color for background
		while (gameOver == false) {
			// [1] CLEAR SCREEN
			clearScreen(bg, ch);
			drawBlock(Player.getSketch(), Player.getX(), Player.getY() + offset, darkblue, lightblue); // For shadow effect


			// [2] READ INPUT
			bool* bKeyGame = new bool[key.size()]; // Check ingame input
			for (int i = 0; i < key.size(); i++) { 	// Read input
				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
			}

			// [3] UPDATE 
			// Player position
			if (bKeyGame[0] == 1) { // W - Move up
				if (Player.getY() - 1 >= 0) {
					Player.moveUp();
					if (Player.getY() + offset <= 5 && Player.getY() > 5) {
						offset++;
					}
				}
			}
			if (bKeyGame[1] == 1) { // A - Move left
				if (Player.getX() - 2 >= 0)
					Player.moveLeft();
			}
			if (bKeyGame[2] == 1) { 	// S - Move down
				if (Player.getY() + 1 <= 18 + nLane * laneSize) {
					Player.moveDown();
					if (Player.getY() + offset + 5 >= nScreenHeight && Player.getY() + 5 <= 18 + nLane * laneSize) {
						offset--;
						//offsetChanged = true;
					}
				}
			}
			if (bKeyGame[3] == 1) { // D - move right
				if (Player.getX() + 2 <= nScreenWidth)
					Player.moveRight();
			}
			// Enemies position
			for (int i = 0; i < nLane; i++) {
				Enemy[i]->updatePos();
			}

			// [4] CHECK GAME LOGIC
			// Update time
			auto end = chrono::system_clock::now();
			chrono::duration<double> elapsed_seconds = end - start;
			int elapsed = elapsed_seconds.count();
			// Check lane pass
			bool newscore = false;
			for (int i = 0; i < nLane; i++) {
				if (Player.getY() >= laneY + i * 5 && passed[i] == false) {
					score += 10;
					newscore = true;
					passed[i] = true;
					playSoundLoop(pass_lane);
				}
			}
			// Check collision
			for (int i = 0; i < nLane; i++) {
				if (checkCollision(Player, Enemy[i]) == true) {
					gameOver = true;
				}
			}
			// Check level pass
			if (Player.getY() == 18 + nLane * laneSize) {
				startGameScreen(level + 1, stage);
			}
			// Check stage pass
			if (elapsed >= duration[stage - 1]) {
				startStage(stage + 1);
			}

			// DISPLAY GAME SCREEN
			// Stars
			if (frame % 15 == 0) makeNewStarMap(starmap);
			drawStars(starmap);
			// Lanes
			for (int i = 0; i <= nLane; i++)
				drawHorizontalLine3(0, laneY - 1 + i * laneSize + offset, nScreenWidth, bg, lightblue);
			// Player
			drawBlock(Player.getSketch(), Player.getX(), Player.getY() + offset, bg, 7);
			for (int i = 0; i < nLane; i++) {
				drawBlock(Enemy[i]->getSketch(), Enemy[i]->getX(), Enemy[i]->getY() + offset, bg, Enemy[i]->getColor());
			}
			// UI
			drawText(L"STAGE " + to_wstring(stage), 4, 4, bg, white);
			drawText(L"LEVEL " + to_wstring(level), 4, 3, bg, white);
			drawText(L"SCORE: " + to_wstring(score), 4, 2, 0, 7);
			drawProgressBar(elapsed, duration[stage - 1], 30, nScreenHeight - 1);
			drawText(L"Time elapsed: " + to_wstring(elapsed_seconds.count()), 2, nScreenHeight - 2, bg, ch);
			// Frame
			drawText(L"Frame: " + to_wstring(frame), 2, nScreenHeight - 1, bg, ch);
			// Render screen
			drawScreen();

			frame++;
		}
		gameOverScreen();
	}
	void gameOverScreen() {
		gameOverEffect();

		clearScreen(9, 7);
		drawBlock(GameOver, 53, 12, 9, 6);
		drawBlock(Skull, 69, 17, 9, 7);
		drawText(L"YOUR SCORE: " + to_wstring(score), 73, 31, 9, 7);
		PlaySound(TEXT("game_over.wav"), NULL, SND_ASYNC);
		drawScreen();
		Sleep(10000);
		exit(0);
	}
	void stageClearScreen() {

	}

};

int main() {
	cScreen Screen;
	Screen.startMenuScreen();
	return 0;
}




