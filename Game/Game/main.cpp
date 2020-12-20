#include "Header.h"

struct Size {
    int w; int h;
};

class dino {
private:
    int x, y, w, h;
public:
    dino(int X, int Y) {
        x = X;
        y = Y;
        w = 19;
        h = 11;
    }
    void setPos(int X, int Y) {
        x = X;
        y = Y;
    }
    void renderDino();
    COORD getPos() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        return coord;
    }
    Size getSize() {
        Size size;
        size.w = w;
        size.h = h;
        return size;
    }
};

void renderRedBG(int x, int y, int w, int h) {
    cout << redBG50;
    for (int i = 0; i < h; ++i) {
        gotoXY(x, y + i);
        for (int j = 0; j < w; ++j)
            cout << " ";
        cout << endl;
    }
    cout << blackBG50;
}

void renderWhiteBG(int x, int y, int w, int h) {
    cout << whiteBG50;
    for (int i = 0; i < h; ++i) {
        gotoXY(x, y + i);
        for (int j = 0; j < w; ++j)
            cout << " ";
    }
    cout << blackBG50;
}

class Canvas
{
private:
    dino& D;
public:
    Canvas(dino& d) : D(d) {};
    void drawCanvas() {
        renderWhiteBG(0, 0, 80, 20);
        D.renderDino();
    }
    void drawCanvas(COORD co, Size si) {
        renderWhiteBG(co.X, co.Y, si.w, si.h);
        D.renderDino();
    }
};

void dino::renderDino() {
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

WORD getKey() {
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD events;
    INPUT_RECORD buffer;
    PeekConsoleInput(handle, &buffer, 1, &events);
    if (events > 0)
    {
        ReadConsoleInput(handle, &buffer, 1, &events);
        return buffer.Event.KeyEvent.wVirtualKeyCode;
    }
    else return 0;
}

int main() {
    int x = 10, y = 6;
    dino Dino(x, y);
    Canvas canvas(Dino);
    fixSizedConsoleWindow();
    //gotoXY(144,41); //coords_max(144, 41);     
    //cout << 1; //(scroll up pls)
    //printPalette();
    renderWhiteBG(0, 0, 80, 20);

    while (1 && delay(50)) {
        Size dinoSize = Dino.getSize();
        COORD oldCoord = Dino.getPos();
        switch (getKey()) {
        case 87:
        case 119: Dino.setPos(x, y-=2); break;
        case 83:
        case 115: Dino.setPos(x, y+=2); break;
        case 97:
        case 65: Dino.setPos(x-=2, y); break;
        case 100:
        case 68: Dino.setPos(x+=2, y); break;
        default: Dino.setPos(x, y); break;
        }
        canvas.drawCanvas(oldCoord, dinoSize);
    }    




    return 0;
}