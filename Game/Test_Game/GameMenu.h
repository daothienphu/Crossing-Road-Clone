#pragma once
#include <vector>
#include <string>
#include "Items.h"
#include "Menu.h"
using namespace std;

class GameMenu : public Items {
protected:
	vector<Menu*> compo; //components;
public:
	GameMenu() : Items("GameMenu") {}

	void add(Menu* menu) {
		return;
	}

	coord getPos()
	{
		return { 0, 0 };
	}

};