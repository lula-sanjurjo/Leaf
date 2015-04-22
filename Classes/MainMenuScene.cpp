#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"

#define PLAY_BUTTON_SIZE		75

#define TITLE_SIZE				100
#define TITLE_COLOR				Color3B(0, 255, 0)
#define TITLE_OFFSET_Y			175

#define INSTRUCTIONS_SIZE		50
#define INSTRUCTIONS_COLOR		Color3B(15, 145, 145)
#define INSTRUCTIONS_OFFSET_Y	(- 200)

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
	// Add a label to the button.
	Label* playButtonLabel = Label::createWithTTF("Play!", "fonts/Marker Felt.ttf", PLAY_BUTTON_SIZE);
	playButtonLabel->setPosition(playButton->getContentSize().width/2, playButton->getContentSize().height/2);
	playButton->addChild(playButtonLabel);
	// Create a menu with the button.
	auto menu = Menu::create(playButton, nullptr);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	// Add the title of the game.
	Label* title = Label::createWithTTF("Welcome to Leaf", "fonts/Marker Felt.ttf", TITLE_SIZE);
	title->setColor(TITLE_COLOR);
	title->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + TITLE_OFFSET_Y);
	this->addChild(title);

	// Add the instructions of the game.
	Label* instructions = Label::createWithTTF("Help our blue friend to take care of the leaves.\nDon't let them burn!", "fonts/Marker Felt.ttf", INSTRUCTIONS_SIZE);
	instructions->setColor(INSTRUCTIONS_COLOR);
	instructions->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + INSTRUCTIONS_OFFSET_Y);
	this->addChild(instructions);

	// TODO: Add some leaves to the scene.

	// done
	return true;
}

void MainMenuScene::onExit()
{
	Super::onExit();

	this->removeAllChildrenWithCleanup(true);
}

void MainMenuScene::goToGameScene(Ref* sender){
	// create and run scene. it's an autorelease object
	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}