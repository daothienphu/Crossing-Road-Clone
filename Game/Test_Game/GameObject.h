#pragma once
#include "Items.h"

class GameObject : public Items {
protected:
	int x, y; // coordinate of top-left corner
	int w, h; // box size
	vector<wstring> bufferData;
public:
	GameObject() : x(0), y(0), w(0), h(0), bufferData({ L" " }) {}
	GameObject(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

	coord getPos() {
		return { x, y };
	}
	BOUNDINGBOX getBoundingBox() {
		return { x,y,w,h };
	}

	virtual vector<wstring>& getBufferData() {
		return bufferData;
	};

	virtual void move(int x, int y) = 0;
};