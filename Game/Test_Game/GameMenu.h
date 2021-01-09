#pragma once
#include <vector>
#include <string>
#include "Items.h"
using namespace std;

class GameMenu : public Items {
protected:
	int x, y;
public:
	GameMenu() : x(0), y(0), Items("GameMenu") {};
	GameMenu(int x, int y, string key) : x(x), y(y), Items(key) {};
	
	coord getPos();
	void setPos(coord c);
};