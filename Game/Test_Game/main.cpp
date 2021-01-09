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
	gc.start();
	return 0;
}