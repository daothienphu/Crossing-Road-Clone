#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
using namespace std;

class Obstacles : public GameObject {
protected:
	int autoX = 1, autoY = 0;
public:
	Obstacles() : GameObject(0, 0, 0, 0, "unknownObstacles") {}
	Obstacles(int x, int y, int w, int h, string bufferKey) : GameObject(x, y, w, h, bufferKey) {}

	virtual void move(int x, int y)
	{
		this->oldX = this->x;
		this->oldY = this->y;
		this->x += x;
		this->y += y;
	}
	virtual void resetPos(int lane, bool left = true) {
		this->x = left? 0 : 137;
		this->y = lane * 5;
	}
};

class Maybe : public Obstacles {
	vector<wstring> buf;
public:
	Maybe() : Obstacles(0, 0, 0, 0, "maybe") {}
	Maybe(int x, int y, int w, int h) : Obstacles(x, y, w, h, "maybe") {
	}
};

class SomeKindsOf : public Obstacles {
	vector<wstring> buf;
public:
	SomeKindsOf() : Obstacles(0, 0, 0, 0, "SomeKindsOf") {}
	SomeKindsOf(int x, int y, int w, int h) : Obstacles(x, y, w, h, "SomeKindsOf") {
		//this->bufferData = this->buf;
	}
};

class Monster :public Obstacles {
	vector<wstring> buf;
public:
	Monster() : Obstacles(0, 0, 0, 0, "Monster") {}
	Monster(int x, int y, int w, int h) : Obstacles(x, y, w, h, "Monster") {
		//this->bufferData = this->buf;
	}
};

//fell free to declare more class using the above template
//feel*