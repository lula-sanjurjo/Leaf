#pragma once

#include "cocos2d.h"
#include "Leaf.h"

USING_NS_CC;

// This class implements the extinguisher, that will be able to stop the fire
// over the leaves. So, to be able to do that, he can move and extinguish the
// fire by being close to the leaf.
class Extinguisher : public Node
{
public:
	Extinguisher(Leaf** _leaves, unsigned leavesSize);
	~Extinguisher();

	void moveToCoord(int x, int y);

private:
	// Will check the collision with the leaf.
	// This will be implemented using the ratio of the leaf and the extinguisher
	// (we don't need to give more complexity to collision in this case).
	bool closeEnoughTo(Leaf* leaf);

	unsigned _leavesSize;
	Sprite* _img;
};
