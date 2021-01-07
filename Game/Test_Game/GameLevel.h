#pragma once
#include "Utils.h"
#include "GameLane.h"
#include "GraphicsController.h"
#include <vector>

class ILevel
{
public:
	virtual void getMap(vector<GameLane*>& lanes, GraphicsController* graphic) = 0;
	virtual void getMap(vector<GameLane*>& lanes, GraphicsController* graphic, bool order, int bg, int level) = 0;
	virtual int addLanes(vector<GameLane*>& lanes, GraphicsController* graphic, int laneIndex) = 0;
	virtual int addLanes(vector<GameLane*>& lanes, GraphicsController* graphic, int laneIndex, bool order, int bg, int level) = 0;

};

class Level_1 : public ILevel
{
public:
	void getMap(vector<GameLane*>& lanes, GraphicsController* graphic)
	{
		if (!lanes.empty()) lanes.clear();
		GameLane* lane1 = new GameLane(1, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);
		GameLane* lane2 = new GameLane(2, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);
		GameLane* lane3 = new GameLane(3, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);
		GameLane* lane4 = new GameLane(4, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);
		GameLane* lane5 = new GameLane(5, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);
		GameLane* lane6 = new GameLane(6, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);

		//nho de lane theo thu tu khong la collision no deo chay dau

		lanes.push_back(lane1);
		lanes.push_back(lane2);
		lanes.push_back(lane3);
		lanes.push_back(lane4);
		lanes.push_back(lane5);
		lanes.push_back(lane6);
		lanes.push_back(new GameLane(7, 0, 1, 0, 0, graphic));
	}
	// For level mode
	void getMap(vector<GameLane*>& lanes, GraphicsController* graphic, bool order, int bg, int level)
	{
		if (!lanes.empty()) lanes.clear(); // reset lanes
		GameLane* cur;
		int nLane = random(3, 8); 	// Random 3 - 8 lanes each time
		for (int i = 0; i < nLane; i++) {
			cur = new GameLane(i + 1, level, 1 - 2 * random(0, 1), random(1, 3), random(1, 2), order, bg, graphic);
			lanes.push_back(cur);
		}
		lanes.push_back(new GameLane(nLane + 1, 0, 1, 0, 0, graphic));
	}

	int addLanes(vector<GameLane*>& lanes, GraphicsController* graphic, int laneIndex)
	{
		int n = random(5, 7);
		for (int i = laneIndex; i < laneIndex + n; i++)
			lanes.push_back(new GameLane(i, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic));
		lanes.push_back(new GameLane(laneIndex + n, 0, 1, 0, 0, graphic));
		return n + 1;
	}
	// For level mode
	int addLanes(vector<GameLane*>& lanes, GraphicsController* graphic, int laneIndex, bool order, int bg, int level)
	{
		int n = random(3, 8); // Number of new lanes to add
		for (int i = 0; i < n; i++)
			lanes.push_back(new GameLane(laneIndex + i, level, 1 - 2 * random(0, 1), random(1, 3), random(1, 2), order, bg, graphic));
		lanes.push_back(new GameLane(laneIndex + n, 0, 1, 0, 0, graphic)); //Padding lane
		return n + 1; // Total lanes added
	}

};

class Level_0 : public ILevel
{
public:
	void getMap(vector<GameLane*>& lanes, GraphicsController* graphic)
	{
		if (!lanes.empty()) lanes.clear();
		GameLane* lane1 = new GameLane(1, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);
		GameLane* lane2 = new GameLane(2, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);
		GameLane* lane3 = new GameLane(3, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);
		GameLane* lane4 = new GameLane(4, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);
		GameLane* lane5 = new GameLane(5, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);
		GameLane* lane6 = new GameLane(6, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic);

		//nho de lane theo thu tu khong la collision no deo chay dau

		lanes.push_back(lane1);
		lanes.push_back(lane2);
		lanes.push_back(lane3);
		lanes.push_back(lane4);
		lanes.push_back(lane5);
		lanes.push_back(lane6);
		lanes.push_back(new GameLane(7, 0, 1, 0, 0, graphic));
	}
	// For level mode
	void getMap(vector<GameLane*>& lanes, GraphicsController* graphic, bool order, int bg, int level)
	{
		if (!lanes.empty()) lanes.clear(); // reset lanes
		GameLane* cur;
		int nLane = random(3, 8); 	// Random 3 - 8 lanes each time
		for (int i = 0; i < nLane; i++) {
			cur = new GameLane(i + 1, level, 1 - 2 * random(0, 1), random(1, 3), random(1, 2), order, bg, graphic);
			lanes.push_back(cur);
		}
		lanes.push_back(new GameLane(nLane + 1, 0, 1, 0, 0, graphic));
	}

	int addLanes(vector<GameLane*>& lanes, GraphicsController* graphic, int laneIndex)
	{
		int n = random(5, 7);
		for (int i = laneIndex; i < laneIndex + n; i++)
			lanes.push_back(new GameLane(i, random(1, 3), 1 - 2 * random(0, 1), random(1, 3), random(1, 2), graphic));
		lanes.push_back(new GameLane(laneIndex + n, 0, 1, 0, 0, graphic));
		return n + 1;
	}
	// For level mode
	// nLane += levelController->addLanes(lanes, graphic, nLane);
	int addLanes(vector<GameLane*>& lanes, GraphicsController* graphic, int laneIndex, bool order, int bg, int level)
	{
		int n = random(3, 8); // Number of new lanes to add
		for (int i = 0; i < n; i++)
			lanes.push_back(new GameLane(laneIndex + i, level, 1 - 2 * random(0, 1), random(1, 3), random(1, 2), order, bg, graphic));
		lanes.push_back(new GameLane(laneIndex + n, 0, 1, 0, 0, graphic)); //Padding lane
		return n + 1; // Total lanes added
	}

};

