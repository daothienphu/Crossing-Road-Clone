#pragma once
#include "Utils.h"
#include "GameLane.h"
#include "GraphicsController.h"
#include <vector>

class ILevel
{
public:
	virtual void getMap(vector<GameLane*>& lanes, GraphicsController* graphic) = 0;
	virtual void getMap(vector<GameLane*>& lanes, GraphicsController* graphic, int bg, bool order, int Level) = 0;

	virtual int addLanes(vector<GameLane*>& lanes, GraphicsController* graphic, int laneIndex) = 0;
	virtual int addLanes(vector<GameLane*>& lanes, GraphicsController* graphic, int laneIndex, int bg, bool order, int Level) = 0;

};

class Level_1 : public ILevel
{
public:
	//levelController->getMap(lanes, graphic);
	void getMap(vector<GameLane*>& lanes, GraphicsController* graphic);
	void getMap(vector<GameLane*>& lanes, GraphicsController* graphic, int bg, bool order, int Level);

	int addLanes(vector<GameLane*>& lanes, GraphicsController* graphic, int laneIndex);

	int addLanes(vector<GameLane*>& lanes, GraphicsController* graphic, int laneIndex, int bg, bool order, int Level);
};
