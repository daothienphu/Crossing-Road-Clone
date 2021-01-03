#pragma once
#include <vector>

class Menu {
protected:
public:
};

class Button : public Menu {
protected:
	vector<wstring> bufferData;
public:
};
class Text : public Menu {
	//x, y, content, bg and fg color, w h
protected:
	vector<wstring> bufferData;
public:
};