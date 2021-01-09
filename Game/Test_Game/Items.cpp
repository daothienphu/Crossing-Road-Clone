#include "Items.h"
using namespace std;

Items::Items() : bufferKey("none") {}

Items::Items(string bufferKey) : bufferKey(bufferKey) {}

string Items::getBufferKey()
{
	return bufferKey;
}