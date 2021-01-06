#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
using namespace std;

class Player : public GameObject {
protected:
public:
	Player() : GameObject(0, 0, 0, 0, "player") {}
	Player(GraphicsController*& graphic) :
		GameObject(0, 0, graphic->getBuffer("player")[0].size(), graphic->getBuffer("player").size(), "player") {}
	Player(int x, int y, GraphicsController*& graphic) : 
		GameObject(x, y, graphic->getBuffer("player")[0].size(), graphic->getBuffer("player").size(), "player") {}

	void move(int x, int y)
	{
		this->oldX = this->x;
		this->oldY = this->y;
		this->x += 2 * x;
		this->y += y;
	}

	void render(GraphicsController*& graphic) {
		clearOldPos(graphic);
		graphic->setBufferWhite(graphic->getBuffer(bufferKey), x, y, BG, 7);
	}

	void clearOldPos(GraphicsController*& graphic) {
		GameObject::clearOldPos(graphic, BG, 7);
	}

	void setPos(int x, int y) {
		this->x = x;
		this->y = y;
	}
};