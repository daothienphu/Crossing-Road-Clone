#include "Header.h"
#include <iomanip>
#include <vector>
#define halfup "\xdf"
#define halfdown "\xdc"
#define whole "\xdb"

#define black50 "\x1B[30m"
#define red50 "\x1B[31m"
#define green50 "\x1B[32m"
#define yellow50 "\x1B[33m"
#define blue50 "\x1B[34m"
#define magenta50 "\x1B[35m"
#define cyan50 "\x1B[36m"
#define white50 "\x1B[37m"

#define blackBG50 "\x1B[40m"
#define redBG50 "\x1B[41m"
#define greenBG50 "\x1B[42m"
#define yellowBG50 "\x1B[43m"
#define blueBG50 "\x1B[44m"
#define magentaBG50 "\x1B[45m"
#define cyanBG50 "\x1B[46m"
#define whiteBG50 "\x1B[47m"

#define black "\x1B[90m"
#define red "\x1B[91m"
#define green "\x1B[92m"
#define yellow "\x1B[93m"
#define blue "\x1B[94m"
#define magenta "\x1B[95m"
#define cyan "\x1B[96m"
#define white "\x1B[97m"

#define blackBG "\x1B[100m"
#define redBG "\x1B[101m"
#define greenBG "\x1B[102m"
#define yellowBG "\x1B[103m"
#define blueBG "\x1B[104m"
#define magentaBG "\x1B[105m"
#define cyanBG "\x1B[106m"
#define whiteBG "\x1B[107m"

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

void renderDino(int x, int y) {
    gotoXY(x, y);
    cout << whiteBG50 << green50 << halfdown << whole << whole << whole << blackBG50 << halfup << whiteBG50 << whole << whole << halfdown;
    gotoXY(x, y + 1);
    cout << whole << whole << whole << whole << whole << whole << whole << whole;
    gotoXY(x + 1, y + 2);
    cout << halfdown << halfdown << halfdown << whole << whole << whole << whole;
    gotoXY(x + 4, y + 3);
    cout << whole << whole << whole << whole;
    gotoXY(x + 4, y + 4);
    cout << cyanBG50 << halfup << blackBG50 << whole << whole << whole << whole << whiteBG50 << halfdown;
    gotoXY(x + 2, y + 5);
    cout << whole << halfup << cyanBG50 << halfup << halfup << blackBG50 << whole << whole << whole << whole << whole << whiteBG50 << halfdown;
    gotoXY(x + 18, y + 5);
    cout << halfdown;
    gotoXY(x + 5, y + 6);
    cout << cyan50 << whole << whole << green50 << whole << whole << whole << whole << whole << whole << halfdown;
    gotoXY(x + 16, y + 6);
    cout << halfdown << whole << whole;
    gotoXY(x + 6, y + 7);
    cout << cyan50 << halfup << whole << green50 << whole << whole << whole << whole << whole << whole << whole << whole << whole << whole;
    gotoXY(x + 8, y + 8);
    cout << cyan50 << halfup << green50 << whole << whole << whole << whole << whole << whole << halfup << halfup;
    gotoXY(x + 9, y + 9);
    cout << whole << halfup;
    gotoXY(x + 12, y + 9);
    cout << halfup << whole;
    gotoXY(x + 8, y + 10);
    cout << halfup << halfup;
    gotoXY(x + 12, y + 10);
    cout << halfup << halfup;
}
void renderwhiteBG(int x, int y, int w, int h) {
    gotoXY(x, y);
    cout << whiteBG50;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j)
            cout << " ";
        cout << endl;
    }
    cout << blackBG50;
}
int main() {
    fixSizedConsoleWindow();

    //gotoXY(144,41); //coords_max(144, 41);     
    //cout << 1; //(scroll up pls)
    printPalette();
    renderwhiteBG(0, 4, 40, 16);
    renderDino(10, 6);
    gotoXY(0, 20);
    return 0;
}