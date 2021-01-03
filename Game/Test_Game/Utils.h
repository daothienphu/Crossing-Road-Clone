#pragma once
struct coord {
	int x, y;
};

struct BOUNDINGBOX {
	int x = 0, y = 0;
	int w = 0, h = 0;
	coord topLeft() {
		return { x,y };
	}
	coord topRight() {
		return { x + w, y };
	}
	coord bottomLeft() {
		return { x,y + h };
	}
	coord bottomRight() {
		return { x + w, y + h };
	}
};

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

#pragma region game config
#define FRAMERATE 50
#define screenWidth 145
#define screenHeight 40
enum GAMESTATE { PLAYING, PAUSE, EXIT };
enum DIRECTION { LEFT, RIGHT };
#pragma endregion

#pragma region global variables
using namespace std;
//const vector<char> key = { 'W', 'A', 'S', 'D', 'P', 'R' };
#pragma endregion

#pragma region Util
void fixSizedConsoleWindow() {
	system("MODE 145, 40"); // Set screen size (width, height + 1)
	//Fix window size
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
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
void gotoXY(int x, int y);
void printPalette();

bool delay(int millisec)
{
	sleep_for(milliseconds(millisec));
	return true;
}
#pragma endregion