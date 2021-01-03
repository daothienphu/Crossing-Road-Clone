#pragma once
#include "Items.h"
#include <string>
#include "Utils.h"

using namespace std;

class GameObject : public Items {
protected:
	int x, y; // coordinate of top-left corner
	int w, h; // box size
public:
	GameObject() : x(0), y(0), w(0), h(0), Items() {}
	GameObject(int x, int y, int w, int h, string bufferKey) : Items(bufferKey), x(x), y(y), w(w), h(h) {}

	coord getPos() {
		return { x, y };
	}
	BOUNDINGBOX getBoundingBox() {
		return { x,y,w,h };
	}

	virtual void move(int x, int y) = 0;
};