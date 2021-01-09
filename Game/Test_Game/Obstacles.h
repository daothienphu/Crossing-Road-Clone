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

	void move(int x, int y);
	virtual void resetPos(bool left = true);

	void render(GraphicsController*& graphic, int offset);
	void render(GraphicsController*& graphic, int offset, int bg);
	void render(GraphicsController*& graphic, int offset, int bg, int ch);
	void clearOldPos(GraphicsController*& graphic);

	void setPos(int x, int y);

	bool isOutOfBound();

	int getTick();
};

//fell free to declare more class using the above template
//feel*