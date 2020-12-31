#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>

#include "Header.h"
#include "GameCore.h"

#pragma region GameObject

class GameObject {
private:
protected:
	int x, y; // coordinate of top-left corner
	int oldX, oldY;
	int w, h; // box size
	int row;  // path number for checking collision
public:
	GameObject() : x(0), y(0), oldX(0), oldY(0), w(0), h(0), row(0) {}
	GameObject(int x, int y, int w, int h, int row) : x(x), y(y), oldX(0), oldY(0), w(w), h(h), row(row) {}

	virtual void move(int x, int y)
	{
		this->x += x;
		this->y += y;
	}

	coord getPos() {
		return { x, y };
	}
	coord getOldPos() {
		return { oldX, oldY };
	}
	BOUNDINGBOX getBoundingBox() {
		return { x,y,w,h };
	}


	//virtual void render(int bgColor = 0, int charColor = 7) {
	//	GameCore::pColor[y * screenWidth + x] = bgColor * 16 + charColor;
	//	GameCore::pBuffer[y * screenWidth + x] = L'▄';
	//};

	virtual bool collision(GameObject& other) {
		//if (other.getBoundingBox() bla bla bla getBoundingBox()) { bla bla bla };
		return 0;
	};
};