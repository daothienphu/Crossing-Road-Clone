#pragma once
#include <iostream>
#include <windows.h>
using namespace std;

#pragma region Util
void fixSizedConsoleWindow();
void gotoXY(int x, int y);
#pragma endregion

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

	virtual void move() = 0;
	virtual void render() = 0;
	//virtual void collision() = 0;
};

enum Direction { LEFT, RIGHT };

class Obstacle : public GameObject {
private:
protected:
	int veclocity;
	Direction direction; // may need a direction
public:
	Obstacle() : GameObject(), veclocity(0), direction(RIGHT) {}
	Obstacle(int x, int y, int w, int h, int row, int veclocity, Direction direction = RIGHT) 
		: GameObject(x, y, w, h, row), veclocity(veclocity), direction(direction) {}

	void move();
	void render() = 0;
	//void collision();
};

#pragma region Obstacles
class Car : public Obstacle {};
class Dino : public Obstacle {};
class Bird : public Obstacle {};
#pragma endregion

class Player : public GameObject {
private:
protected:
public:
	Player() : GameObject() {}
	Player(int x, int y, int w, int h) : GameObject(x, y, w, h, 0) {}
	void move();
	void render();
};
#pragma endregion