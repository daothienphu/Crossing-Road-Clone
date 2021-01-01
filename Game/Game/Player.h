#pragma once
#include "GameObject.h"

#pragma region PLAYER CONFIG

#define PLAYER_H 50
#define PLAYER_W 50

#pragma endregion

class Player : public GameObject {
private:
	//sprite or render storage will be here
protected:
public:
	Player() : GameObject() {}
	Player(int x, int y, int w = PLAYER_W, int h = PLAYER_H) : GameObject(x, y, w, h, 0) {}
};
#pragma endregion

