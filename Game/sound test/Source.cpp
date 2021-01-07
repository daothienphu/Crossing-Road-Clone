//#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

int main() {

     mciSendString(L"play song_game_3.wav", NULL, 0, NULL);
     int n;
     cin >> n;
     //mciSendString(L"pause song_game_3.wav", NULL, 0, NULL);
     mciSendString(L"stop song_game_3.wav", NULL, 0, NULL);
     mciSendString(L"play game_over.wav", NULL, 0, NULL);
     cin >> n;
     mciSendString(L"play song_game_3.wav", NULL, 0, NULL);
     cin >> n;
    return 0;

    //PlaySound(TEXT("song_game_3.wav"), NULL, SND_FILENAME | SND_ASYNC);
    //int n;
    //cin >> n;
    //mciSendString(L"play game_over.wav", NULL, 0, NULL);
    //cin >> n;
}