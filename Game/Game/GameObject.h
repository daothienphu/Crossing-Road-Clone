#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>

#include "GameGraphic.h"
#include "Header.h"


#pragma region GameObject

class GameObject {
private:
protected:
	int x, y; // coordinate of bottom-left corner
	int w, h; // box size
	int row;  // path number for checking collision
public:
	GameObject() : x(0), y(0), w(0), h(0), row(0) {}
	GameObject(int x, int y, int w, int h, int row) : x(x), y(y), w(w), h(h), row(0) {}

	virtual void move(int x, int y)
	{
		this->x += x;
		this->y += y;
	}
	virtual void render() = 0;
	//virtual void collision() = 0;
};