#include "GameOverScene.h"
#include "GameScene.h"
#include "Definitions.h"

#define TITLE_SIZE		100
#define TITLE_COLOR		Color3B(0, 255, 0)
#define TITLE_OFFSET_Y	175

#define SCORE_SIZE		75
#define SCORE_COLOR		Color3B(15, 145, 145)
#define SCORE_OFFSET_Y	(- 200)

#define PLAY_AGAIN_SIZE	65

USING_NS_CC;

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
	// super init first
	if (!Super::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Create the "play again button".
	auto playAgainButton = MenuItemImage::create("menu/ButtonGreen.png", "menu/ButtonBlue.png", CC_CALLBACK_1(GameOverScene::goToGameScene, this));
	playAgainButton->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	// Create a label for the button.
	Label* playAgainButtonLabel = Label::createWithTTF("Play again!", "fonts/Marker Felt.ttf", PLAY_AGAIN_SIZE);
	playAgainButtonLabel->setPosition(playAgainButton->getContentSize().width / 2, playAgainButton->getContentSize().height / 2);
	playAgainButton->addChild(playAgainButtonLabel);
	// Create a menu with the button.
	auto menu = Menu::create(playAgainButton, nullptr);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	// Add the "Well done" text.
	Label* title = Label::createWithTTF("Well done!", "fonts/Marker Felt.ttf", TITLE_SIZE);
	title->setColor(TITLE_COLOR);
	title->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + TITLE_OFFSET_Y);
	this->addChild(title);

	// Show the final score.
	Label* score = Label::createWithTTF("Thank you for playing!", "fonts/Marker Felt.ttf", SCORE_SIZE);
	score->setColor(SCORE_COLOR);
	score->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + SCORE_OFFSET_Y);
	this->addChild(score);

	// done
	return true;
}
void GameOverScene::onExit()
{
	Super::onExit();

	this->removeAllChildren();
}

void GameOverScene::goToGameScene(Ref* sender){
	// create and run scene. it's an autorelease object
	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}