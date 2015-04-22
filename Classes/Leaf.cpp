#include "Leaf.h"

Leaf::Leaf(int x, int y) :
_state(Normal),
_ratio(0),
_imgDead(CCSprite::create("Leefy-Skeleton.png")),
_imgHappy(CCSprite::create("Leefy-Happy.png")),
_imgBurning(CCSprite::create("Leefy-Bump.png")),
_fire(new Fire())
{
	// Change the size, the resources are too big.
	_imgDead->setScale(0.25f);
	_imgHappy->setScale(0.25f);
	_imgBurning->setScale(0.25f);
	// Add images as childs
	this->addChild(_imgDead);
	this->addChild(_imgHappy);
	this->addChild(_imgBurning);
	this->addChild(_fire);
	// Hide the images that are not yet shown.
	_imgDead->setVisible(false);
	_imgBurning->setVisible(false);

	// Create a ratio that is good for colliding (visually).
	_ratio = _imgHappy->getBoundingBox().size.width / 2;

	// Set the position.
	this->setPosition(x, y);

	// The leaf starts it's life in a Normal state.
	setState(Normal);
	startBurningAfterAWhile();
}

Leaf::~Leaf()
{
	this->removeAllChildren();
	delete _fire;// ok?
}

int Leaf::getRatio(){
	return _ratio;
}

void Leaf::startFire(){
	setState(Burning);
}

void Leaf::burned(){
	setState(Dead);
}

void Leaf::extinguish() {
	setState(Normal);
}

void Leaf::startBurningAfterAWhile(){
	// After a random amount of seconds, the leaf will start burning.
	FiniteTimeAction *callAct = CallFunc::create(CC_CALLBACK_0(Leaf::startFire, this));
	this->runAction(Sequence::create(DelayTime::create(3.0f + rand() % 10), callAct, nullptr));
}

void Leaf::setState(LeafState state){
	// If the leaf is dead, it doesn't accept new state changes.
	if (_state == Dead){
		return;
	}

	switch (state){
	case Normal:
		_imgHappy->setVisible(true);
		_imgBurning->setVisible(false);
		_imgDead->setVisible(false);

		// If the leaf was burning, stop fire.
		if (_state == Burning){
			// Stop all the fire actions.
			_fire->stop(true);
			this->stopAllActions();

			// After a random amount of seconds, the leaf will start burning.
			startBurningAfterAWhile();
		}
		break;

	case Burning:
		// The leaf starts burning.
		if (_state == Normal){
			// Show the burning face of the leaf.
			_imgHappy->setVisible(false);
			_imgBurning->setVisible(true);
			_imgDead->setVisible(false);

			// Start the fire.
			_fire->start();
			// After 5 seconds, the leaf burns completely and dies.
			FiniteTimeAction *callAct = CallFunc::create(CC_CALLBACK_0(Leaf::burned, this));
			this->runAction(Sequence::create(DelayTime::create(5.0f), callAct, nullptr));
		}
		break;

	case Dead:
		// The leaf was burned
		_imgHappy->setVisible(false);
		_imgBurning->setVisible(false);
		_imgDead->setVisible(true);

		// Stop the fire.
		_fire->stop(false);
		break;
	}

	// Update the state.
	_state = state;
}