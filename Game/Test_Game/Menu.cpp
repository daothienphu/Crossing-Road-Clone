#include "Menu.h"

Button::Button() : GameMenu(0, 0, "Unnamed Button") {};
Button::Button(int x, int y, string key) : GameMenu(x, y, key) {};
Button::Button(string key) : GameMenu(0, 0, key) {};