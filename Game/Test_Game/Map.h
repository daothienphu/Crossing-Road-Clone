#pragma once
#include <vector>
#include "Items.h"
using namespace std;

class Lane {
protected:
public:
};
class Map : public Items {
protected:
	vector<Lane> lanes;
public:
};