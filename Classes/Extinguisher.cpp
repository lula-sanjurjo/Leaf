#include "Extinguisher.h"

Extinguisher::Extinguisher(Leaf** _leaves, unsigned leavesSize)
{
	_leavesSize = leavesSize;
	// TODO: copy the reference to the leaves.

	_img = Sprite::create("BlueBlob-Normal.png");
	_img->setScale(0.5f);

	_img->setPosition(0, 0);

	// add the sprite as a child
	this->addChild(_img);
}

Extinguisher::~Extinguisher()
{
	this->removeAllChildren();
	//delete _img; how?
}

void Extinguisher::moveToCoord(int x, int y) {
	// Move the extinguisher
	this->setPosition(x, y);

	// Check if it is close enough to extinguish a burning leaf.
	for (unsigned i = 0; i < _leavesSize; i++){
//		if (closeEnoughTo(_leaves[i])){
//			_leaves[i]->extinguish();
//		}
	}
}

bool Extinguisher::closeEnoughTo(Leaf* leaf){
	// TODO: collision if la distancia euclideana entre los dos es menor a los ratios sumados.
	return false;
}