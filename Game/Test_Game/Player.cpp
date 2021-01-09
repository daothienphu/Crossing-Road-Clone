#include "Player.h"
Player::Player() : GameObject(0, 0, 0, 0, "player") {}
Player::Player(GraphicsController*& graphic) :
	GameObject(0, 0, graphic->getBuffer("player")[0].size(), graphic->getBuffer("player").size(), "player") {}
Player::Player(int x, int y, GraphicsController*& graphic) :
	GameObject(x, y, graphic->getBuffer("player")[0].size(), graphic->getBuffer("player").size(), "player") {}

void Player::update() {
	this->oldX = this->x;
	this->oldY = this->y;
}

void Player::move(int x, int y)
{
	this->x += 2 * x;
	this->y += y;
}

void Player::render(GraphicsController*& graphic, int offset) {
	//clearOldPos(graphic);
	graphic->setBufferWhite(graphic->getBuffer(bufferKey), oldX, oldY + offset, BG, 1);
	graphic->setBufferWhite(graphic->getBuffer(bufferKey), x, y + offset, BG, 7);
}
void Player::render(GraphicsController*& graphic, int offset, int bg, int ch) {
	//clearOldPos(graphic);
	graphic->setBufferWhite(graphic->getBuffer(bufferKey), oldX, oldY + offset, bg, blueLight);
	graphic->setBufferWhite(graphic->getBuffer(bufferKey), x, y + offset, bg, ch);
}

void Player::clearOldPos(GraphicsController*& graphic) {
	GameObject::clearOldPos(graphic, BG, 7);
}

void Player::setPos(int x, int y) {
	this->x = x;
	this->y = y;
}