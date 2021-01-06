#pragma once
#include "Obstacles.h"
#include "Items.h"

class GameLane : public Items {
private:
	vector <Obstacles*> obs;
	bool isGreen = 1;
	int velocity, level, lane, dir;
public:
	GameLane(int lane, int level, int dir, GraphicsController*& graphic) : lane(lane), dir(dir) {
		// level 1: [2, 3] mobs	speed = 3
		// level 2: [3, 5] mobs	speed = 2
		// level 3: MAX mobs	speed = 1
		srand(time(NULL));
		int n;
		switch (level) {
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
		if (n == -1) {
			// Yeahh boi
			int cur = 0;
			while (1) {
				string chosen = "enemy" + to_string(random(1, NUM_ENEMY));
				if (cur < screenWidth)
				{
					obs.push_back(new Obstacles(cur, lane * LANE_HEIGHT, velocity, BG, random(1, 7), chosen, graphic));
					cur += graphic->getBuffer(chosen)[0].size() + LEAST_SPACE;
				}
				else
					break;
			}
		}
		else
		{
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
	}

	coord getPos() {
		return { 0, lane * LANE_HEIGHT };
	}

	int random(int a, int b) {
		long long res = (long long)rand() + (long long)rand() * (long long)rand();
		if (res < 0) res = -res;
		return a + ((int)res % (b - a + 1));
	}

	void logic() {
		if (isGreen)
			for (auto o : obs) {
				o->move(dir, 0);
			}
	}

	void render(GraphicsController*& graphic) {
		// Render lane itself

		// Render obstacles
		for (auto o : obs) {
			o->render(graphic);
		}
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