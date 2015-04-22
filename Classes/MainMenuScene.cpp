#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	// super init first
	if (!Super::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Create the button to start playing.
	auto playButton = MenuItemImage::create("menu/ButtonGreen.png", "menu/ButtonBlue.png", CC_CALLBACK_1(MainMenuScene::goToGameScene, this));
	playButton->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	Label* playButtonLabel = Label::create("Play!", "fonts/Marker Felt.ttf", 75);
	playButtonLabel->setPosition(playButton->getContentSize().width/2, playButton->getContentSize().height/2);
	playButton->addChild(playButtonLabel);
	
	

	auto menu = Menu::create(playButton, nullptr);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	// Add the title of the game.
	Label* title = Label::create("Welcome to Leaf", "fonts/Marker Felt.ttf", 100);
	title->setColor(ccc3(0, 255, 0));
	title->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 175);
	this->addChild(title);

	// Add the instructions of the game.
	Label* instructions = Label::create("Help our blue friend to take care of the leaves.\nDon't let them burn!", "fonts/Marker Felt.ttf", 50);
	instructions->setColor(ccc3(15, 145, 145));
	instructions->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 200);
	this->addChild(instructions);

	// TODO: Add some leaves to the scene.

	// done
	return true;
}

void MainMenuScene::goToGameScene(Ref* sender){
	auto scene = GameScene::create();

	Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene));// TODO: DEFINE TRANSITION TIME.
}