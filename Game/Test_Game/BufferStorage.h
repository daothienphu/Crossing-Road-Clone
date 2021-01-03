#pragma once
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

//unordered_map<string, vector<wstring>> bufferStorage;

//draw the sprite here, coresspondence with the variable name
//remember to use the "extern" keyword to declare a global variable between many file
extern vector<wstring> title = {
	L".'''.  l'''.  .'''.  .'''   .'''   'l'  l.  l  .''''",
	L"l      l'''.  l   l   '''.   '''.   l   l '.l  l ''l",
	L"'...'  l   l  '...'  '...'  '...'  .l.  l   l  '...l",
	L" ",
	L"             l'''.  .'''.  .'''.  l'''.",
	L"             l'''.  l   l  l...l  l   l",
	L"             l   l  '...'  l   l  l...'",
};
extern vector<wstring> player = { 
	L"..",
	L"''"};
extern vector<wstring> enemy1 = { 
	L". '.  .' .", 
	L"l.l'll'l.'", 
	L" ll.ll.ll ", 
	L".l '  ' l."};
extern vector<wstring> enemy2 = { 
	L" '...' ", 
	L" l'l'l ", 
	L".'l'l'.", 
	L"' ' ' '" };
extern vector<wstring> enemy3 = { 
	L"  '..'  ", 
	L"l.'ll'.l", 
	L"l'llll'l", 
	L" .l  l. " };
extern vector<wstring> enemy4 = { 
	L" .'...'. ", 
	L"ll..l..ll", 
	L"l'l'l'l'l", 
	L" ' ' ' ' " };
extern vector<wstring> start = { 
	L"  PLAY  " };
extern vector<wstring> load = { 
	L"  LOAD  " };
extern vector<wstring> settings = { 
	L"SETTINGS" };
extern vector<wstring> Exit = { 
	L"  EXIT  " };
extern vector<wstring> settingTitle = {
	L"This is setting screen." };

//then go to GraphicController and map it to the unordered_map using the syntax: bufferStorage["name"] = name;