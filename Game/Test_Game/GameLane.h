#pragma once
#include "Obstacles.h"
#include "Items.h"

const int MAX_PER_LANE = 7;

class GameLane : public Items {
private:
	vector <Obstacles*> obs;
	bool isGreen = 1;
	int velocity, level;
public:
	GameLane(int _level = 1, int dir) : level(_level) {
		// level 1: [0.4, 0.7] * MAX mobs	speed = 2
		// level 2: [0.7, 1] * MAX mobs		speed = 3
		// level 3: MAX mobs				speed = 5
		int n;
		switch (level) {
		case 1: {
			velocity = 2 * dir;
			int n = random(0.4 * MAX_PER_LANE, 0.7 * MAX_PER_LANE);
			break;
		}
		case 2: {
			velocity = 3 * dir;
			int n = random(0.7 * MAX_PER_LANE, MAX_PER_LANE);
			break;
		}
		case 3: {
			velocity = 5 * dir;
			int n = MAX_PER_LANE;
			break;
		}
		}
		for (int i = 0; i < n; i++)
			obs.push_back(new Monster()); //choose Obs type randomly
		// TO-DO: maximum means fill until no fit ( ͡° ͜ʖ ͡°)
	}

	int random(int a, int b) {
		long long res = rand() + rand() * rand();
		if (res < 0) res = -res;
		return a + (res % (b - a + 1));
	}

	void logic() {
		// Something to deal with green/red lights

		// Move obs (if isGreen)
		if (isGreen)
		{
			for (Obstacles* o : obs) {
				o->move(velocity, 0);
			}
		}
	}
};