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

	void update();

	void move(int x, int y);

	void render(GraphicsController*& graphic, int offset);
	void render(GraphicsController*& graphic, int offset, int bg, int ch);

	void clearOldPos(GraphicsController*& graphic);

	void setPos(int x, int y);
};