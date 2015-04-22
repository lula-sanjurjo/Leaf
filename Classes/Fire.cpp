#include "Fire.h"

Fire::Fire()
{
	// Create the smoke sprites.
	_whiteSmoke = Sprite::create("Smoke_White.png");
	_brownSmoke = Sprite::create("Smoke_Brown.png");
	// Scale the smokes
	_whiteSmoke->setScale(0.5f);
	_brownSmoke->setScale(0.5f);
	// Don't show the smokes until necessary.
	_whiteSmoke->setVisible(false);
	_brownSmoke->setVisible(false);

	this->addChild(_whiteSmoke);
	this->addChild(_brownSmoke);

	// Create the fire frames
	for (int i = 0; i < FIRE_IMGS_SIZE; i++){
		std::string str = "Flame";
		str += std::to_string(i+1);
		str += ".png";
		_imgs[i] = Sprite::create(str);

		// Configure some properties so the fire is shown at on "start()".
		_imgs[i]->setScale(0.25f);
		_imgs[i]->setPositionY(-15);
		_imgs[i]->setVisible(false);
		this->addChild(_imgs[i]);
	}
}

Fire::~Fire()
{
	this->removeAllChildren();
}

void Fire::start(){
	// Make fire visible
	_imgs[0]->setVisible(true);

	// Create the burning sequence, swapping fire images.
	FiniteTimeAction *callAct = CallFunc::create(CC_CALLBACK_0(Fire::swapImgs, this));
	this->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.5f), callAct, nullptr)));
}

void Fire::stop(bool wasExtinguished) {
	// Stop the burning action.
	this->stopAllActions();

	if (wasExtinguished){
		_whiteSmoke->setVisible(true);	
	}
	else{
		_brownSmoke->setVisible(true);
	}

	// Show the smoke for a while, and then the fire stops.
	FiniteTimeAction *callAct = CallFunc::create(CC_CALLBACK_0(Fire::hideSmoke, this));
	Sequence* seq = Sequence::create(DelayTime::create(1.0f), callAct, nullptr);
	this->runAction(seq);
}

void Fire::hideSmoke(){
	// Stop showing the fire.
	for (int i = 0; i < FIRE_IMGS_SIZE; i++){
		_imgs[i]->setVisible(false);
	}

	// Stop showing the smoke.
	_whiteSmoke->setVisible(false);
	_brownSmoke->setVisible(false);
}

// TODO: don't assume that there are only 2 frames.
void Fire::swapImgs() {
	// Change the image being shown.
	if (_imgs[0]->isVisible()){
		_imgs[0]->setVisible(false);
		_imgs[1]->setVisible(true);
	}
	else {
		_imgs[0]->setVisible(true);
		_imgs[1]->setVisible(false);
	}
}