#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

int main() {
    //PlaySound(TEXT("mywavsound.wav"), NULL, SND_FILENAME); - My erroring code
    int n = 1;
    LPCWSTR command2{ L"play intro.wav" };
    LPCWSTR command1{ L"play game_over.wav" };

    //while(cin >> n && n != 0)
     //bool played = PlaySound(TEXT("game_over.wav"), NULL, SND_ASYNC);// - the correct code
     //cout << played << endl;
     //mciSendString(command1, NULL, 0, NULL);
     mciSendString(command2, NULL, 0, NULL);
     mciSendString(command1, NULL, 0, NULL);

    int test = 0;
    cin >> test;
    return 0;
}