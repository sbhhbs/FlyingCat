#include "Pause.h"
#include "RectWorld.h"

using namespace cocos2d;

bool Pause :: init()
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

		_currentStar = CCLabelBMFont::labelWithString("100","Bigfnt.fnt");
		_currentDistance = CCLabelBMFont::labelWithString("100","Bigfnt.fnt");
		_title = CCLabelBMFont::labelWithString("Game Paused", "Bigfnt.fnt");
		_distanceLabel = CCLabelBMFont::labelWithString("Distance : ", "Bigfnt.fnt");
		_starLabel = CCLabelBMFont::labelWithString("Star gathered : ", "Bigfnt.fnt");
		_resume = CCLabelBMFont::labelWithString("Resume", "Bigfnt.fnt");
		_mainMenu = CCLabelBMFont::labelWithString("Main Menu", "Bigfnt.fnt");

		_currentStar->setScale(0.5f);
		_currentDistance->setScale(0.5f);
		_distanceLabel->setScale(0.5f);
		_starLabel->setScale(0.5f);
		_resume->setScale(0.5f);
		_mainMenu->setScale(0.5f);

		CCMenuItemLabel *resume = CCMenuItemLabel::itemWithLabel(_resume, this, menu_selector(Pause::gameResume));	
		CCMenuItemLabel *menu = CCMenuItemLabel::itemWithLabel(_mainMenu, this, menu_selector(Pause::mainMenu));

		_title->setPosition(ccp(winSize.width / 2,winSize.height / 2 + back->getContentSize().height / 2 - _currentStar->getContentSize().height / 2 - 100));

		_distanceLabel->setPosition(ccp(winSize.width / 2 - back->getContentSize().width / 2 + _distanceLabel->getContentSize().width / 2, 
			_title->getPosition().y - _title->getContentSize().height / 2 -  _distanceLabel->getContentSize().height / 2 ));

		_currentDistance->setPosition(ccp(back->getPosition().x + back->getContentSize().width / 2 - 80 - _currentDistance->getContentSize().width / 2, 
			_title->getPosition().y - _title->getContentSize().height / 2 -  _distanceLabel->getContentSize().height / 2));

		_starLabel->setPosition(ccp(winSize.width / 2 - back->getContentSize().width / 2 + _starLabel->getContentSize().width / 2 - 40, 
			_currentDistance->getPosition().y - _currentDistance->getContentSize().height / 2 -  _starLabel->getContentSize().height / 2 + 10));

		_currentStar->setPosition(ccp(back->getPosition().x + back->getContentSize().width / 2 - 80 - _currentDistance->getContentSize().width / 2, 
			_currentDistance->getPosition().y - _currentDistance->getContentSize().height / 2 -  _starLabel->getContentSize().height / 2 + 10));

		resume->setPosition(ccp(winSize.width / 2 - back->getContentSize().width / 2 + _starLabel->getContentSize().width / 2 - 40, 
			_currentStar->getPosition().y - _currentStar->getContentSize().height / 2 - 3 * _resume->getContentSize().height / 2 + 50));

		menu->setPosition(ccp(back->getPosition().x + back->getContentSize().width / 2 - 40 - _currentDistance->getContentSize().width / 2,
			_currentStar->getPosition().y - _currentStar->getContentSize().height / 2 - 3 * _resume->getContentSize().height / 2 + 50));

		CCMenu *pauseMenu = CCMenu::menuWithItems(resume, menu, NULL);
		pauseMenu->setPosition(CCPointZero);
		pauseMenu->setTag(1);

		this->addChild(_currentStar);
		this->addChild(_currentDistance);
		this->addChild(_title);
		this->addChild(_distanceLabel);
		this->addChild(_starLabel);
		this->addChild(pauseMenu);

		bRet = true;
	} while (0);

	return bRet;
}

CCScene* Pause::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		Pause *layer = Pause::node();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

void Pause :: setStar(long star)
{
	char buffer[8];

	sprintf(buffer,"%d",star);

	_currentStar->setString(buffer);

}

void Pause :: setDistance(long distance)
{
	char buffer[8];

	sprintf(buffer,"%d",distance);

	_currentDistance->setString(buffer);
}

void Pause :: gameResume(CCObject* object)
{
	assert(_delegate);
	_delegate->pauseResumePressed();

	this->removeFromParentAndCleanup(true);
	
}

void Pause :: mainMenu(CCObject* object)
{
	// TODO : Add the main menu part
}

void Pause::setDelegate( BtnProtocal *iamadelegate )
{
	this->_delegate = iamadelegate;
}
