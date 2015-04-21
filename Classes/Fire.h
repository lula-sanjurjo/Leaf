#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define FIRE_IMGS_SIZE	2

// This class implements an animation with two images from different resource files.
// It was easier to develop this small class, instead of trying to adapt Cocos's
// animation class to take it's resources like this.
class Fire : public Node
{
public:
	Fire();
	~Fire();

	// Start the burning animation.
	void start();

	// Stop the burning animation.
	// If it was extinguished, show the white smoke.
	// Otherwise, show the black smoke.
	void stop(bool wasExtinguished);

private:
	// Hide the burning animation.
	void hideSmoke();

	// Will change the image being shown.
	void swapImgs();

	// Animation frames.
	Sprite* _imgs[FIRE_IMGS_SIZE];

	// Two types of smokes deppending on how the fire ended.
	Sprite* _whiteSmoke;
	Sprite* _brownSmoke;
};
