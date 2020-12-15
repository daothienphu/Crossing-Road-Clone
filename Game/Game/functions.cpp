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

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void printPalette() {
    int i = 30;
    while (i < 108) {
        string res = "";
        int j = i;
        while (j) {
            char tmp = char(j % 10 + '0');
            res = tmp + res;
            j /= 10;
        }

        string color = "\x1B[" + res + 'm';
        cout << color << setw(5) << i;

        switch (i) {
        case 37:
        case 97: i += 3; cout << endl; break;
        case 47: i += 43; cout << endl << blackBG50; break;
        case 107: cout << blackBG50 << white50;
        default: i++; break;
        }
    }
}
#pragma endregion
