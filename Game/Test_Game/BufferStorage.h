#pragma once
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

//unordered_map<string, vector<wstring>> bufferStorage;

//draw the sprite here, coresspondence with the variable name
//remember to use the "extern" keyword to declare a global variable between many file
extern vector<wstring> player = { L"...." };

extern vector<wstring> Title = {
	L".'''.  l'''.  .'''.  .'''   .'''   'l'  l.  l  .''''",
	L"l      l'''.  l   l   '''.   '''.   l   l '.l  l ''l",
	L"'...'  l   l  '...'  '...'  '...'  .l.  l   l  '...l",
	L" ",
	L"             l'''.  .'''.  .'''.  l'''.",
	L"             l'''.  l   l  l...l  l   l",
	L"             l   l  '...'  l   l  l...'",
};

//then go to GraphicController and map it to the unordered_map using the syntax: bufferStorage["name"] = name;