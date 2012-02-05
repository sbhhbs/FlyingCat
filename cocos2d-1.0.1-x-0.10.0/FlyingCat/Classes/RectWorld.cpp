#include "RectWorld.h"
#include "ccMacros.h"
#include "MovingBackground.h"
#include "string"
#include "Cat1.h"
#include "Pause.h"
#include "ScoreLayer.h"
#include "Warning.h"
#include "TimeLayer.h"
#include "GameOver.h"
#include "DataCore.h"
#include "AchievementCore.h"
#include "TimeCount.h"


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
		CCMenuItemImage *pPauseItem = CCMenuItemImage::itemFromNormalImage("pause.png","pause.png",this,menu_selector(RectWorld::menuPause));
		CC_BREAK_IF(! pPauseItem);

		

		// Place the menu item bottom-right conner.
		pPauseItem->setPosition(ccp(22, 22));
		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::menuWithItems(pPauseItem, NULL);
		pMenu->setPosition(CCPointZero);
		pMenu->setTag(6);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 4);

		// Add the warning layer
		Warning *warning = Warning :: node();
		
		warning->setIsVisible(false);
		warning->setTag(20);
		this->addChild(warning, 3);

		TimeCount *timeCount = TimeCount :: node();
		timeCount->continueCount();
		timeCount->setIsVisible(false);
		timeCount->setTag(30);

		this->addChild(timeCount);
		

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

		//this->schedule(schedule_selector(RectWorld::collision));
		this->schedule(schedule_selector(RectWorld::gameLogic), 1.0);
		this->schedule(schedule_selector(RectWorld::update));
		this->schedule(schedule_selector(RectWorld::removeObjects, 1.0f));

		AchivementCore::sharedCore()->setLayer(this);


		//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
		if (_type == 1)
		{


		}
		else if (_type == 2)
		{

		}
		else if (_type == 3)
		{
			TimeLayer *timeLayer = TimeLayer :: node();
			timeLayer->setInitalTime(60);
			timeLayer->setTag(4);

			timeLayer->setDelegate(this);


			this->addChild(timeLayer, 3);

			this->schedule(schedule_selector(RectWorld::clockPassBy), 1.0f);
		}

        bRet = true;
    } while (0);

    return bRet;
}

void RectWorld::menuPause(CCObject* pSender)
{
	_gameOver = true;

	TimeCount *timeCount = (TimeCount *)this->getChildByTag(30);
	timeCount->stopCount();

    this->pauseSchedulerAndActions();

	CCMutableArray<CCSprite*> :: CCMutableArrayIterator it;

	for(it = _barriers->begin(); it != _barriers->end(); it++)
	{
		(*it)->pauseSchedulerAndActions();
	}

	for(it = _stars->begin(); it != _stars->end(); it++)
	{
		(*it)->pauseSchedulerAndActions();
	}

	Pause *pause = Pause::node();
	pause->setDelegate(this);

	CCMenu *pItem = (CCMenu *)this->getChildByTag(6);
	pItem->setIsVisible(false);

	ScoreLayer *scoreLayer = (ScoreLayer *)this->getChildByTag(2);
	scoreLayer->setIsVisible(false);

	ScoreLayer *score = (ScoreLayer*)this->getChildByTag(2);

	char buffer[8];

	itoa(score->getCurrentDistance(), buffer, 10);
	pause->setItem1Descriptor(buffer);

	itoa(score->getCurrentStar(), buffer, 10);
	pause->setItem2Descriptor(buffer);

	if (_type == 3)
	{
		TimeLayer *timeLayer = (TimeLayer*)this->getChildByTag(4);
		timeLayer->setIsVisible(false);
	}

	this->addChild(pause,4);

	
}


RectWorld :: RectWorld()
{
	_gameOver = false;
	_flyState = false; 
	_gravityAccelerate = 9.8 / 3;				// just like on the other moon : )
	_motiveAccelerate = 9.8 / 3;				// will it be like on the moon?
	_currentSpeed = 0;							// well the cat need a current speed, right?
	_type = 2;								

	// If _type == 1, then it's classic mode, which means that the player will have 3 lives
	// If _type == 2, then it's survial mode, which means that the player will only have 1 life
	// If _type == 3, then it's time trial mode, which means that the player will have time limit
	// throughout the game and the time decrease every 1s, whenever the player collide with something
	// the time decrease a lot


	//  I announce that when the value of _currentSpeed is positive, it means
	//  that the cat is going up, then it goes negative, then the cat is affected
	//	only by the gravity and dropping

	_stars = new CCMutableArray<CCSprite*>();
	_barriers = new CCMutableArray<CCSprite*>();
};


