﻿#pragma once
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

//draw the sprite here, coresspondence with the variable name
extern unordered_map<string, vector<wstring>> BUFFER_MAP = {
	//intro & title screen
	{   "intro",
		vector<wstring>{
	    L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
		L"░░██████╗░███████╗██████╗░░░░░░░░░░░░░░░██████╗░██████╗░░█████╗░░██╗░░░░░░░██╗███████╗░██████╗░██████╗░░",
		L"░░██╔══██╗██╔════╝██╔══██╗░░░░░░░░░░░░░░██╔══██╗██╔══██╗██╔══██╗░██║░░██╗░░██║██╔════╝██╔════╝██╔════╝░░",
		L"░░██║░░██║█████╗░░██║░░██║███████████╗░░██████╔╝██████╔╝██║░░██║░╚██╗████╗██╔╝█████╗░░╚█████╗░╚█████╗░░░",
		L"░░██║░░██║██╔══╝░░██║░░██║╚══════════╝░░██╔═══╝░██╔══██╗██║░░██║░░████╔═████║░██╔══╝░░░╚═══██╗░╚═══██╗░░",
		L"░░██████╔╝███████╗██████╔╝░░░░░░░░░░░░░░██║░░░░░██║░░██║╚█████╔╝░░╚██╔╝░╚██╔╝░███████╗██████╔╝██████╔╝░░",
		L"░░╚═════╝░╚══════╝╚═════╝░░░░░░░░░░░░░░░╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░╚═╝░░╚══════╝╚═════╝░╚═════╝░░░",
		L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
        L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█▀█ █▀█ █▀█ █▀▄ █░█ █▀▀ ▀█▀ █ █▀█ █▄░█ █▀░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
        L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█▀▀ █▀▄ █▄█ █▄▀ █▄█ █▄▄ ░█░ █ █▄█ █░▀█ ▄█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
		L"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
		} //104 x 11
	},
	{
		"title",
		vector<wstring>{
		/*L"┏━━━┓",
		L"┃┏━┓┃",
		L"┃┃╋┗╋━┳━━┳━━┳━━┳┳━┓┏━━┓",
		L"┃┃╋┏┫┏┫┏┓┃━━┫━━╋┫┏┓┫┏┓┃",
		L"┃┗━┛┃┃┃┗┛┣━━┣━━┃┃┃┃┃┗┛┃",
		L"┗━━━┻┛┗━━┻━━┻━━┻┻┛┗┻━┓┃",
		L"╋╋╋╋╋╋╋╋╋╋╋╋╋╋╋╋╋╋╋┏━┛┃",
		L"┏━━━┓╋╋╋╋╋╋╋┏┓╋╋╋╋╋┗━━┛",
		L"┃┏━┓┃╋╋╋╋╋╋╋┃┃",
		L"┃┗━┛┣━━┳━━┳━┛┣━━┓",
		L"┃┏┓┏┫┏┓┃┏┓┃┏┓┃━━┫",
		L"┃┃┃┗┫┗┛┃┏┓┃┗┛┣━━┃",
		L"┗┛┗━┻━━┻┛┗┻━━┻━━┛"*/
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

	//player & enemies
	{
		"player",
		vector<wstring>{
		L"ll"
		}
	},
	{
		"enemy1", // blue
		vector<wstring>{
		L". '.  .' .",
		L"l.l'll'l.'",
		L" ll.ll.ll ",
		L".l '  ' l."
		}
	},
	{
		"enemy2", // yellow
		vector<wstring>{
		L" '...' ",
		L" l'l'l ",
		L".'l'l'.",
		L"' ' ' '"
		}
	},
	{
		"enemy3", // green
		vector<wstring>{
		L"  '..'  ",
		L"l.'ll'.l",
		L"l'llll'l",
		L" .l  l. "
		}
	},
	{
		"enemy4", // red
		vector<wstring>{
		L" .l...l. ",
		L"ll..l..ll",
		L"l'l'l'l'l",
		L" ' ' ' ' "
		}
	},
	{
		"enemy5", // purple
		vector<wstring>{
		L"  .l..l.",
		L".ll'll'll.",
		L"l llllll l",
		L"  .l  l."
		} 
	},
	{
		"enemy6", // orange
		vector<wstring>{
		L". '...' .",
		L"l.l'l'l.l",
		L" 'l'''l'",
		L" '     '"
		}
	},
	{
		"enemy7", // brown
		vector<wstring>{
		L" ..lll.. ",
		L"l''lll''l",
		L"''l'''l''",
		L".' ''' '."
		}
	},
	{
		"enemy8", // pink
		vector<wstring>{
		L"  '..'",
		L"l.'ll'.l",
		L"l'llll'l",
		L"l. '' .l"
		}
	},
	// select mode screen
	{
		"chooseTitle",
		vector<wstring>{
		L"▌│█║▌║▌║ CHOOSE MODE ║▌║▌║█│▌"
		}
	},
	{
		"levelMode",
		vector<wstring>{
		L"  LEVEL  MODE  "
		}
	},
	{
		"infinityMode",
		vector<wstring>{
		L" INFINITY MODE "
		}
	},

	//score & level
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

	//setting screen
	{
		"settingsTitle",
		vector<wstring>{
		L"▌│█║▌║▌║ SETTINGS ║▌║▌║█│▌"
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
		L"   BACK   "
		}
	},

	//pause screen
	{
		"pauseTitle",
		vector<wstring>{
		L"▌│█║▌║▌║ PAUSE ║▌║▌║█│▌" //9 each side incl spaces
		}
	},
	{
		"resumeButton",
		vector<wstring>{
		L"  RESUME  "
		}
	},
	{
		"restartButton",
		vector<wstring>{
		L"  RESTART "
		}
	},
	{
		"saveButton",
		vector<wstring>{
		L"   SAVE   "
		}
	},

	//exit & game over screen
	{
		"exitTitle",
		vector<wstring>{
		L"HOW DARE YOU EXIT OUR MARVELOUS GAME YOU UNCULTURED SWINE" //Some bull-headed kid wrote this (not me) //stfu
		}
	},
	{
		"gameoverTitle",
		vector<wstring>{
		L"─────────▄──────────────▄────",
		L"────────▌▒█───────────▄▀▒▌───",
		L"────────▌▒▒▀▄───────▄▀▒▒▒▐───",
		L"───────▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐───",
		L"─────▄▄▀▒▒▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐───",
		L"───▄▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀██▀▒▌───",
		L"──▐▒▒▒▄▄▄▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄▒▒▌──",
		L"──▌▒▒▐▄█▀▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐──",
		L"─▐▒▒▒▒▒▒▒▒▒▒▒▌██▀▒▒▒▒▒▒▒▒▀▄▌─",
		L"─▌▒▀▄██▄▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▌─",
		L"─▌▀▐▄█▄█▌▄▒▀▒▒▒▒▒▒░░░░░░▒▒▒▐─",
		L"▐▒▀▐▀▐▀▒▒▄▄▒▄▒▒▒▒▒░░░░░░▒▒▒▒▌",
		L"▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒░░░░░░▒▒▒▐─",
		L"─▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒▒▒░░░░▒▒▒▒▌─",
		L"─▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐──",
		L"──▀▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▌──",
		L"────▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀───",
		L"───▐▀▒▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀─────",
		L"──▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▀────────"
		} //29x19
	},
	{
		"inspirationalText",
		vector<wstring> {
		L"  Haha u lost, loser!!!! XD  "
		}
	},
	/*{
		"name",
		vector <wstring> {
		L"Something here",
		}
	},*/
	{
		"easterEgg1",
		vector<wstring> {
		L"           The game takes no time to load, but we made u wait cuz we hate u.",
		L"The name of the loading bar component in our code is literally \"Loading bar, cuz why not\""
		}
	},
	{
		"easterEgg2",
		vector<wstring> {
		L"There\'s only one button dumbass."
		}
	},
};

// Any buffer that requires padding to block
extern vector <string> CHAR_TO_BLOCK = {
	"player",
	"enemy1",
	"enemy2",
	"enemy3",
	"enemy4",
	"enemy5",
	"enemy6",
	"enemy7",
	"enemy8",
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