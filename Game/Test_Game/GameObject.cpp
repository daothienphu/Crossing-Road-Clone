#include "GameObject.h"
using namespace std;

GameObject::GameObject() : oldX(0), oldY(0), x(0), y(0), w(0), h(0), Items() {}
GameObject::GameObject(int x, int y, int w, int h, string bufferKey) : Items(bufferKey), oldX(x), oldY(y), x(x), y(y), w(w), h(h) {}

coord GameObject::getPos() {
	return { x, y };
}
coord GameObject::getOldPos() {
	return { oldX, oldY };
}
BOUNDINGBOX GameObject::getBoundingBox() {
	return { x,y,w,h };
}

void GameObject::render(GraphicsController*& graphic, int bgColor, int fgColor) {
	graphic->setBufferObject(graphic->getBuffer(bufferKey), x, y, bgColor, fgColor);
}

void GameObject::clearOldPos(GraphicsController*& graphic, int bgColor, int fgColor) {
	graphic->setBufferObject(graphic->getBuffer(bufferKey + "_clear"), oldX, oldY, bgColor, fgColor);
}