RectWorld :: ~RectWorld()
{
	if (_barriers != NULL)
		_barriers->release();
	if (_stars != NULL)
		_stars->release();
}


bool RectWorld :: ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if (_gameOver)
		return true;

	_currentSpeed = 0;

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
	if (_gameOver)
		return;

	Cat1 *cat1 = (Cat1*)this->getChildByTag(1);

	_currentSpeed = 0;

	cat1->flyDownAnimation();
	_flyState = 0;
}

void RectWorld :: update(ccTime dt)
{
	if (_gameOver)
		return;

	AchivementCore::sharedCore()->update();

	Cat1 *cat1 = (Cat1*)this->getChildByTag(1);

	if(cat1 == NULL)
		return;

	if(_flyState == 2)					// this is the slide state 
	{
		cat1->setPosition(ccp(cat1->getPosition().x, cat1->getPosition().y - (float)_currentSpeed / 3));
	}
	if(_flyState == 1)					// this is the up state
	{

		float distance = (_currentSpeed + _currentSpeed + _motiveAccelerate) / 2 * (float)dt;
		_currentSpeed += _motiveAccelerate;

		if(cat1->getPosition().y + distance + cat1->getBody()->getContentSize().height >= 610)
		{
			cat1->setPosition(ccp(cat1->getPosition().x, 610 - cat1->getBody()->getContentSize().height));
			//_gameOver = true;
			cat1->deadAnimation();
		}
		cat1->setPosition(ccp(cat1->getPosition().x, cat1->getPosition().y + distance));
	}
	else if (_flyState == 0)			// well the last one is droping!
	{
		float distance = (_currentSpeed + _currentSpeed - _gravityAccelerate) / 2 * (float)dt;

		_currentSpeed -= _gravityAccelerate;	

		if(cat1->getPosition().y - distance <= 25)
		{
			cat1->setPosition(ccp(cat1->getPosition().x, 25));
			cat1->deadAnimation();
			//_gameOver = true;
		}
		else
			cat1->setPosition(ccp(cat1->getPosition().x, cat1->getPosition().y + distance));
	}

	// Common Move Update Complete

	CCRect catRect = CCRectMake(cat1->getPosition().x, cat1->getPosition().y, cat1->getBody()->getContentSize().width, cat1->getBody()->getContentSize().height);

	CCMutableArray<CCSprite*>::CCMutableArrayIterator it;

	for (it = _barriers->begin(); it != _barriers->end(); it++)
	{
		CCSprite *barrier = *it;
		CCRect barrierRect = CCRectMake(barrier->getPosition().x - (barrier->getContentSize().width/2), 
			barrier->getPosition().y - (barrier->getContentSize().height/2),
			barrier->getContentSize().width, barrier->getContentSize().height);

		if (CCRect :: CCRectIntersectsRect(catRect, barrierRect))
		{
			switch(_type)
			{
			case 1:
				// TODO: Add the case 1 codes
				break;
			case 2:
				gameOver();
				break;
			case 3:
			{
				TimeLayer *timeLayer = (TimeLayer*)this->getChildByTag(4);
				
				if (timeLayer != NULL)
				{
					Warning *warning = (Warning *)this->getChildByTag(20);
					if (!warning->getIsVisible())
					{
						if (timeLayer->decreaseCollisionTime())
						{
							gameOver();
						}
						else
							warning->setIsVisible(true);
					}

				}
				break;
			}
			}
			break;
		} 
	}

	// Detect if the cat has collided something

	for (it = _stars->begin(); it != _stars->end(); it++)
	{
		CCSprite *star = *it;
		CCRect starRect = CCRectMake(star->getPosition().x - (star->getContentSize().width/2), 
			star->getPosition().y - (star->getContentSize().height/2),
			star->getContentSize().width, star->getContentSize().height);

		if (CCRect :: CCRectIntersectsRect(catRect, starRect))
		{
			this->removeChild(star, true);
			_stars->removeObject(star);

			ScoreLayer* score = (ScoreLayer*)this->getChildByTag(2);
			score->setCurrentStar(score->getCurrentStar() + 1);

			break;
		} 
	}

	// Detect if the cat has got any star and only one star at a time

	//And at last add the distance

	ScoreLayer *score = (ScoreLayer*)this->getChildByTag(2);
	score->setCurrentDistance(score->getCurrentDistance() + 1);

	if (score->getCurrentDistance() > score->getBest())
		score->setBest(score->getCurrentDistance());
}

