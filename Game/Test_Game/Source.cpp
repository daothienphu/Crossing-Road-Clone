#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

#pragma region game config
#define GAME_RATE 50
#define screenWidth 145
#define screenHeight 40
enum GAMESTATE { PLAYING, PAUSE, EXIT };
enum DIRECTION { LEFT, RIGHT };
#pragma endregion

#pragma region global variables
using namespace std;
const vector<char> key = { 'W', 'A', 'S', 'D', 'P', 'R' };
const vector<wstring> Title = {
	L".'''.  l'''.  .'''.  .'''   .'''   'l'  l.  l  .''''",
	L"l      l'''.  l   l   '''.   '''.   l   l '.l  l ''l",
	L"'...'  l   l  '...'  '...'  '...'  .l.  l   l  '...l",
	L" ",
	L"             l'''.  .'''.  .'''.  l'''.",
	L"             l'''.  l   l  l...l  l   l",
	L"             l   l  '...'  l   l  l...'",
};
#pragma endregion

#pragma region Util
void fixSizedConsoleWindow();
void gotoXY(int x, int y);
void printPalette();

bool delay(int millisec);


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

class Items {
protected:
	GraphicsController gc;
public:
	virtual vector<wstring>& getBufferData() = 0;
	virtual coord getPos() = 0;
};


class Menu {
protected:
public:
};
class Button : public Menu {
protected:
	vector<wstring> bufferData;
public:
};
class Text: public Menu {
	//x, y, content, bg and fg color, w h
protected:
	vector<wstring> bufferData;
public:
};
class GameMenu: public Items{
protected:
	vector<Menu*> compo; //components;
	vector<wstring> bufferData;
public:
	vector<wstring>& getBufferData() {
		return bufferData;
	};
	void add(Menu* menu) {
		return;
	}
	coord getPos()
	{
		return {0, 0};
	}

};

class Lane {
protected:
public:
};
class Map : public Items {
protected:
	vector<Lane> lanes;
public:
};

class GameObject: public Items {
protected:
	int x, y; // coordinate of top-left corner
	int w, h; // box size
	vector<wstring> bufferData;
public:
	GameObject() : x(0), y(0), w(0), h(0), bufferData({L" "}) {}
	GameObject(int x, int y, int w, int h, vector<wstring> bufferData) : x(x), y(y), w(w), h(h), bufferData(bufferData) {}

	coord getPos() {
		return { x, y };
	}
	BOUNDINGBOX getBoundingBox() {
		return { x,y,w,h };
	}

	virtual vector<wstring>& getBufferData() {
		return bufferData;
	};
};
class Obstacles: public GameObject {
protected:
public:
	Obstacles() : GameObject(0, 0, 0, 0, { L" " }) {}
	Obstacles(int x, int y, int w, int h, vector<wstring> bufferData) : GameObject(x, y, w, h, bufferData) {}
};

#pragma region OBSTACLES LIST
class Maybe : public Obstacles {
	const vector<wstring> bufferData = {L""};
public:
	Maybe() : Obstacles(0, 0, 0, 0, this->bufferData) {}
	Maybe(int x, int y, int w, int h) : Obstacles(x, y, w, h, this->bufferData) {}
};

class SomeKindsOf : public Obstacles {
	const vector<wstring> bufferData = {L""}; //fill in here
public:
	SomeKindsOf() : Obstacles(0, 0, 0, 0, this->bufferData) {}
	SomeKindsOf(int x, int y, int w, int h) : Obstacles(x, y, w, h, this->bufferData) {}
};

class Monster :public Obstacles {
	const vector<wstring> bufferData = {L""};
public:
	Monster() : Obstacles(0, 0, 0, 0, this->bufferData) {}
	Monster(int x, int y, int w, int h) : Obstacles(x, y, w, h, this->bufferData) {}
};

//fell free to declare more class using the above template
#pragma endregion


class Player : public GameObject {
protected:
	const vector<wstring> bufData = { L"" }; //draw the player here
public:
	Player() : GameObject(0, 0, 0, 0, this->bufData) {}
	Player(int x, int y, int w, int h) : GameObject(x, y, w, h, this->bufData) {}


};


class GraphicsController{
protected:
	wchar_t* buffer = new wchar_t[screenHeight * screenWidth];
	WORD* color = new WORD[screenHeight * screenWidth];

	HANDLE hConsole;
	DWORD dwBytesWritten;
public:
	void render() {
		for (int i = 0; i < screenHeight; i++)
		{
			for (int j = 0; j < screenWidth; j++)
			{
				COORD cPos;
				cPos.X = j;
				cPos.Y = i;
				WriteConsoleOutputAttribute(hConsole, &color[i * screenWidth + j], 1, cPos, &dwBytesWritten);
			}
		}
		WriteConsoleOutputCharacter(hConsole, buffer, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
	}
	void setBuffer(vector<wstring>& content, int x, int y, int bgColor, int fgColor) {
		for (int i = 0; i < content.size(); ++i) {
			for (int j = 0; j < content[i].length(); ++j) {
				buffer[y * screenWidth + x + j] = content[i].at(j);
				color[y * screenWidth + x + j] = bgColor * 16 + fgColor;
			}
		}
	}
};


class GameCore{
protected:
	vector<Items*> menuHier; //hierarchy
	Items* player;

	GraphicsController* graphic;

public:
	GameCore() {
		player = new Player;
		graphic = new GraphicsController;
	}
	~GameCore() {
		for (int i = 0; i < menuHier.size(); ++i)
			delete menuHier[i];

		delete graphic;
	}

	void start() {
		Items* startMenu = new GameMenu;

		//graphic->setBuffer(startMenu.getBufferData(), 0,0,0,7);
	}
};


int main() {
	GameCore gc;
	gc.start();
}