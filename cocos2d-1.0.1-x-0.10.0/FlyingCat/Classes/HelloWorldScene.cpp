#include "HelloWorldScene.h"
#include "MovingBackground.h"
#include "Cat1.h"
#include "ScoreLayer.h"
#include "TinyWing.h"

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

		TinyWing * tinyWing = TinyWing::node();

		this->addChild(tinyWing);

        bRet = true;
    } while (0);

    return bRet;
}

bool HelloWorld::ccTouchBegan( CCTouch *pTouch,CCEvent *pEvent )
{
	static int i = 0;
	i++;

	Cat1 *cat = (Cat1*) this->getChildByTag(1);

	ScoreLayer *scores = (ScoreLayer*) this->getChildByTag(2);
	if(i % 2)
	{
		cat->flyDownAnimation();
		scores->appear();
	}
	else
	{
		cat->flyUpAnimation();
		scores->disappear();
	}
	return true;
}
