#include "Extinguisher.h"

Extinguisher::Extinguisher(Leaf** leaves, unsigned leavesSize){
	// Save the reference to the leaves.
	_leavesSize = leavesSize;
	_leaves = new Leaf*[leavesSize];
	for (unsigned i = 0; i < _leavesSize; i++){
		_leaves[i] = leaves[i];
	}

	// Create the image of the extinguisher
	Sprite* img = Sprite::create("BlueBlob-Normal.png");
	img->setScale(0.5f);
	img->setPosition(0, 0);
	// Set ratio.
	_ratio = img->getBoundingBox().size.width/2;

	// Add the sprite as a child
	this->addChild(img);
}

Extinguisher::~Extinguisher(){
	this->removeAllChildren();
	delete[_leavesSize] _leaves;
}

void Extinguisher::moveToCoord(int x, int y){
	// Move the extinguisher
	this->setPosition(x, y);

	// Check if it is close enough to extinguish a burning leaf.
	for (unsigned i = 0; i < _leavesSize; i++){
		if (closeEnoughTo(_leaves[i])){
			// It is close! So we can extinguish it.
			_leaves[i]->extinguish();
		}
	}
}

bool Extinguisher::closeEnoughTo(Leaf* leaf){
	// Get the distance between extinguisher and leaf.
	float distance = leaf->getPosition().getDistance(this->getPosition());
	
	return ((leaf->getRatio() + _ratio) >= distance);
}