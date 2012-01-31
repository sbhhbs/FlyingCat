#include "GameOver.h"
#include "RectWorld.h"

using namespace cocos2d;

bool GameOver :: init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		CCLayerColor::initWithColor(ccc4(0, 0, 0, 100));
		CC_BREAK_IF(! CCLayer::init());

		CCSprite *back = CCSprite::spriteWithFile("back.png");

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		back->setPosition(ccp(winSize.width / 2, winSize.height / 2));

		this->addChild(back);

		//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);

		_delegate = NULL;

		_finalStar = CCLabelBMFont::labelWithString("100","Bigfnt.fnt");
		_finalDistance = CCLabelBMFont::labelWithString("100","Bigfnt.fnt");
		_title = CCLabelBMFont::labelWithString("Game Over", "Bigfnt.fnt");
		_distanceLabel = CCLabelBMFont::labelWithString("Distance : ", "Bigfnt.fnt");
		_starLabel = CCLabelBMFont::labelWithString("Star gathered : ", "Bigfnt.fnt");
		_restart = CCLabelBMFont::labelWithString("Restart", "Bigfnt.fnt");
		_mainMenu = CCLabelBMFont::labelWithString("Main Menu", "Bigfnt.fnt");

		_finalStar->setScale(0.5f);
		_finalDistance->setScale(0.5f);
		_distanceLabel->setScale(0.5f);
		_starLabel->setScale(0.5f);
		_restart->setScale(0.5f);
		_mainMenu->setScale(0.5f);

		CCMenuItemLabel *restart = CCMenuItemLabel::itemWithLabel(_restart, this, menu_selector(GameOver::gameRestart));	
		CCMenuItemLabel *menu = CCMenuItemLabel::itemWithLabel(_mainMenu, this, menu_selector(GameOver::mainMenu));

		_title->setPosition(ccp(winSize.width / 2,winSize.height / 2 + back->getContentSize().height / 2 - _finalStar->getContentSize().height / 2 - 100));

		_distanceLabel->setPosition(ccp(winSize.width / 2 - back->getContentSize().width / 2 + _distanceLabel->getContentSize().width / 2, 
			_title->getPosition().y - _title->getContentSize().height / 2 -  _distanceLabel->getContentSize().height / 2 ));

		_finalDistance->setPosition(ccp(back->getPosition().x +  back->getContentSize().width / 2 - 80 - _finalDistance->getContentSize().width / 2, 
			_title->getPosition().y - _title->getContentSize().height / 2 -  _distanceLabel->getContentSize().height / 2));

		_starLabel->setPosition(ccp(winSize.width / 2 - back->getContentSize().width / 2 + _starLabel->getContentSize().width / 2 - 40, 
			_finalDistance->getPosition().y - _finalDistance->getContentSize().height / 2 -  _starLabel->getContentSize().height / 2 + 10));

		_finalStar->setPosition(ccp(back->getPosition().x + back->getContentSize().width / 2 - 80 - _finalDistance->getContentSize().width / 2, 
			_finalDistance->getPosition().y - _finalDistance->getContentSize().height / 2 -  _starLabel->getContentSize().height / 2 + 10));

		_restart->setPosition(ccp(winSize.width / 2 - back->getContentSize().width / 2 + _starLabel->getContentSize().width / 2 - 40, 
			_finalStar->getPosition().y - _finalStar->getContentSize().height / 2 - 3 * _restart->getContentSize().height / 2 + 50));

		menu->setPosition(ccp(back->getPosition().x + back->getContentSize().width / 2 - 40 - _finalDistance->getContentSize().width / 2,
			_finalStar->getPosition().y - _finalStar->getContentSize().height / 2 - 3 * _restart->getContentSize().height / 2 + 50));

		CCMenu *pauseMenu = CCMenu::menuWithItems(restart, menu, NULL);
		pauseMenu->setPosition(CCPointZero);
		pauseMenu->setTag(1);

		this->addChild(_finalStar);
		this->addChild(_finalDistance);
		this->addChild(_title);
		this->addChild(_distanceLabel);
		this->addChild(_starLabel);
		this->addChild(pauseMenu);

		bRet = true;
	} while (0);

	return bRet;
}

CCScene* GameOver::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		GameOver *layer = GameOver::node();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

void GameOver :: setStar(long star)
{
	char buffer[8];

	sprintf(buffer,"%d",star);

	_finalStar->setString(buffer);

}

void GameOver :: setDistance(long distance)
{
	char buffer[8];

	sprintf(buffer,"%d",distance);

	_finalDistance->setString(buffer);
}

void GameOver :: gameRestart(CCObject* object)
{
	assert(_delegate);
	_delegate->pauseResumePressed(); // TODO : Add the restart function

	this->removeFromParentAndCleanup(true);

}

void GameOver :: mainMenu(CCObject* object)
{
	// TODO : Add the main menu part
}

void GameOver::setDelegate( BtnProtocal *iamadelegate )
{
	this->_delegate = iamadelegate;
}
