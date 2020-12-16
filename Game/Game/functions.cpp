#include "Header.h"

#pragma region Util
void fixSizedConsoleWindow() {
    RECT windowRes;
    const HWND window = GetDesktopWindow();
    GetWindowRect(window, &windowRes);

    HWND consoleWindow = GetConsoleWindow();
    MoveWindow(consoleWindow, (windowRes.right - 1080) / 2, (windowRes.bottom - 720) / 2, 1080, 720, TRUE);

    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);

    SetWindowLong(consoleWindow, GWL_STYLE, style);

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void printPalette() {
    int i = 30;
    while (i < 108) {
        string res = "";
        int j = i;
        while (j) {
            char tmp = char(j % 10 + '0');
            res = tmp + res;
            j /= 10;
        }

        string color = "\x1B[" + res + 'm';
        cout << color << setw(5) << i;

        switch (i) {
        case 37:
        case 97: i += 3; cout << endl; break;
        case 47: i += 43; cout << endl << blackBG50; break;
        case 107: cout << blackBG50 << white50;
        default: i++; break;
        }
    }
}
#pragma endregion

#pragma region GameObject

class GameObject {
private:
protected:
	int x, y; // coordinate of bottom-left corner
	int w, h; // box size
	int row; // path number for checking collision
public:
	GameObject() : x(0), y(0), w(0), h(0), row(0) {}
	GameObject(int x, int y, int w, int h, int row) : x(x), y(y), w(w), h(h), row(0) {}

	virtual void move() = 0;
	virtual void render() = 0;
	//virtual void collision() = 0;
};

enum Direction { LEFT, RIGHT };

class Obstacle : public GameObject {
private:
protected:
	int veclocity;
	Direction direction; // may need a direction
public:
	Obstacle() : veclocity(0), direction(RIGHT) {}
	Obstacle(int veclocity, Direction direction = RIGHT) : veclocity(veclocity), direction(direction) {}

	void move();
	void render() = 0;
	//void collision();
};

#pragma region Obstacles
class Car : public Obstacle{};
class Dino : public Obstacle{};
class Bird : public Obstacle{}l
#pragma endregion

class Player : public GameObject {
private:
protected:
public:
	void move();
	void render();
};
#pragma endregion