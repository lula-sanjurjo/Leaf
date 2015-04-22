//
//  GameScene.h
//  ExpJam
//
//  Created by Two Tails on 09/12/2014.
//
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Extinguisher.h"
#include "Leaf.h"

#define LEAVES_COLUMNS	6
#define LEAVES_ROWS		5
#define LEAVES_AMOUNT	(LEAVES_COLUMNS * LEAVES_ROWS)

class GameScene : public cocos2d::Scene
{
    typedef cocos2d::Scene Super;
public:
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

    // scene initialisation
    virtual bool init();
    // scene shown
    virtual void onEnter();
    // scene hidden
    virtual void onExit();
    
    // called once per frame
    virtual void update( float delta );
    
    // key pressed event
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    // key lifted event
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    // mouse pressed down
    void onMouseDown( cocos2d::Event *event );
    // mouse button lifted
    void onMouseUp( cocos2d::Event *event );
    // mouse moved
    void onMouseMove( cocos2d::Event *event );
    // mouse scroll
    void onMouseScroll( cocos2d::Event *event );
    
	// Returns true if the leaf is alive.
	bool isAlive();
    
private:
	// Called when a leaf_dies_event event is received.
	void aLeafDied();

	Extinguisher* _theGoodGuy;
	Leaf* _leaves[LEAVES_AMOUNT];
    
    cocos2d::EventListenerKeyboard* _keyEventListener = NULL;
    cocos2d::EventListenerMouse* _mouseEventListener = NULL;
};

#endif
