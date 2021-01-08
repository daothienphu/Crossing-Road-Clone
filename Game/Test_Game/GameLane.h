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
	GameLane(int lane, int level, int dir, int green, int red, GraphicsController*& graphic) : 
		lane(lane), 
		dir(dir),
		green(green * FRAMERATE),
		red(red * FRAMERATE)
	{
		// level 1: [2, 3] mobs	speed = 3
		// level 2: [3, 5] mobs	speed = 2
		// level 3: MAX mobs	speed = 1
		int n;
		switch (level) {
		case 0: {
			velocity = 0;
			n = 0;
			break;
		}
		case 1: {
			velocity = 3;
			n = random(2, 3);
			break;
		}
		case 2: {
			velocity = 2;
			n = random(3, 5);
			break;
		}
		case 3: {
			velocity = 1;
			n = -1;
			break;
		}
		}
		if (level == 0)
			return;
		if (n == -1) {
			// Yeahh boi
			int cur = 0;
			while (1) {
				string chosen = "enemy" + to_string(random(1, NUM_ENEMY));
				if (cur + LEAST_SPACE < screenWidth)
				{
					obs.push_back(new Obstacles(cur, lane * LANE_HEIGHT, velocity, BG, random(1, 7), chosen, graphic));
					cur += graphic->getBuffer(chosen)[0].size() + LEAST_SPACE;
				}
				else
					break;
			}
		}
		else {
			int sum = 0;
			for (int i = 0; i < n; i++)
			{
				string chosen = "enemy" + to_string(random(1, NUM_ENEMY));
				obs.push_back(new Obstacles(0, lane * LANE_HEIGHT, velocity, BG, random(1, 7), chosen, graphic));
				sum += graphic->getBuffer(chosen)[0].size();
			}

			// Justify space

			sum = screenWidth - sum;
			sum /= obs.size();
			int cur = 0;
			for (int i = 0; i < n; i++)
			{
				obs[i]->setPos(cur, lane * LANE_HEIGHT);
				cur += obs[i]->getBoundingBox().w + sum;
			}
		}
		light = random(0, 2);
		if (light == 0)
			curTime = random(0, green - 1);
		else if (light == 1)
			curTime = random(0, YELLOW_LIGHT_SECS * FRAMERATE - 1);
		else
			curTime = random(0, red - 1);
	}
	// For level mode
	GameLane(int lane, int level, int dir, int green, int red, GraphicsController*& graphic, int bg, bool order, int Level) :
		lane(lane),
		dir(dir),
		green(green* FRAMERATE),
		red(red* FRAMERATE)
	{
		// level 1: [2, 3] mobs	speed = 3
		// level 2: [3, 5] mobs	speed = 2
		// level 3: MAX mobs	speed = 1
		int n;
		switch (level) {
		case 0: {
			velocity = 0;
			n = 0;
			break;
		}
		case 1: {
			velocity = 3;
			n = random(2, 3);
			break;
		}
		case 2: {
			velocity = 2;
			n = random(3, 5);
			break;
		}
		case 3: {
			velocity = 1;
			n = -1;
			break;
		}
		}
		if (level == 0)
			return;
		if (n == -1) {
			// Yeahh boi
			int cur = 0;
			while (1) {
				int e = random(1, 4 + Level - 1);
				string chosen = "enemy" + to_string(e);
				int c = 1;
				switch (e) {
				case 1:	c = blueLight; break;
				case 2: c = yellow; break;
				case 3: c = 4; break; 
				case 4: c = 6; break; 
				case 5: c = purple; break;
				case 6: c = orange; break; 
				case 7: c = brown; break; 
				case 8: c = pink; break; 
				default: break;
				}
				if (cur + LEAST_SPACE < screenWidth)
				{
					obs.push_back(new Obstacles(cur, lane * LANE_HEIGHT, velocity, bg, c, chosen, graphic));
					cur += graphic->getBuffer(chosen)[0].size() + LEAST_SPACE;
				}
				else
					break;
			}
		}
		else {
			int sum = 0;
			for (int i = 0; i < n; i++)
			{
				int e = random(1, 4 + Level - 1);
				string chosen = "enemy" + to_string(e);
				int c = 1;
				switch (e) {
				case 1:	c = blueLight; break;
				case 2: c = yellow; break;
				case 3: c = 4; break;
				case 4: c = 6; break;
				case 5: c = purple; break;
				case 6: c = orange; break;
				case 7: c = brown; break;
				case 8: c = pink; break;
				default: break;
				}
				obs.push_back(new Obstacles(0, lane * LANE_HEIGHT, velocity, bg, c, chosen, graphic));
				sum += graphic->getBuffer(chosen)[0].size();
			}

			// Justify space

			sum = screenWidth - sum;
			sum /= obs.size();
			int cur = 0;
			for (int i = 0; i < n; i++)
			{
				obs[i]->setPos(cur, lane * LANE_HEIGHT);
				cur += obs[i]->getBoundingBox().w + sum;
			}
		}
		light = random(0, 2);
		if (light == 0)
			curTime = random(0, green - 1);
		else if (light == 1)
			curTime = random(0, YELLOW_LIGHT_SECS * FRAMERATE - 1);
		else
			curTime = random(0, red - 1);
	}

	~GameLane() {
		for (auto o : obs)
			delete o;
	}

	void setPassed(bool s) { passed = s; }
	void setNewPassed(bool s) { newPass = s; }
	bool Passed() { return passed; }
	bool NewPass() { return newPass; }
	coord getPos() {
		return { 0, lane * LANE_HEIGHT };
	}

	void logic() {
		if (obs.size() == 0)
			return;
		curTime++;
		if (light == 0 || light == 1) {
			for (auto o : obs) {
				o->move(dir, 0);
			}

			if (light == 0) {
				if (curTime >= green)
				{
					curTime -= green;
					light = 1;
				}
			}

			if (light == 1) {
				if (curTime >= YELLOW_LIGHT_SECS * FRAMERATE)
				{
					curTime -= YELLOW_LIGHT_SECS * FRAMERATE;
					light = 2;
				}
			}
		}
		else {
			if (curTime >= red)
			{
				curTime -= red;
				light = 0;
			}
		}
	}

	void render(GraphicsController*& graphic, int offset) {
		// Render lane itself

		if (obs.size() == 0)
			return;
		// Render obstacles
		for (auto o : obs) {
			o->render(graphic, offset);
		}

		// Render lights
		graphic->setBufferObject(graphic->getBuffer("lightLine"), 0, lane * LANE_HEIGHT - 2 + offset, BG, light == 0 ? 4 : (light == 1 ? 3 : 6)); // Light line
		graphic->setBufferObject(graphic->getBuffer("player"), 2, lane * LANE_HEIGHT - 2 + offset, BG, light == 0 ? 4 : (light == 1 ? 3 : 6));
	}
	// For level mode
	void render(GraphicsController*& graphic, int offset, int bg) {
		// Render lane itself
		if (obs.size() == 0)
			return;
		// Render obstacles
		for (auto o : obs) {
			o->render(graphic, offset, bg);
		}
		// Render lights
		int ch = light == 0 ? 4 : (light == 1 ? 3 : 6);
		graphic->setBufferObject(graphic->getBuffer("lightLine"), 0, lane * LANE_HEIGHT - 2 + offset, bg, ch); // Light line
		graphic->setBufferObject(graphic->getBuffer("player"), 2, lane * LANE_HEIGHT - 2 + offset, bg, ch);
	}

	bool checkCollision(BOUNDINGBOX player)
	{
		for (auto it : obs)
		{
			BOUNDINGBOX obj = it->getBoundingBox();
			if (min(player.x + player.w, obj.x + obj.w) > max(player.x, obj.x) && 
				min(player.y + player.h, obj.y + obj.h) > max(player.y, obj.y)) return true;
		}
		return false;
	}

};