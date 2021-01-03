#pragma once
#include <vector>

class Items {
protected:
public:
	virtual vector<wstring>& getBufferData() = 0;
	virtual coord getPos() = 0;
};