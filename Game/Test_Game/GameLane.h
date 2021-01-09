#pragma once
#include "Obstacles.h"
#include "Items.h"

class GameLane : public Items {
private:
	vector <Obstacles*> obs;
	int light = 0;
	bool passed;
	bool newPass;
	// 0: green
	// 1: yellow
	// 2: red
	int velocity, level, lane, dir, curTime = 0, green, red;
public:
	GameLane(int lane, int level, int dir, int green, int red, GraphicsController*& graphic);
	// For level mode
	GameLane(int lane, int level, int dir, int green, int red, GraphicsController*& graphic, int bg, bool order, int Level);

	~GameLane();

	void setPassed(bool s);
	void setNewPassed(bool s);
	bool Passed();
	bool NewPass();
	coord getPos();

	void logic();

	void render(GraphicsController*& graphic, int offset);
	// For level mode
	void render(GraphicsController*& graphic, int offset, int bg);

	bool checkCollision(BOUNDINGBOX player);

};