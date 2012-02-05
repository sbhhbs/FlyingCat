#include "GameOver.h"
#include "RectWorld.h"
#include "Board.h"
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

		Board *_board = Board :: node();

		_board->setTitle("Game Over");
		_board->setItem1Text("Distance : ");
		_board->setItem2Text("Stars : ");
		_board->setButton1Text("Restart");
		_board->setButton2Text("Main Menu");
		_board->setTag(1);

		//_board->setScale(0.5);

		BoardParent *parent = this;

		// Set Button1 Func && Button2 Func

		_board->setBoardParent(parent);

		this->addChild(_board);

		_board->setPosition(ccpAdd(_board->getPosition(),ccp(0,-500)));
		_board->runAction(CCEaseBounceOut::actionWithAction(CCMoveBy::actionWithDuration(0.2f,ccp(0,500))));


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

void GameOver :: setItem2Descriptor(std::string text)
{
	Board *board = (Board *)this->getChildByTag(1);
	board->setItem2Descriptor(text.c_str());

}

void GameOver :: setItem1Descriptor(std::string text)
{
	Board *board = (Board *)this->getChildByTag(1);

	board->setItem1Descritor(text);
}

void GameOver :: button1Func(CCObject* object)
{
	assert(_delegate);
	_delegate->pauseRestartPressed();

	//this->removeFromParentAndCleanup(true);

}

void GameOver :: button2Func(CCObject* object)
{
	// TODO : Add the main menu part
}