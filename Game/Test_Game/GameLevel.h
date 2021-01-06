#pragma once
#include "GameLane.h"
#include "GraphicsController.h"
#include <vector>

class ILevel
{
public:
	virtual void getMap(vector<GameLane*>& lanes, GraphicsController* graphic) = 0;

	virtual void addLanes(vector<GameLane*> &lanes, GraphicsController* graphic, int laneIndex) = 0;
};

class Level_1 : public ILevel
{
public:
	void getMap(vector<GameLane*>& lanes, GraphicsController* graphic)
	{
		if (!lanes.empty()) lanes.clear();
		GameLane* lane1 = new GameLane(1, 1, 1, graphic);
		GameLane* lane2 = new GameLane(2, 2, 1, graphic);
		GameLane* lane3 = new GameLane(3, 1, 1, graphic);
		GameLane* lane4 = new GameLane(4, 1, 1, graphic);
		GameLane* lane5 = new GameLane(5, 1, 1, graphic);
		GameLane* lane6 = new GameLane(6, 1, 1, graphic);
		GameLane* lane7 = new GameLane(7, 1, 1, graphic);

		//nho de lane theo thu tu khong la collision no deo chay dau
		
		lanes.push_back(lane1);
		lanes.push_back(lane2);
		lanes.push_back(lane3);
		lanes.push_back(lane4);
		lanes.push_back(lane5);
		lanes.push_back(lane6);
		lanes.push_back(lane7);
	}

	void addLanes(vector<GameLane*> &lanes, GraphicsController* graphic, int laneIndex)
	{
		for (int i = laneIndex; i < laneIndex + 7; i++)
		{
			GameLane* tmp = new GameLane(i, 2, 1, graphic);
			lanes.push_back(tmp);
		}
	}
	
};
