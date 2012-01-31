#include "Warning.h"

Warning :: Warning()
{
	_angle = 45;
	_warningContent = "Be careful!";
}

Warning :: Warning(int angle, std :: string warningContent)
{
	_angle = angle;
	_warningContent = warningContent;
}

bool Warning :: init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		CC_BREAK_IF(! CCLayer::init());

		CCSprite *back = CCSprite::spriteWithFile("warning-hd.png");

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		back->setPosition(ccp(winSize.width / 2, winSize.height / 2));

		this->addChild(back);

		//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);

		_delegate = NULL;

		_warningLabel = CCLabelBMFont::labelWithString(_warningContent.c_str(),"Bigfnt.fnt");

		_warningLabel->setScale(1.0f);

		_warningLabel->setRotation((-1) * _angle);

		_warningLabel->setColor(ccc3(0, 0, 255));

		_warningLabel->setPosition(ccp(winSize.width / 2, winSize.height / 2));

		_warningLabel->setTag(1);
	
		this->addChild(_warningLabel);

		bRet = true;
	} while (0);

	return bRet;
}

CCScene* Warning :: scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		Warning *layer = Warning::node();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}