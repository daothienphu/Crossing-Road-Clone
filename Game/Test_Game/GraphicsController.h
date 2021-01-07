#pragma once

#include "BufferStorage.h"

class GraphicsController {
protected:
	wchar_t* buffer, *starBuffer;
	WORD* color;

	HANDLE hConsole;
	DWORD dwBytesWritten;

	unordered_map<string, vector<wstring>> bufferStorage;

	int randomInterval = 10;
public:
	GraphicsController()
	{
		buffer = new wchar_t[screenHeight * screenWidth]{L" "};
		starBuffer = new wchar_t[screenHeight * screenWidth]{ L' ' };
		color = new WORD[screenHeight * screenWidth];
		for (int i = 0; i < screenHeight * screenWidth; ++i) {
			color[i] = black * 16 + whiteDark; //will add crescendo effect later
		}
		HANDLE hConsole1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole1);
		hConsole = hConsole1;
		dwBytesWritten = 0;
		bufferStorage = BUFFER_MAP;
		initCharToBlock();
		initClearBuffer();
	}
	~GraphicsController() {
		delete[] buffer;
		delete[] starBuffer;
		delete[] color;
	}

	void initClearBuffer() {
		for (string c : CLEAR_BUFFER) {
			wstring tmp = L"";
			for (int i = 0; i < bufferStorage[c][0].size() /* width */; i++)
				tmp += L" ";
			bufferStorage[c + "_clear"] = vector <wstring>{};
			for (int i = 0; i < bufferStorage[c].size() /* height */; i++)
				bufferStorage[c + "_clear"].push_back(tmp);
		}
	}
	void initCharToBlock() {
		for (string c : CHAR_TO_BLOCK)
			charToBlock(bufferStorage[c]);
	}

	void charToBlock(vector<wstring>& graphics) {
		for (int i = 0; i < graphics.size(); ++i) {
			for (int j = 0; j < graphics[i].length(); ++j) {
				if (graphics[i][j] == L' ')
					continue;
				else if (graphics[i][j] == L'.')
					graphics[i][j] = L'▄';
				else if (graphics[i][j] == L'\'')
					graphics[i][j] = L'▀';
				else if (graphics[i][j] == L'l')
					graphics[i][j] = L'█';
			}
		}
	}
	void openFrame(int x, int y, int w, int h) {
		buffer[y * screenWidth + x] = bufferStorage["frame"][0][0];
		buffer[y * screenWidth + x + w - 1] = bufferStorage["frame"][0][2];
		color[y * screenWidth + x] = 7;
		color[y * screenWidth + x + w - 1] = 7;
		for (int i = 1; i < w - 1; ++i) {
			buffer[y * screenWidth + x + i] = bufferStorage["frame"][0][1];
			color[y * screenWidth + x + i] = 7;	
		}
		int UwU = 2; // Moi nguoi oi toi bat dc 1 thang wibu nay  //Hai dat ten bien, the luon
		while (1) {
			buffer[(y + UwU - 1) * screenWidth + x] = bufferStorage["frame"][2][0];
			buffer[(y + UwU - 1) * screenWidth + x + w - 1] = bufferStorage["frame"][2][2];
			color[(y + UwU - 1) * screenWidth + x] = 7;
			color[(y + UwU - 1) * screenWidth + x + w - 1] = 7;
			for (int i = 1; i < w - 1; ++i) {
				buffer[(y + UwU - 1) * screenWidth + x + i] = bufferStorage["frame"][2][1];
				color[(y + UwU - 1) * screenWidth + x + i] = 7;
			}
			if (UwU > 2) {
				buffer[(y + UwU - 2) * screenWidth + x] = bufferStorage["frame"][1][0];
				buffer[(y + UwU - 2) * screenWidth + x + w - 1] = bufferStorage["frame"][1][2];
				color[(y + UwU - 2) * screenWidth + x] = 7;
				color[(y + UwU - 2) * screenWidth + x + w - 1] = 7;
				for (int j = 1; j < w - 1; ++j) {
					buffer[(y + UwU - 2) * screenWidth + x + j] = L' ';
					color[(y + UwU - 2) * screenWidth + x + j] = 7;
				}
			}
			UwU++;
			if (UwU == h + 1) {
				render();
				break;
			}
			render();
			delay(1000 / (FRAMERATE));
		}
	}
	void createFrame(int x, int y, int w, int h, bool transparentBG = true) {
		buffer[y * screenWidth + x] = bufferStorage["frame"][0][0];
		buffer[y * screenWidth + x + w - 1] = bufferStorage["frame"][0][2];
		buffer[(y + h - 1) * screenWidth + x] = bufferStorage["frame"][2][0];
		buffer[(y + h - 1) * screenWidth + x + w - 1] = bufferStorage["frame"][2][2];
		color[y * screenWidth + x] = black * 16 + white;
		color[y * screenWidth + x + w - 1] = black * 16 + white;
		color[(y + h - 1) * screenWidth + x] = black * 16 + white;
		color[(y + h - 1) * screenWidth + x + w - 1] = black * 16 + white;
		for (int i = 1; i < w - 1; ++i) {
			buffer[y * screenWidth + x + i] = bufferStorage["frame"][0][1];
			buffer[(y + h - 1) * screenWidth + x + i] = bufferStorage["frame"][2][1];
			color[y * screenWidth + x + i] = black * 16 + white;
			color[(y + h - 1) * screenWidth + x + i] = black * 16 + white;
		}
		for (int i = 1; i < h - 1; ++i) {
			buffer[(y + i) * screenWidth + x] = bufferStorage["frame"][1][0];
			buffer[(y + i) * screenWidth + x + w - 1] = bufferStorage["frame"][1][2];
			color[(y + i) * screenWidth + x] = black * 16 + white;
			color[(y + i) * screenWidth + x + w - 1] = black * 16 + white;
		}
		if (!transparentBG) {
			for (int i = 1; i < h - 1; ++i) {
				for (int j = 1; j < w - 1; ++j) {
					buffer[(y + i) * screenWidth + x + j] = L' ';
					color[(y + i) * screenWidth + x + j] = black * 16 + white;
				}
			}
		}
	}

	vector<wstring>& getBuffer(string key)
	{
		return bufferStorage[key];
	}

	bool isInScreen(int y, int x) {
		return 0 <= y && y < screenHeight - 1 && 0 <= x && x <= screenWidth - 1;
	}

	void setBuffer(vector<wstring>& content, int x, int y, int bgColor, int fgColor) {
		for (int i = 0; i < content.size(); ++i) {
			for (int j = 0; j < content[i].length(); ++j) {
				if (!isInScreen(y + i, x + j))
					continue;
				buffer[(y + i) * screenWidth + x + j] = content[i].at(j);
				color[(y + i) * screenWidth + x + j] = bgColor * 16 + fgColor;
			}
			if (isInScreen(y + i, x - 2))
				color[(y + i) * screenWidth + x - 2] = bgColor * 16 + fgColor;
			if (isInScreen(y + i, x - 1))
				color[(y + i) * screenWidth + x - 1] = bgColor * 16 + fgColor;
			if (isInScreen(y + i, x + content[i].length()))
				color[(y + i) * screenWidth + x + content[i].length()] = bgColor * 16 + fgColor;
			if (isInScreen(y + i, x + content[i].length() + 1))
				color[(y + i) * screenWidth + x + content[i].length() + 1] = bgColor * 16 + fgColor;
		}
	}
	void setBuffer(wstring content, int x, int y, int bgColor, int fgColor) {
		for (int i = 0; i < content.length(); ++i) {
			buffer[y * screenWidth + x + i] = content[i];
			color[y * screenWidth + x + i] = bgColor * 16 + fgColor;
		}
	}

	void setBufferWhite(vector<wstring>& content, int x, int y, int bgColor, int fgColor) {
		for (int i = 0; i < content.size(); ++i) {
			for (int j = 0; j < content[i].length(); ++j) {
				buffer[(y + i) * screenWidth + x + j] = content[i].at(j);
				color[(y + i) * screenWidth + x + j] = bgColor * 16 + fgColor;
			}
		}
	}
	void clearBuffer() {
		for (int i = 0; i < screenWidth * screenHeight; ++i) {
			color[i] = black * 16 + whiteDark;
			buffer[i] = L' ';
		}
	}
	void clearBuffer(int bg, int ch) {
		for (int i = 0; i < screenWidth * screenHeight; ++i) {
			color[i] = bg * 16 + ch;
			buffer[i] = L' ';
		}
	}
	void render() {
		WriteConsoleOutputAttribute(hConsole, color, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
		WriteConsoleOutputCharacter(hConsole, buffer, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
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
	void randomStars() {
		if (randomInterval != 10) {
			randomInterval++;
			copyStarBuffer();
			return;
		}

		randomInterval -= 10;
		for (int i = 0; i < 70; ++i) {
			int a = rand() % (screenWidth * screenHeight);
			starBuffer[a] = L'.';
		}
		copyStarBuffer();
	}
	void clearStars() {
		if (randomInterval == 10)
			for (int i = 0; i < screenWidth * screenHeight; ++i) {
				starBuffer[i] = L' ';
			}
	}
	void copyStarBuffer() {
		for (int i = 0; i < screenWidth * screenHeight; ++i) {
			if (starBuffer[i] == L'.') {
				buffer[i] = L'.';
				color[i] = black * 16 + white;
			}
		}
	}
	void glitch() {
		for (int i = 0; i < screenWidth * screenHeight; ++i) {
			color[i] = whiteDark * 16 + black;		
		}
		render();
		delay(250);
		for (int i = 0; i < screenWidth * screenHeight; ++i) {
			color[i] = black * 16 + whiteDark;
		}
		render();
		delay(125);
		for (int i = 0; i < screenWidth * screenHeight; ++i) {
			color[i] = whiteDark * 16 + black;
		}
		render();
		delay(125);
	}
	wstring line(wstring pattern, int length) {
		wstring res;
		for (int i = 0; i < length / pattern.length(); i++)
			res += pattern;
		return res;
	}
	wstring time_to_wstring(int t) { // From 125 to 02:05
		int m = t / 60;
		int s = t % 60;
		wstring res = L"0";
		res += L'0' + m;
		res += ':';
		res += L'0' + s / 10;
		res += L'0' + s % 10;
		return res;
	}
	void progressBar(int elapsed, int duration, int x, int y) {
		// Draw bar
		wstring bar;
		for (int i = 0; i < 100; i++)
			bar += L' ';
		setBuffer(bar, x, y, black, white);
		// Draw progress
		for (int i = 0; i < elapsed * 100 / duration; i++) {
			if (i < 100)
				setBuffer(L"█", x + i, y, blueDark, white);
		}
		// Draw time
		setBuffer(time_to_wstring(elapsed), x - 6, y, black, white);
		setBuffer(time_to_wstring(duration), x + 104, y, black, white);
	}
};