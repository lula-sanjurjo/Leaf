#pragma once

#include "cocos2d.h"
#include "Fire.h"

USING_NS_CC;

class Leaf: public Node
{
public:
	Leaf();
	~Leaf();

	// If the leaf is burning (and not dead), stop the fire.
	void extinguish();

private:
	enum LeafState{
		Normal=0,
		Burning,
		Dead
	};

	// Set the state of the leaf.
	void setState(LeafState state);

	// Will start the burning animation over the leaf.
	void startFire();

	// The leaf dies because it is completely burned.
	void burned();

	// The state of the leaf.
	LeafState _state;

	// The different states of the leaf.
	Sprite* _imgDead;
	Sprite* _imgHappy;
	Sprite* _imgBurning;

	// The burning animation
	Fire* _fire;
};

