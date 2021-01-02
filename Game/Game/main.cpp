#include "Header.h"
#include "GameCore.h"

int main() {
    //gameGraphics will be obsoleted.
    fixSizedConsoleWindow();
    GameCore gc;
    gc.renderStartScreen();
    //gc.start();
    //gc.gameLogic();

    return 0;
}
