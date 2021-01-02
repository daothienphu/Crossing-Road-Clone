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
public:
	virtual vector<wstring>& getBufferData() = 0;
	virtual coord getPos() = 0;
};


class Menu {
protected:
	vector<wstring> bufferData;
public:
	Menu() {
		bufferData.clear();
	}
	~Menu() = default;
	vector<wstring>& getBufferData() {
		return bufferData;
	}
};
class Button : public Menu {
public:
	Button() {
		bufferData.emplace_back(L"Unnamed Button");
	}
	Button(wstring text) {
		bufferData.emplace_back(text);
	}
	~Button() = default;

	void setButtonText(wstring text) {
		bufferData.emplace_back(text);
	}
};
class Text: public Menu {
public:
	Text() {
		bufferData.emplace_back(L"SomeText");
	}
	Text(wstring text) {
		bufferData = text;
	}
	~Text() = default;

	void setText(wstring text) {
		bufferData = text;
	}
};
class GameMenu: public Items{
protected:
	vector<Menu*> compo; //components;
	vector<wstring> bufferData;
public:
	vector<wstring>& getBufferData() {
		return bufferData;
	};
	void add(Menu* menu, int spacing) {
		if (!compo.empty())
			for (int i = 0; i < spacing; ++i) {
				bufferData.emplace_back(L" ");
			}
		bufferData.emplace_back(menu->getBufferData());
		//////add something more for vertical centering
		compo.emplace_back(menu);
	}
	coord getPos()
	{
		return {0, 0};
	}

};

class Lane {
protected:
	vector<wstring> BufferData;
public:
	//setBufferData
	vector<wstring>& getBufferData() {
		return BufferData;
	}
};
class Map : public Items {
protected:
	vector<Lane> lanes;
	vector<wstring> bufferData;
public:
	Map() {
		lanes.clear();
		bufferData.clear();
	}
	~Map() {
		lanes.clear();
		bufferData.clear();
	}

	vector<wstring>& getBufferData() {
		return bufferData;
	}

	void add(Map* lane, int spacing) {
		if (!lanes.empty())
			for (int i = 0; i < spacing; ++i) {
				bufferData.emplace_back(L" ");
			}
		vector<wstring> tmp = lane->getBufferData();
		for (int i = 0; i < tmp.size(); ++i) {
			bufferData.emplace_back(tmp[i]);
		} //////add something more for vertical centering
		lanes.emplace_back(lane);
	}
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

	void startMainScreen() {
		Items* startMenu = new GameMenu;
		Button b(L" START GAME ");
		

		graphic->setBuffer(startMenu->getBufferData(), 0, 0, 0, 7);
	}

	void start() {
		
	}
};


int main() {
	GameCore gc;
	gc.start();
}