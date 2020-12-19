#include <Windows.h>
#include <string>
#include<iostream>
#include<vector>
using namespace std;

#define nScreenWidth 100
#define nScreenHeight 40

const wstring detail = L" ▄▀█▓░╚╝╔╗║═";

void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Place the cursor at (x, y)
}

void printTitle(int x, int y) {
	// width = 52, height = 8
	// Get error in char, string, use wstring
	gotoXY(x, y);     cout << L"▄▀▀▀▄  █▀▀▀▄  ▄▀▀▀▄  ▄▀▀▀   ▄▀▀▀   ▀█▀  █▄  █  ▄▀▀▀▀" << endl;
	gotoXY(x, y + 1); cout << L"█      █▀▀▀▄  █   █   ▀▀▀▄   ▀▀▀▄   █   █ ▀▄█  █ ▀▀█" << endl;
	gotoXY(x, y + 2); cout << L"▀▄▄▄▀  █   █  ▀▄▄▄▀  ▀▄▄▄▀  ▀▄▄▄▀  ▄█▄  █   █  ▀▄▄▄█" << endl;
	gotoXY(x, y + 3); cout << L" " << endl;
	gotoXY(x, y + 4); cout << " " << endl;
	gotoXY(x, y + 5); cout << L"             █▀▀▀▄  ▄▀▀▀▄  ▄▀▀▀▄  █▀▀▀▄" << endl;
	gotoXY(x, y + 6); cout << L"             █▀▀▀▄  █   █  █▄▄▄█  █   █" << endl;
	gotoXY(x, y + 7); cout << L"             █   █  ▀▄▄▄▀  █   █  █▄▄▄▀" << endl;
}

class cPlayer {
public:
	int X = 0, Y = 0;
	const vector<wstring> show = {
		L"."
	};
};

void color(int x) //Change text color to color x
{
	HANDLE hconsoleColor;
	hconsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsoleColor, x);
}

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

void drawFrame(wchar_t*& pBuffer, WORD*& pColor, int x, int y, int width, int height) {
	for (int i = 0; i < nScreenWidth; i++) { // x iterator
		for (int j = 0; j < nScreenHeight; j++) { // y iterator
			// Corners
			if (i == 0 && j == 0)
				pBuffer[i * nScreenHeight + j] = L'╔';
			else if (i == 0 && j == width - 1)
				pBuffer[i * height + j] = L'╚';
			else if (i == height - 1 && j == 0)
				pBuffer[i * height + j] = L'╔';
			else if (i == height - 1 && j == width - 1)
				pBuffer[i * height + j] = L'╚';
			// Sides
			if ((i == 0 && (j >= 1 && j < width - 1)) && (i == height - 1 && (j >= 1 && j < width - 1)))
				pBuffer[i * height + j] = L'═';
			if ((j == 0 && (i >= 1 && j < height - 1)) && (j == height - 1 && (i >= 1 && i < height - 1)))
				pBuffer[i * height + j] = L'║';
		}
	}
	// Fix here
}



const vector<wstring> enemy = {
	L"llll",
	L"llll"
};

void draw(wchar_t*& pBuffer, WORD*& pColor, int X, int Y, vector<wstring> str, int colorBackground, int colorChar) {
	//cout << "Bug" << endl;
		// background_color * 16 + character_color
	DWORD dwBytesWritten = 0;
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

int main() {
	//Configure();
	//printTitle(0, 0);
	game();
	return 0;
}