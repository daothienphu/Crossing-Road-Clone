#pragma once
#include "GameLane.h"
#include "GraphicsController.h"
#include <vector>

class ILevel
{
public:
	virtual void getMap(vector<GameLane*>& lanes, GraphicsController* graphic) = 0;
};

class Level_1 : public ILevel
{
public:
	virtual void getMap(vector<GameLane*>& lanes, GraphicsController* graphic)
	{
		if (!lanes.empty()) lanes.clear();
		GameLane* lane1 = new GameLane(1, 1, 1, graphic);
		GameLane* lane2 = new GameLane(2, 2, 1, graphic);
		GameLane* lane3 = new GameLane(3, 3, 1, graphic);

		lanes.push_back(lane1);
		lanes.push_back(lane2);
		lanes.push_back(lane3);
	}
};
