#pragma once
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

//draw the sprite here, coresspondence with the variable name
extern unordered_map<string, vector<wstring> > BUFFER_MAP = {
	{
		"title",
		vector<wstring>{
		L".'''.  l'''.  .'''.  .'''   .'''   'l'  l.  l  .''''",
		L"l      l'''.  l   l   '''.   '''.   l   l '.l  l ''l",
		L"'...'  l   l  '...'  '...'  '...'  .l.  l   l  '...l",
		L" ",
		L"             l'''.  .'''.  .'''.  l'''.",
		L"             l'''.  l   l  l...l  l   l",
		L"             l   l  '...'  l   l  l...'",
		}
	},
	{
		"start",
		vector<wstring>{
		L"  PLAY  " 
		}
	},
	{
		"load",
		vector<wstring>{
		L"  LOAD  " 
		}
	},
	{
		"settings",
		vector<wstring>{
		L"SETTINGS"
		}
	},
	{
		"exit",
		vector<wstring>{
		L"  EXIT  "
		}
	},
	{
		"frame",
		vector<wstring>{
		L"╔═╗",
		L"║ ║",
		L"╚═╝"
		}
	},
	{
		"player",
		vector<wstring>{
		L"..",
		L"''"
		}
	},
	{
		"enemy1",
		vector<wstring>{
		L". '.  .' .",
		L"l.l'll'l.'",
		L" ll.ll.ll ",
		L".l '  ' l."
		}
	},
	{
		"enemy2",
		vector<wstring>{
		L" '...' ",
		L" l'l'l ",
		L".'l'l'.",
		L"' ' ' '"
		}
	},
	{
		"enemy3",
		vector<wstring>{
		L"  '..'  ",
		L"l.'ll'.l",
		L"l'llll'l",
		L" .l  l. "
		}
	},
	{
		"enemy4",
		vector<wstring>{
		L" .'...'. ",
		L"ll..l..ll",
		L"l'l'l'l'l",
		L" ' ' ' ' "
		}
	},
	{
		"score",
		vector<wstring>{
		L"SCORE"
		}
	},
	{
		"level",
		vector<wstring>{
		L"LEVEL"
		}
	},
	{
		"settingsTitle",
		vector<wstring>{
		L"This is setting screen."
		}
	},
	{
		"sound",
		vector<wstring>{
		L"SOUND:"
		}
	},
	{
		"on",
		vector<wstring>{
		L"  ON"
		}
	},
	{
		"off",
		vector<wstring>{
		L" OFF"
		}
	},
	{
		"back",
		vector<wstring>{
		L"BACK"
		}
	},
	{
		"pauseTitle",
		vector<wstring>{
		L"This is pause screen."
		}
	},
	{
		"resumeButton",
		vector<wstring>{
		L"RESUME"
		}
	},
	{
		"restartButton",
		vector<wstring>{
		L"RESTART"
		}
	},
	{
		"exitTitle",
		vector<wstring>{
		L"HOW DARE YOU EXIT OUR MARVELOUS GAME YOU UNCULTURED SWINE" //Some bull-headed kid wrote this (not me) //stfu
		}
	},
	/*{
		"name",
		vector <wstring> {
		L"Something here",
		}
	},*/
};

// Any buffer that requires padding to block
extern vector <string> CHAR_TO_BLOCK = {
	"player",
	"enemy1",
	"enemy2",
	"enemy3",
	"enemy4",
	"title",
	// "Some string here"
};

// Any buffer that requires a clear buffer (movable GameObject)
extern vector <string> CLEAR_BUFFER = {
	"player",
	"enemy1",
	"enemy2",
	"enemy3",
	"enemy4",
};

//then go to GraphicController and map it to the unordered_map using the syntax: bufferStorage["name"] = name;