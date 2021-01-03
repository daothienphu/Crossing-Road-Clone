#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>

#include "GameCore.h"

int main() {
	fixSizedConsoleWindow();
	GameCore gc;
	//gc.test();
	gc.playScreen(1);
	return 0;
}