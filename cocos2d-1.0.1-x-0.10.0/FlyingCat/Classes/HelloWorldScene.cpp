#include "HelloWorldScene.h"
#include "MovingBackground.h"
#include "Cat1.h"
#include "RectWorld.h"
#include "ScoreLayer.h"
#include "DataCore.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::node();
        CC_BREAK_IF(! layer);

        // add layer as a ch ild to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

		RectWorld *rectWorld = RectWorld::node();
		rectWorld->setTag(3);

		rectWorld->setDelegate(this);

		this->addChild(rectWorld, 0);


		Cat1* cat1 = Cat1::node();

		cat1->setPosition(ccp(200,200));
		cat1->flyDownAnimation(); 
		cat1->setTag(1);

		rectWorld->addChild(cat1, 2);
		 

		ScoreLayer *scores = ScoreLayer::node();
		scores->setTag(2);
		scores->appear();

		rectWorld->addChild(scores, 3);
		//this->setIsTouchEnabled(true);

		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);

        bRet = true;
    } while (0);

    return bRet;
}

bool HelloWorld::ccTouchBegan( CCTouch *pTouch,CCEvent *pEvent )
{
	/*Cat1 *cat = (Cat1*) this->getChildByTag(1);

	ScoreLayer *scores = (ScoreLayer*) this->getChildByTag(2);
	if(i % 2)
	{
		cat->flyDownAnimation();
		
	}
	else
	{
		cat->flyUpAnimation();
		scores->disappear();
	}*/
	   
	RectWorld* rectWorld = (RectWorld*)this->getChildByTag(3);

	if (rectWorld != NULL)
	{
		rectWorld->ccTouchBegan(pTouch, pEvent);
	}

	return true;
}


void HelloWorld :: ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	RectWorld* rectWorld = (RectWorld*)this->getChildByTag(3);

	if (rectWorld != NULL)
	{
		rectWorld->ccTouchEnded(touch, event);
	}

}

void HelloWorld :: pauseRestartPressed()
{

	RectWorld *rectWorld = RectWorld::node();
	rectWorld->setTag(3);

	rectWorld->setDelegate(this);

	this->addChild(rectWorld, 0);


	Cat1* cat1 = Cat1::node();

	cat1->setPosition(ccp(200,200));
	cat1->flyDownAnimation(); 
	cat1->setTag(1);

	rectWorld->addChild(cat1, 2);


	ScoreLayer *scores = ScoreLayer::node();
	scores->setTag(2);
	scores->appear();
	scores->setBest(DataCore::sharedCore()->getBestScoreFor(kWorldRect, kTimeTrial));

	rectWorld->addChild(scores, 3);
}