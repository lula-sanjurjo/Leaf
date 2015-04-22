#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
	typedef cocos2d::Scene Super;
public:
	// implement the "static create()" method manually
	CREATE_FUNC(GameOverScene);

	// scene initialisation
	virtual bool init();
};

#endif