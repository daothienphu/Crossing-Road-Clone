#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
using namespace std;

class Player : public GameObject {
protected:
public:
	Player() : GameObject(0, 0, 0, 0, "player") {}
	Player(int x, int y, GraphicsController*& graphic) : 
		GameObject(x, y, graphic->getBuffer("player")[0].size(), graphic->getBuffer("player").size(), "player") {}

	void move(int x, int y, GraphicsController*& graphic)
	{
		this->oldX = this->x;
		this->oldY = this->y;
		this->x += 2 * x;
		this->y += y;

		clearOldPos(graphic);
		render(graphic, 0, 7);
	}
};