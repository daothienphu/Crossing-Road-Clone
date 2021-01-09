#include "GameMenu.h"

GameMenu::GameMenu() : x(0), y(0), Items("GameMenu") {};
GameMenu::GameMenu(int x, int y, string key) : x(x), y(y), Items(key) {};

coord GameMenu::getPos()
{
	return { x,y };
}
void GameMenu::setPos(coord c) {
	x = c.x;
	y = c.y;
}
