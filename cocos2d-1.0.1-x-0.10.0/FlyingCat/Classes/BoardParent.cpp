#include "BoardParent.h"

void BoardParent :: setDelegate(BtnProtocal *iamadelegate)
{
	_delegate = iamadelegate;
}

void BoardParent :: button1Func(CCObject* object)
{

}

void BoardParent :: button2Func(CCObject* object)
{

}

void BoardParent :: setItem1Descriptor(std::string text)
{

}

void BoardParent :: setItem2Descriptor(std::string text)
{

}

bool BoardParent :: init()
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

		bRet = true;
	} while (0);

	return bRet;
}



CCScene* BoardParent :: scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		BoardParent *layer = BoardParent::node();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}