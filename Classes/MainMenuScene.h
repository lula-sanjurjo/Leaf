#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
	typedef cocos2d::Scene Super;
public:
	// implement the "static create()" method manually
	CREATE_FUNC(MainMenuScene);

	// scene initialisation
	virtual bool init();
	// scene hidden
	virtual void onExit();

private:
	void goToGameScene(Ref* sender);
};

#endif