//-------------------------------------------------------------------------
// TODO: Make the calculation more complex!!!!!
//-------------------------------------------------------------------------

 void RectWorld :: addTarget()
{

	static float actualDuration = 4.0f;
	static int times = 0;
	times ++;

	int top = 640;
	int bottom = 0;

	int topRectSize = 0;
	int bottomRectSize = 0;

	//if (times > 100)
	//{
	//	actualDuration -= 0.5f;
	//	times = 0;
	//}

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

	barrier->setTag(9);
	
	if(barrier->getContentSize().height < 150)
		barrier->setScaleY(150.0f / barrier->getContentSize().height);

	int count = _barriers->count();

	int initialX = (float) winSize.width - barrier->getContentSize().width / 2 + 600 ;
	int initialY = winSize.height * ( rand() % 641 ) / 641 - barrier->getContentSize().height / 2 ;

	if(initialY < barrier->getContentSize().height / 2 )
		initialY  = barrier->getContentSize().height / 2;

	if (initialY + barrier->getContentSize().height / 2 <= 320)
	{
		bottom += initialY + barrier->getContentSize().height / 2;
		bottomRectSize = barrier->getContentSize().height;
	}
	else
	{
		top -= (640 - initialY + barrier->getContentSize().height / 2);
		topRectSize = barrier->getContentSize().height;
	}

	barrier->setPosition(ccp(initialX, initialY));
	this->addChild(barrier, 1);
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

		barrierSecond->setTag(9);

		if(barrierSecond->getContentSize().height < 150)
			barrierSecond->setScaleY(150.0f / barrierSecond->getContentSize().height);

		initialY = winSize.height * ( 1 - rand() % 151 / 300 ) - barrierSecond->getContentSize().height / 2;

		if (initialY - barrierSecond->getContentSize().height / 2  - barrier->getPosition().y - barrier->getContentSize().height / 2 < 180)
			initialY = barrier->getPosition().y + barrier->getContentSize().height / 2 + 180 + barrierSecond->getContentSize().height / 2;

		barrierSecond->setPosition(ccp(initialX, initialY));
		this->addChild(barrierSecond, 1);
		_barriers->addObject(barrierSecond);

		actionMove = CCMoveTo::actionWithDuration((ccTime)actualDuration, ccp(0 - barrierSecond->getContentSize().width / 2, initialY));

		barrierSecond->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));

		top -= (640 - initialY + barrierSecond->getContentSize().height / 2);

		topRectSize = barrierSecond->getContentSize().height;
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

		barrierSecond->setTag(9);

		if(barrierSecond->getContentSize().height < 150)
			barrierSecond->setScaleY(150.0f / barrierSecond->getContentSize().height);

		initialY = winSize.height * ( rand() % 151 / 300 ) - barrierSecond->getContentSize().height / 2;

		if(initialY <= barrierSecond->getContentSize().height / 2)
			initialY = barrierSecond->getContentSize().height / 2;

		if (barrier->getPosition().y - barrier->getContentSize().height / 2 - initialY - barrierSecond->getContentSize().height / 2 < 180)
			initialY = barrier->getPosition().y - barrier->getContentSize().height / 2 - 180 - barrierSecond->getContentSize().height / 2;

		barrierSecond->setPosition(ccp(initialX, initialY));
		this->addChild(barrierSecond, 1);
		_barriers->addObject(barrierSecond);

		actionMove = CCMoveTo::actionWithDuration((ccTime)actualDuration, ccp(0 - barrierSecond->getContentSize().width / 2, initialY));

		barrierSecond->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));

		bottom += initialY + barrierSecond->getContentSize().height / 2;

		bottomRectSize = barrierSecond->getContentSize().height;
	}

	if (rand() % 256 > 128 )
	{
		CCSprite *star = CCSprite :: spriteWithFile("star.png");

		if (top - bottom < star->getContentSize().height + 10)
			return;
		
		int starY;
		int starX;

		star->setTag(10);

		starX = initialX;

		starY = (top + bottom) / 2 - 10;

		if (starY + star->getContentSize().height / 2 > top )
		{
			if (640 - top - topRectSize > star->getContentSize().height + 10)
			{
				starY = (1280 - top - topRectSize) / 2;
			}
			else
				return;
		}
		else if(starY - star->getContentSize().height / 2 < bottom)
		{
			if(bottom - bottomRectSize - 0 > star->getContentSize().height + 50)
			{
				starY = (bottom - bottomRectSize - 0) / 2;
			}
			else
				return;
		}



		star->setPosition(ccp(starX, starY));

		actionMove = CCMoveTo::actionWithDuration((ccTime)actualDuration, ccp(0 - star->getContentSize().width / 2, starY));

		star->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));

		_stars->addObject(star);

		this->addChild(star, 1);

	}
}

