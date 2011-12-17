#include "MovingBackground.h"
#include "cocos2d.h"

using namespace cocos2d;


CCScene* MovingBackground::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MovingBackground *layer = MovingBackground::node();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MovingBackground::init()
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

		_background = CCSprite::spriteWithFile("bk.png");

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		_background->setPosition(ccp(winSize.width/2, winSize.height/2));       
		ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
		_background->getTexture()->setTexParameters(&tp);

		this->addChild(_background);

		this->scheduleUpdate();

		bRet = true;
	} while (0);

	return bRet;
}

void MovingBackground::update( ccTime dt )
{
	
	float PIXELS_PER_SECOND = 70;
	static float offset = 0;
	offset += PIXELS_PER_SECOND * dt;

	CCSize textureSize = _background->getTextureRect().size;
	_background->setTextureRect(CCRectMake(offset, 0, textureSize.width, textureSize.height));
	
}
