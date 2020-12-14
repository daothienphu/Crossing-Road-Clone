#pragma once
#include <iostream>
#include <windows.h>
using namespace std;

#pragma region Util
void fixSizedConsoleWindow();
void gotoXY(int x, int y);
#pragma endregion

#pragma region Classes def
class Vehicle {
	int x, y;
public:
	virtual void move(int, int);
};
class Truck : public Vehicle {
public:
};
class Car : public Vehicle {
public:
};

class Animal {
	int x,y;
public:
	virtual void move(int, int);
	virtual void roar();
};
class Dinosaur : public Animal {
public:
};
class Bird : public Animal {
public:
};

class People {
private:
	int x, y;
	bool state;
public:
	People();

	//update position
	void up(int);
	void left(int);
	void right(int);
	void down(int);

	bool isCollided(const Vehicle*&);
	bool isCollided(const Animal*&);

	bool isFinish();
	bool isAlive();
};

class Game {
	Truck* trucks;
	Car* cars;
	Dinosaur* dinosaurs;
	Bird* birds;
	People people;
public:
	Game();
	void drawGame();
	~Game();
	People getPeople();
	Vehicle* getVehicle();
	Animal* getAnimal();
	void reset();
	void exit(HANDLE);
	void start();
	void loadGame(istream);
	void saveGame(istream);
	void pauseGame(HANDLE);
	void resumeGame(HANDLE);
	void updatePosPeople(char);
	void updatePosVehicle();
	void updatePosAnimal();
};
#pragma endregion