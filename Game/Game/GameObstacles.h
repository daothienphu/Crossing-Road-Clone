#pragma once
#include "GameObject.h"

class Obstacle : public GameObject {
private:
protected:
	int veclocity;
	DIRECTION direction; // may need a direction
public:
	Obstacle() : GameObject(), veclocity(0), direction(DIRECTION::RIGHT) {}
	Obstacle(int x, int y, int w, int h, int row, int veclocity, DIRECTION direction = DIRECTION::RIGHT)
		: GameObject(x, y, w, h, row), veclocity(veclocity), direction(direction) {}

	void move(int x, int y)
	{
		if(direction == DIRECTION::RIGHT)
		{
			this->x += x;
			this->y += y;
		}
		else {
			this->x -= x;
			this->y += y;
		}
	}
	//void collision();
};

#pragma region Obstacles

class Something : public Obstacle {};
class Will : public Obstacle {};
class BeDefineLater : public Obstacle {};
#pragma endregion

