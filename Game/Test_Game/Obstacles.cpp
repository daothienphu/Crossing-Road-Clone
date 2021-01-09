#pragma once
#include "Obstacles.h"

Obstacles::Obstacles() : GameObject(0, 0, 0, 0, "unknownObstacles") {}
Obstacles::Obstacles(int x, int y, int _speed, int _bgColor, int _fgColor, string bufferKey, GraphicsController*& graphic) :
	GameObject(x, y, graphic->getBuffer(bufferKey)[0].size(), graphic->getBuffer(bufferKey).size(), bufferKey),
	speed(_speed),
	bgColor(_bgColor),
	fgColor(_fgColor)
{}

void Obstacles::move(int x, int y)
{
	tick++;

	// Check if enough ticks yet
	if (tick < speed)
		return; //Nah, not enough

	tick %= speed;
	this->oldX = this->x;
	this->oldY = this->y;
	this->x += x;
	this->y += y;

	if (isOutOfBound())
		resetPos(x > 0);
}

void Obstacles::render(GraphicsController*& graphic, int offset) {
	//clearOldPos(graphic);
	graphic->setBufferObject(graphic->getBuffer(bufferKey), this->x, this->y + offset, bgColor, fgColor);
}
void Obstacles::render(GraphicsController*& graphic, int offset, int bg) {
	//clearOldPos(graphic);
	graphic->setBufferObject(graphic->getBuffer(bufferKey), this->x, this->y + offset, bg, fgColor);
}
void Obstacles::render(GraphicsController*& graphic, int offset, int bg, int ch) {
	//clearOldPos(graphic);
	graphic->setBufferObject(graphic->getBuffer(bufferKey), this->x, this->y + offset, bg, ch);
}
void Obstacles::clearOldPos(GraphicsController*& graphic) {
	GameObject::clearOldPos(graphic, bgColor, fgColor);
}

void Obstacles::setPos(int x, int y) {
	this->x = x;
	this->oldX = x;
	this->y = y;
	this->oldY = y;
}

bool Obstacles::isOutOfBound() {
	return x + MAX_ENEMY_WIDTH < 1 || x > screenWidth;
}

int Obstacles::getTick() {
	return tick;
}