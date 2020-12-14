#include "Header.h"

#pragma region Util
void fixSizedConsoleWindow() {
	RECT windowRes;
	const HWND window = GetDesktopWindow();
	GetWindowRect(window, &windowRes);

	HWND consoleWindow = GetConsoleWindow();
	MoveWindow(consoleWindow, (windowRes.right - 1080) / 2, (windowRes.bottom - 720) / 2, 1080, 720, TRUE);

	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);

	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#pragma endregion