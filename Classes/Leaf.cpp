#include "Leaf.h"

// TODO: have three states for the leaf: {normal, burning, dead},
// and handle images and burning animation accordingly.

Leaf::Leaf() :
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
	_ratio = _imgHappy->getBoundingBox().size.width/2;

	// get visible size of window
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// The leaf will be placed on a random place in the screen.
	CCPoint pos = ccp(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height);
	this->setPosition(pos);

	this->addChild(_imgDead);
	this->addChild(_imgHappy);
	this->addChild(_imgBurning);
	this->addChild(_fire);

	_imgDead->setVisible(false);
	_imgBurning->setVisible(false);

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
	this->runAction(Sequence::create(DelayTime::create(rand() % 10), CallFunc::create(this, callfunc_selector(Leaf::startFire)), nullptr));//deprecated!
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
			this->runAction(Sequence::create(DelayTime::create(5.0f), CallFunc::create(this, callfunc_selector(Leaf::burned)), nullptr));//deprecated!
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