void RectWorld :: spriteMoveFinished(CCNode* sender)
{
	CCSprite *object = (CCSprite*)sender;
	this->removeChild(object, true);

	if(object->getTag() == 9)
		_barriers->removeObject(object);
	else if(object->getTag() == 10)
		_stars->removeObject(object);
}

void RectWorld :: gameLogic(ccTime dt)
{	
	if (_gameOver)
		return;
	this->addTarget();
}


void RectWorld :: setType(int type)
{
	_type = type;
}

void RectWorld :: clockPassBy(ccTime dt)
{
	TimeLayer *timeLayer = (TimeLayer*)this->getChildByTag(4);

	if(timeLayer != NULL)
	{
		if (timeLayer->decreaseRestTime())
			gameOver();
	}
}

void RectWorld::pauseResumePressed()
{
	TimeCount *timeCount = (TimeCount *)this->getChildByTag(30);
	timeCount->continueCount();

	this->resumeSchedulerAndActions();

	CCMenu *pItem = (CCMenu *)this->getChildByTag(6);
	pItem->setIsVisible(true);

	ScoreLayer *scoreLayer = (ScoreLayer *)this->getChildByTag(2);
	scoreLayer->setIsVisible(true);

	if (_type == 3)
	{
		TimeLayer *timeLayer = (TimeLayer*)this->getChildByTag(4);
		timeLayer->setIsVisible(true);
	}

	CCMutableArray<CCSprite *> :: CCMutableArrayIterator it;

	for(it = _barriers->begin(); it != _barriers->end(); it++)
	{
		(*it)->resumeSchedulerAndActions();
	}

	for(it = _stars->begin(); it != _stars->end(); it++)
	{
		(*it)->resumeSchedulerAndActions();
	}

	_gameOver = false;
}

void RectWorld :: removeObjects(ccTime dt)
{
	Warning *warning = (Warning*)this->getChildByTag(20);
	if (warning->getIsVisible())
	{
		CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration((ccTime)1.0f, ccp(0, 0));
		CCFiniteTimeAction* deleteWarning = CCCallFuncN::actionWithTarget(this, callfuncN_selector(RectWorld::removeWarning));
		this->runAction(CCSequence::actions(actionMove, deleteWarning, NULL));
	}
}

void RectWorld :: removeWarning(CCNode* sender)
{
	//CCSprite *object = (CCSprite*)sender;
	//this->removeChild(object, true);
	Warning *warning = (Warning*)this->getChildByTag(20);
	warning->setIsVisible(false);

}

void RectWorld::gameOver()
{
	TimeCount *timeCount = (TimeCount *)this->getChildByTag(30);
	
	timeCount->stopCount();

	ScoreLayer *scores = (ScoreLayer *)this->getChildByTag(2);
	
	DataCore::sharedCore()->finishAGameWithScore(scores->getCurrentDistance(), kWorldRect, kTimeTrial);
	DataCore::sharedCore()->addTotalDistance(scores->getCurrentDistance());
	DataCore::sharedCore()->addTotalStar(scores->getCurrentStar());
	DataCore::sharedCore()->addTotalTime(timeCount->getTime());

	_gameOver = true;

	this->pauseSchedulerAndActions();

	CCMutableArray<CCSprite*> :: CCMutableArrayIterator it;

	for(it = _barriers->begin(); it != _barriers->end(); it++)
	{
		(*it)->pauseSchedulerAndActions();

	}

	for(it = _stars->begin(); it != _stars->end(); it++)
	{
		(*it)->pauseSchedulerAndActions();
	}
	
	GameOver *gameEnd = GameOver::node();
	gameEnd->setDelegate(this);

	CCMenu *pItem = (CCMenu *)this->getChildByTag(6);
	pItem->setIsVisible(false);

	
	ScoreLayer *scoreLayer = (ScoreLayer *)this->getChildByTag(2);
	scoreLayer->setIsVisible(false);

	ScoreLayer *score = (ScoreLayer*)this->getChildByTag(2);

	char buffer[8];

	itoa(score->getCurrentDistance(), buffer, 10);
	gameEnd->setItem1Descriptor(buffer);

	itoa(score->getCurrentStar(), buffer, 10);
	gameEnd->setItem2Descriptor(buffer);

	if (_type == 3)
	{
		TimeLayer *timeLayer = (TimeLayer*)this->getChildByTag(4);
		timeLayer->setIsVisible(false);
	}

	this->addChild(gameEnd,4);
}

void RectWorld :: setDelegate(BtnProtocal * delegate)
{
	_delegate = delegate;
}

void RectWorld :: pauseRestartPressed()
{
	_delegate->pauseRestartPressed();
	this->removeFromParentAndCleanup(true);
}