#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
using namespace std;

class Obstacles : public GameObject {
protected:
	int autoX = 1, autoY = 0;;
public:
	Obstacles() : GameObject(0, 0, 0, 0) {}
	Obstacles(int x, int y, int w, int h) : GameObject(x, y, w, h) {}

	virtual void move(int x, int y)
	{
		this->x += autoX;
		this->y += autoY;
	}
};

class Maybe : public Obstacles {
	vector<wstring> buf;
public:
	Maybe() : Obstacles(0, 0, 0, 0) {}
	Maybe(int x, int y, int w, int h) : Obstacles(x, y, w, h) {
		this->bufferData = buf;
	}
};

class SomeKindsOf : public Obstacles {
	vector<wstring> buf;
public:
	SomeKindsOf() : Obstacles(0, 0, 0, 0) {}
	SomeKindsOf(int x, int y, int w, int h) : Obstacles(x, y, w, h) {
		this->bufferData = this->buf;
	}
};

class Monster :public Obstacles {
	vector<wstring> buf;
public:
	Monster() : Obstacles(0, 0, 0, 0) {}
	Monster(int x, int y, int w, int h) : Obstacles(x, y, w, h) {
		this->bufferData = this->buf;
	}
};

//fell free to declare more class using the above template