#pragma once
#include <vector>
#include <string>
#include "Items.h"
#include "Menu.h"
using namespace std;

class GameMenu : public Items {
protected:
	vector<Menu*> compo; //components;
	vector<wstring> bufferData;
public:
	vector<wstring>& getBufferData() {
		return bufferData;
	};
	void add(Menu* menu) {
		return;
	}
	coord getPos()
	{
		return { 0, 0 };
	}

};