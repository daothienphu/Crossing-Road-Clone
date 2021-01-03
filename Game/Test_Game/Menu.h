#pragma once
#include <vector>
#include "GameMenu.h"

class Button : public GameMenu {
protected:

public:
	Button() : GameMenu(0, 0, "Unnamed Button") {};
	Button(int x, int y, string key) : GameMenu(x, y, key) {};
	Button(string key) : GameMenu(0, 0, key) {};
};