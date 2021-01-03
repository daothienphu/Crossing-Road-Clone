#pragma once
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

//unordered_map<string, vector<wstring>> bufferStorage;

//draw the sprite here, coresspondence with the variable name
//remember to use the "extern" keyword to declare a global variable between many file
vector<wstring> title = {
	L".'''.  l'''.  .'''.  .'''   .'''   'l'  l.  l  .''''",
	L"l      l'''.  l   l   '''.   '''.   l   l '.l  l ''l",
	L"'...'  l   l  '...'  '...'  '...'  .l.  l   l  '...l",
	L" ",
	L"             l'''.  .'''.  .'''.  l'''.",
	L"             l'''.  l   l  l...l  l   l",
	L"             l   l  '...'  l   l  l...'",
};
vector<wstring> player = { 
	L"..",
	L".."};
vector<wstring> enemy1 = { 
	L". '.  .' .", 
	L"l.l'll'l.'", 
	L" ll.ll.ll ", 
	L".l '  ' l."};
vector<wstring> enemy2 = { 
	L" '...' ", 
	L" l'l'l ", 
	L".'l'l'.", 
	L"' ' ' '" };
vector<wstring> enemy3 = { 
	L"  '..'  ", 
	L"l.'ll'.l", 
	L"l'llll'l", 
	L" .l  l. " };
vector<wstring> enemy4 = { 
	L" .'...'. ", 
	L"ll..l..ll", 
	L"l'l'l'l'l", 
	L" ' ' ' ' " };
vector<wstring> start = { 
	L"  PLAY  " };
vector<wstring> load = { 
	L"  LOAD  " };
vector<wstring> settings = { 
	L"SETTINGS" };
vector<wstring> Exit = { 
	L"  EXIT  " };
vector<wstring> settingTitle = {
	L"This is setting screen." };

//then go to GraphicController and map it to the unordered_map using the syntax: bufferStorage["name"] = name;