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

		//charToBlock(player);
		//charToBlock(enemy1);
		//charToBlock(enemy2);
		//charToBlock(enemy3);
		//charToBlock(enemy4);
		//bufferStorage mapping
		bufferStorage["player"] = player; //player was declare in BufferStorage.h
		bufferStorage["enemy1"] = enemy1;
		bufferStorage["enemy2"] = enemy2;
		bufferStorage["enemy3"] = enemy3;
		bufferStorage["enemy4"] = enemy4;
	}

	//void charToBlock() {
	//	/*charToBlock("player");
	//	charToBlock("enemy1");
	//	charToBlock("enemy2");
	//	charToBlock("enemy3");
	//	charToBlock("enemy4");*/
	//	//charToBlock(player);
	//	//charToBlock(enemy1);
	//	//charToBlock(enemy2);
	//	//charToBlock(enemy3);
	//	//charToBlock(enemy4);
	//	////bufferStorage mapping
	//	//bufferStorage["player"] = player; //player was declare in BufferStorage.h
	//	//bufferStorage["enemy1"] = enemy1;
	//	//bufferStorage["enemy2"] = enemy2;
	//	//bufferStorage["enemy3"] = enemy3;
	//	//bufferStorage["enemy4"] = enemy4;
	//}

	//void charToBlock(vector<wstring>& graphics) {
	//	for (int i = 0; i < graphics.size(); ++i) {
	//		for (int j = 0; j < graphics[i].length(); ++j) {
	//			if (graphics[i][j] == L' ')
	//				continue;
	//			else if (graphics[i][j] == L'.')
	//				graphics[i][j] == L'▄';
	//			else if (graphics[i][j] == L'\'')
	//				graphics[i][j] == L'▀';
	//			else if (graphics[i][j] == L'l')
	//				graphics[i][j] == L'█';
	//		}
	//	}
	//}

	//void charToBlock(string key) {
	//	int n = bufferStorage.at(key).size();
	//	for (int i = 0; i < n; ++i) {
	//		for (int j = 0; j < bufferStorage.at(key)[i].length(); ++j) {
	//			if (bufferStorage.at(key)[i][j] == L' ')
	//				continue;
	//			else if (bufferStorage.at(key)[i][j] == L'.')
	//				bufferStorage.at(key)[i][j] == L'▄';
	//			else if (bufferStorage.at(key)[i][j] == L'\'')
	//				bufferStorage.at(key)[i][j] == L'▀';
	//			else if (bufferStorage.at(key)[i][j] == L'l')
	//				bufferStorage.at(key)[i][j] == L'█';
	//		}
	//	}
	//}

	vector<wstring>& getBuffer(string key)
	{
		return bufferStorage[key];
	}

	void render() {
		WriteConsoleOutputAttribute(hConsole, color, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
		WriteConsoleOutputCharacter(hConsole, buffer, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
	}

	void setBuffer(vector<wstring>& content, int x, int y, int bgColor, int fgColor) {
		for (int i = 0; i < content.size(); ++i) {
			for (int j = 0; j < content[i].length(); ++j) {
				buffer[(y + i) * screenWidth + x + j] = content[i].at(j);
				color[(y + i) * screenWidth + x + j] = bgColor * 16 + fgColor;
			}
		}
	}

	void renderAt(int x, int y, string key) {
		vector<wstring> tmp = bufferStorage[key];
		for (int i = 0; i < tmp.size(); i++)
		{
			for (int j = 0; j < tmp[i].length(); j++)
			{
				COORD t;
				t.X = j;
				t.Y = i;
				WriteConsoleOutputAttribute(hConsole, &color[i * screenWidth + j], 1, t, &dwBytesWritten);
				WriteConsoleOutputCharacter(hConsole, &buffer[i * screenWidth + j], 1, t, &dwBytesWritten);
			}
		}
	}
};