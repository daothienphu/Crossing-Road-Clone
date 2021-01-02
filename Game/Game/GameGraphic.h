//#pragma once
//#include "Header.h"
//
//	void clearScreen(int colorBackground, int colorCharacter) {
//		for (int i = 0; i < screenWidth; i++) {
//			for (int j = 0; j < screenHeight; j++) {
//				pBuffer[j * screenWidth + i] = L' '; // Fill screen with blank space
//				pColor[j * screenWidth + i] = colorBackground * 16 + colorCharacter; // Set color
//			}
//		}
//	}
//
//
//	
//	
//
//
//	void startMenuScreen() {
//		
//
//	void startGameScreen() {
//		cPlayer Player;
//		Player.setXY(2, 1); // Player spawns at (0, 0)
//		cEnemy Enemy1;//, Enemy2;
//		Enemy1.setXY(15, 10);
//		//Enemy2.setXY(70, 20);
//		int bg = 0;
//		clearScreen(0, 0);
//		bool gameOver = false;
//		while (gameOver == false) {
//			clearScreen(0, 2);
//
//			// READ INPUT
//			bool* bKeyGame = new bool[key.size()]; // Check ingame input
//			for (int i = 0; i < key.size(); i++) { 	// Read input
//				bKeyGame[i] = (GetAsyncKeyState(key.at(i))) != 0;
//			}
//			// W - Move up
//			if (bKeyGame[0] == 1) {
//				Player.moveUp();
//			}
//			// A - Move left
//			if (bKeyGame[1] == 1) {
//				Player.moveLeft();
//			}
//			// S - Move down
//			if (bKeyGame[2] == 1) {
//				Player.moveDown();
//			}
//			// D - Move right
//			if (bKeyGame[3] == 1) {
//				Player.moveRight();
//			}
//
//			// UPDATE 
//			if (Enemy1.getX() >= screenWidth)Enemy1.setX(15);
//			Enemy1.moveRight();
//			//if (Enemy2.getX() <= 0) Enemy2.setX(70);
//			//Enemy2.moveLeft();
//
//			// DISPLAY
//			Sleep(990);
//			drawBlock(Player.getSketch(), Player.getX(), Player.getY(), bg, 2);
//			drawBlock(Enemy1.getSketch(), Enemy1.getX(), Enemy1.getY(), bg, 6); // Red enemy
//			//drawBlock(Enemy2.getSketch(), Enemy2.getX(), Enemy2.getY(), bg, 3); // Yellow enemy
//			drawScreen();
//		}
//	}
//
//};
