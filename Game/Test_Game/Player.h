﻿#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
using namespace std;

class Player : public GameObject {
protected:
public:
	Player() : GameObject(0, 0, 0, 0, "player") {}
	Player(int x, int y, int w, int h) : GameObject(x, y, w, h, "player") {}

	virtual void move(int x, int y)
	{
		this->x += 2 * x;
		this->y += y;
	}
};