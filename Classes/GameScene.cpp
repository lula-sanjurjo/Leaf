//
//  GameScene.cpp
//  ExpJam
//
//  Created by Two Tails on 09/12/2014.
//
//

#include "GameScene.h"
#include "GameOverScene.h"
#include "Leaf.h"
#include "Definitions.h"
#include "MainMenuScene.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool GameScene::init()
{
    // super init first
    if ( !Super::init() )
    {
        return false;
    }

	// Create the position for the leaves.
	int startAt = 100;
	int separationX = 150;
	int separationY = 110;
	Point positions[LEAVES_AMOUNT];
	for (int i = 0; i < LEAVES_COLUMNS; i++){
		for (int j = 0; j < LEAVES_ROWS; j++){
			positions[i + j * LEAVES_COLUMNS] = Point(startAt + separationX * i, startAt + separationY * j);
		}
	}
    
	// Create the leaves.
	srand(time(0));
	for (int i = 0; i < LEAVES_AMOUNT; i++){
		_leaves[i] = new Leaf(positions[i].x, positions[i].y);
		this->addChild(_leaves[i]);

		// Suscribe to the leaf events.
		_leafEventListener[i] = EventListenerCustom::create("leaf_dies_event", [=](EventCustom* event){
			this->aLeafDied();
		});
		_eventDispatcher->addEventListenerWithSceneGraphPriority(_leafEventListener[i], _leaves[i]);
	}
 
	// Create the extinguisher and give him the leaves references.
	_theGoodGuy = new Extinguisher(_leaves, LEAVES_AMOUNT);
	// get visible size of window
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// Set the good guy to be in the middle of the screen.
	_theGoodGuy->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(_theGoodGuy);

    // done
    return true;
}

void GameScene::onEnter()
{
    Super::onEnter();
    
    // create a mouse event listener
    if( _mouseEventListener == NULL )
    {
        _mouseEventListener = EventListenerMouse::create();
		_mouseEventListener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
    }
    
    // register event listeners
    _eventDispatcher->addEventListenerWithSceneGraphPriority( _mouseEventListener, this );
    
    // schedule update calls
    scheduleUpdate();
}

void GameScene::onExit()
{
    Super::onExit();

	// Release the exthinguisher.
	this->removeChild(_theGoodGuy);
	delete _theGoodGuy;
	// Release the leaves.
	for (int i = 0; i < LEAVES_AMOUNT; i++){
		// de-register leaf event listeners
		_eventDispatcher->removeEventListener(_leafEventListener[i]);
		// Release the leaves.
		this->removeChild(_leaves[i]);
		delete _leaves[i];
	}

	this->removeAllChildren();

	// de-register event listeners
	_eventDispatcher->removeEventListener(_mouseEventListener);

	// unschedule update
    unscheduleUpdate();
}

void GameScene::onMouseMove(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    // Our good guy must move!
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_theGoodGuy->moveToCoord(e->getCursorX(), visibleSize.height + e->getCursorY());
}

void GameScene::aLeafDied(){
	bool allLeavesDead = true;

	// A leaf has died. Check if there is at least one leaf alive.
	for (int i = 0; i < LEAVES_AMOUNT; i++){
		if (_leaves[i]->isAlive()){
			allLeavesDead = false;
			break;
		}
	}

	// Check condition to end game.
	if (allLeavesDead){
		// create and run scene. it's an autorelease object
		auto scene = GameOverScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}
}