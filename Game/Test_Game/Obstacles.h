#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
#include "Utils.h"
using namespace std;

class Obstacles : public GameObject {
private:
	int speed = 0, tick = 0, bgColor, fgColor;
protected:
	int autoX = 1, autoY = 0;
public:
	Obstacles() : GameObject(0, 0, 0, 0, "unknownObstacles") {}
	Obstacles(int x, int y, int _speed, int _bgColor, int _fgColor, string bufferKey, GraphicsController*& graphic) : 
		GameObject(x, y, graphic->getBuffer(bufferKey)[0].size(), graphic->getBuffer(bufferKey).size(), bufferKey), 
		speed(_speed),
		bgColor(_bgColor),
		fgColor(_fgColor)
	{}

	void move(int x, int y)
	{
		tick++;

		// Check if enough ticks yet
		if (tick < speed)
			return; //Nah, not enough
		
		tick %= speed;
		this->oldX = this->x;
		this->oldY = this->y;
		this->x += x;
		this->y += y;

		if (isOutOfBound())
			resetPos(x > 0);
	}
	virtual void resetPos(bool left = true) {
		this->x = left? -w + 1 : screenWidth;
	}

	void render(GraphicsController*& graphic) {
		clearOldPos(graphic);
		graphic->setBuffer(graphic->getBuffer(bufferKey), this->x, this->y, bgColor, fgColor);
	}

	void clearOldPos(GraphicsController*& graphic) {
		GameObject::clearOldPos(graphic, bgColor, fgColor);
	}

	void setPos(int x, int y) {
		this->x = x;
		this->oldX = x;
		this->y = y;
		this->oldY = y;
	}

	bool isOutOfBound() {
		return x + w < 1 || x > screenWidth;
	}

	int getTick() {
		return tick;
	}
};

class Enemy1 : public Obstacles {
public:

};

//class Maybe : public Obstacles {
//	vector<wstring> buf;
//public:
//	Maybe() : Obstacles(0, 0, 0, 0, "maybe") {}
//	Maybe(int x, int y, int w, int h) : Obstacles(x, y, w, h, "maybe") {
//	}
//};
//
//class SomeKindsOf : public Obstacles {
//	vector<wstring> buf;
//public:
//	SomeKindsOf() : Obstacles(0, 0, 0, 0, "SomeKindsOf") {}
//	SomeKindsOf(int x, int y, int w, int h) : Obstacles(x, y, w, h, "SomeKindsOf") {
//		//this->bufferData = this->buf;
//	}
//};
//
//class Monster :public Obstacles {
//	vector<wstring> buf;
//public:
//	Monster() : Obstacles(0, 0, 0, 0, "Monster") {}
//	Monster(int x, int y, int w, int h) : Obstacles(x, y, w, h, "Monster") {
//		//this->bufferData = this->buf;
//	}
//};

//fell free to declare more class using the above template
//feel*