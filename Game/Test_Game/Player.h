#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
using namespace std;

class Player : public GameObject {
protected:
	vector<wstring> buf;
public:
	Player() : GameObject(0, 0, 0, 0)
	{
		buf = { L"█-█",
				L"█-█" }; //draw player here
		bufferData = buf;
	}
	Player(int x, int y, int w, int h) : GameObject(x, y, w, h)
	{
		buf = { L"." };
		bufferData = buf;
	}

	virtual void move(int x, int y)
	{
		this->x += 2 * x;
		this->y += y;
	}
};