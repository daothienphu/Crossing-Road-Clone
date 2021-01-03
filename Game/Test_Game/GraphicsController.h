#pragma once
#define GAME_RATE 50
#define screenWidth 145
#define screenHeight 40

#include "BufferStorage.h"

class GraphicsController {
protected:
	wchar_t* buffer;
	WORD* color;

	HANDLE hConsole;
	DWORD dwBytesWritten;

	unordered_map<string, vector<wstring>> bufferStorage;
public:
	GraphicsController()
	{
		buffer = new wchar_t[screenHeight * screenWidth]{ L" " };
		color = new WORD[screenHeight * screenWidth]{ 7 };
		HANDLE hConsole1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole1);
		hConsole = hConsole1;

		//bufferStorage mapping
		bufferStorage["player"] = player; //player was declare in BufferStorage.h
	}

	vector<wstring>& getBuffer(string key)
	{
		return bufferStorage[key];
	}

	void render() {
		for (int i = 0; i < screenHeight; i++)
		{
			for (int j = 0; j < screenWidth; j++)
			{
				COORD cPos;
				cPos.X = j;
				cPos.Y = i;
				WriteConsoleOutputAttribute(hConsole, &color[i * screenWidth + j], 1, cPos, &dwBytesWritten);
			}
		}
		WriteConsoleOutputCharacter(hConsole, buffer, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
	}

	void setBuffer(vector<wstring>& content, int x, int y, int bgColor, int fgColor) {
		for (int i = 0; i < content.size(); ++i) {
			for (int j = 0; j < content[i].length(); ++j) {
				buffer[y * screenWidth + x + j] = content[i].at(j);
				color[y * screenWidth + x + j] = bgColor * 16 + fgColor;
			}
		}
	}

	/*void renderAt(int x, int y, int w, int h) {
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				COORD tmp;
				tmp.X = j; tmp.Y = i;
				WriteConsoleOutputAttribute(hConsole, &color[i * screenWidth + j], 1, tmp, &dwBytesWritten);
			}
		}
		WriteConsoleOutputCharacter(hConsole, buffer, screenWidth * screenHeight, { 0, 0 }, &dwBytesWritten);
	}*/
};