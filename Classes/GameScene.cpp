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

USING_NS_CC;

// TODO: Change name to "GameScene"

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
		auto listener = EventListenerCustom::create("leaf_dies_event", [=](EventCustom* event){
			this->aLeafDied();
		});
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _leaves[i]);
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
    
    // create a keyboard event listener
    if( _keyEventListener == NULL )
    {
        _keyEventListener = EventListenerKeyboard::create();
		_keyEventListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
		_keyEventListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    }
    
    // create a mouse event listener
    if( _mouseEventListener == NULL )
    {
        _mouseEventListener = EventListenerMouse::create();
		_mouseEventListener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
		_mouseEventListener->onMouseUp = CC_CALLBACK_1(GameScene::onMouseUp, this);
		_mouseEventListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
		_mouseEventListener->onMouseScroll = CC_CALLBACK_1(GameScene::onMouseScroll, this);
    }
    
    // register event listeners
    _eventDispatcher->addEventListenerWithSceneGraphPriority( _keyEventListener, this );
    _eventDispatcher->addEventListenerWithSceneGraphPriority( _mouseEventListener, this );
    
    // schedule update calls
    scheduleUpdate();
}

void GameScene::onExit()
{
    Super::onExit();

	// Remove event listeners
	_eventDispatcher->removeAllEventListeners();

	// Release the memory
	_theGoodGuy->release();//delete _theGoodGuy;?
	for (int i = 0; i < LEAVES_AMOUNT; i++)
		_leaves[i]->release();// delete _leaves[i];?
    
    // de-register event listeners
    _eventDispatcher->removeEventListener( _keyEventListener );
    _eventDispatcher->removeEventListener( _mouseEventListener );
    
    // unschedule update
    unscheduleUpdate();
}

void GameScene::update(float delta)
{
    // called once per frame
//    cocos2d::log( "Update: %f", delta );
    
}


#pragma mark - Key Events


void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    cocos2d::log( "Key with keycode %d pressed", keyCode );
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    cocos2d::log( "Key with keycode %d released", keyCode );
}


#pragma mark - Mouse Events


void GameScene::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Down detected, Key: ";
    str += std::to_string(e->getMouseButton());
    cocos2d::log( "%s", str.c_str() );
}

void GameScene::onMouseUp(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Up detected, Key: ";
    str += std::to_string(e->getMouseButton());
    cocos2d::log( "%s", str.c_str() );
}

void GameScene::onMouseMove(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    // Our good guy must move!
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_theGoodGuy->moveToCoord(e->getCursorX(), visibleSize.height + e->getCursorY());
}

void GameScene::onMouseScroll(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Scroll detected, X: ";
    str += std::to_string(e->getScrollX()) + " Y: " + std::to_string(e->getScrollY());
    cocos2d::log( "%s", str.c_str() );
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

	if (allLeavesDead){
		// create and run scene. it's an autorelease object
		auto scene = GameOverScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));// TODO: DEFINE TRANSITION TIME.
	}
}