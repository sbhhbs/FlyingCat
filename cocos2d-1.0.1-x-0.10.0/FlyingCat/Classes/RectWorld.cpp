#include "RectWorld.h"
#include "ccMacros.h"
#include "MovingBackground.h"
#include "string"
#include "Cat1.h"

using namespace cocos2d;

CCScene* RectWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        RectWorld *layer = RectWorld::node();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RectWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.

        // Create a menu with the "close" menu item, it's an auto release object.

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();

        // 3. Add add a splash screen, show the cocos2d splash image.

        // Place the sprite on the center of the screen

		MovingBackground *bk = MovingBackground::node();

		this->addChild(bk);


		//CCParticleSystem *particle = ARCH_OPTIMAL_PARTICLE_SYSTEM::particleWithFile("tile.plist");

		//particle->setPosition(ccp(_player->getContentSize().width / 2 + size.width / 5 * 3, size.height / 2));

		//this->addChild(particle, 1);

		this->schedule(schedule_selector(RectWorld::gameLogic), 1.0);
		this->schedule(schedule_selector(RectWorld::update));

		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);

        bRet = true;
    } while (0);

    return bRet;
}

void RectWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}


RectWorld :: RectWorld()
{
	_flyState = false; 
	_speed = 4;
	_barriers = new CCMutableArray<CCSprite*>();
};


RectWorld :: ~RectWorld()
{
	//if(_player != NULL)
	//{
	//	this->removeChild(_player);
	//	delete(_player);
	//}
	if (_barriers != NULL)
		_barriers->release();
}


bool RectWorld :: ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint location = touch->locationInView(touch->view());
	Cat1 *cat1 = (Cat1*)this->getChildByTag(1);

	if(location.x > 480)
		_flyState = 2;
	else
		_flyState = 1;
	cat1->flyUpAnimation(); 
	return true;
}

void RectWorld :: ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	Cat1 *cat1 = (Cat1*)this->getChildByTag(1);

	cat1->flyDownAnimation();
	_flyState = 0;
}

void RectWorld :: update(ccTime dt)
{
	Cat1 *cat1 = (Cat1*)this->getChildByTag(1);

	if(cat1 == NULL)
		return;

	if(_flyState == 2)
	{
		cat1->setPosition(ccp(cat1->getPosition().x, cat1->getPosition().y - (float)_speed / 3));
	}
	if(_flyState == 1)
	{
		if(cat1->getPosition().y + _speed + cat1->getBody()->getContentSize().height / 2 >= 640)
			cat1->setPosition(ccp(cat1->getPosition().x, 640 - cat1->getBody()->getContentSize().height / 2));
		cat1->setPosition(ccp(cat1->getPosition().x, cat1->getPosition().y + _speed));
	}
	else if (_flyState == 0)
	{
		if(cat1->getPosition().y - _speed + cat1->getBody()->getContentSize().height / 2 <= 0)
			cat1->setPosition(ccp(cat1->getPosition().x, cat1->getBody()->getContentSize().height / 2));
		else
			cat1->setPosition(ccp(cat1->getPosition().x, cat1->getPosition().y - _speed));
	}
}

void RectWorld :: addTarget()
{

	static float actualDuration = 4.0f;
	static int times = 0;
	times ++;

	if (times > 100)
	{
		actualDuration -= 0.5f;
		times = 0;
	}

	if(actualDuration < 1)
		actualDuration = 1.0f;

	std::string src = "barrier_.png";
	int index = rand() % 8;
	char sequence = index + '0';
	std::string :: iterator it = src.begin();
	while(*it != '.')
		it++;
	src.insert(it, sequence);

	// Complete the bitmap select

	CCSprite* barrier = CCSprite :: spriteWithFile(src.c_str(), CCRectMake(0, 0, 96, rand() % 257));

	CCSize winSize = CCDirector :: sharedDirector()->getWinSize();
	
	if(barrier->getContentSize().height < 150)
		barrier->setScaleY(150.0f / barrier->getContentSize().height);

	int count = _barriers->count();

	int initialX = (float) winSize.width - barrier->getContentSize().width / 2 + count * 200;
	int initialY = winSize.height * ( rand() % 641 ) / 641 - barrier->getContentSize().height / 2 ;

	if(initialY < 0 )
		initialY  = 0;

	barrier->setPosition(ccp(initialX, initialY));
	this->addChild(barrier);
	_barriers->addObject(barrier);

	CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration((ccTime)actualDuration, ccp(0 - barrier->getContentSize().width / 2, initialY));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(RectWorld::spriteMoveFinished));

	barrier->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));

	if (initialY + barrier->getContentSize().height / 2 < winSize.height / 2)
	{
		src = "barrier_.png";
		index = rand() % 8;
		sequence = index + '0';
		it = src.begin();
		while(*it != '.')
			it++;
		src.insert(it, sequence);

		// Complete the bitmap select

		CCSprite* barrierSecond = CCSprite :: spriteWithFile(src.c_str(), CCRectMake(0, 0, 96, rand() % 257));

		if(barrierSecond->getContentSize().height < 150)
			barrierSecond->setScaleY(150.0f / barrierSecond->getContentSize().height);

		initialY = winSize.height * ( 1 - rand() % 151 / 300 ) - barrierSecond->getContentSize().height / 2;

		barrierSecond->setPosition(ccp(initialX, initialY));
		this->addChild(barrierSecond);
		_barriers->addObject(barrierSecond);

		actionMove = CCMoveTo::actionWithDuration((ccTime)actualDuration, ccp(0 - barrierSecond->getContentSize().width / 2, initialY));

		barrierSecond->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));

	}
	else if (initialY - barrier->getContentSize().height / 2 > winSize.height / 2)
	{
		src = "barrier_.png";
		index = rand() % 8;
		sequence = index + '0';
		it = src.begin();
		while(*it != '.')
			it++;
		src.insert(it, sequence);

		// Complete the bitmap select

		CCSprite* barrierSecond = CCSprite :: spriteWithFile(src.c_str(), CCRectMake(0, 0, 96, rand() % 257));

		if(barrierSecond->getContentSize().height < 150)
			barrierSecond->setScaleY(150.0f / barrierSecond->getContentSize().height);

		initialY = winSize.height * ( rand() % 151 / 300 ) - barrierSecond->getContentSize().height / 2;

		if(initialY < 0)
			initialY = 0;

		barrierSecond->setPosition(ccp(initialX, initialY));
		this->addChild(barrierSecond);
		_barriers->addObject(barrierSecond);

		actionMove = CCMoveTo::actionWithDuration((ccTime)actualDuration, ccp(0 - barrierSecond->getContentSize().width / 2, initialY));

		barrierSecond->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));

	}
}

void RectWorld :: spriteMoveFinished(CCNode* sender)
{
	CCSprite *barrier = (CCSprite*)sender;
	this->removeChild(barrier, true);

	_barriers->removeObject(barrier);
}

void RectWorld :: gameLogic(ccTime dt)
{
	this->addTarget();
}