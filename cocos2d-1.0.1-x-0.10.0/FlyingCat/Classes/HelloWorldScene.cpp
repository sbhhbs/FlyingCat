#include "HelloWorldScene.h"
#include "MovingBackground.h"
#include "Cat1.h"

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

        // add layer as a child to scene
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

		MovingBackground *bk = MovingBackground::node();

		this->addChild(bk);



		Cat1* cat1 = Cat1::node();

		this->addChild(cat1);

		cat1->setPosition(ccp(500,500));
		cat1->flyUpAnimation();
		cat1->setTag(1);

		//this->setIsTouchEnabled(true);

		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);

        bRet = true;
    } while (0);

    return bRet;
}

bool HelloWorld::ccTouchBegan( CCTouch *pTouch,CCEvent *pEvent )
{
	static int i = 0;
	i++;

	Cat1 *cat = (Cat1*) this->getChildByTag(1);
	if(i % 2)
		cat->flyDownAnimation();
	else
		cat->flyUpAnimation();
	return true;
}
