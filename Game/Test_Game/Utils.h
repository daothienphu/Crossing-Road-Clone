#pragma once
#include <chrono>
#include <thread>
#include <windows.h>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
#define FRAMERATE 60
#define screenWidth 145
#define screenHeight 41
#define LANE_HEIGHT 7
#define LEAST_SPACE 10
#define NUM_ENEMY 8
#define MAX_ENEMY_WIDTH 10
#define BG black
#define YELLOW_LIGHT_SECS 1
enum { blueDark = 0, blueLight, orange, yellow, green, purple, red, whiteDark, white, black, brown, pink };

#pragma region structs 
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
#pragma endregion

#pragma region Utils
void fixSizedConsoleWindow();
int random(int a, int b);
void gotoXY(int x, int y);
bool delay(int millisec);
wstring toWstring(int a);
void toVwstring(int a, vector<wstring>& result);
#pragma endregion