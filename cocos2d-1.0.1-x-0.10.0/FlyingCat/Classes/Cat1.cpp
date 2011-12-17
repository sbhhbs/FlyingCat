#include "Cat1.h"


bool Cat1::init()
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

		body = CCSprite::spriteWithFile("cat1-body.png");
		
		foreWing = CCSprite::spriteWithFile("cat1-wing.png");
		backWing = CCSprite::spriteWithFile("cat1-wing.png");

		foreWing->setAnchorPoint(ccp(1.0f,0.2f));
		backWing->setAnchorPoint(ccp(1.0f,0.2f));

		foreWing->setPosition(ccp(20,-10));
		backWing->setPosition(ccp(35,-10));


		this->addChild(backWing);
		this->addChild(body);
		this->addChild(foreWing);
		this->setAnchorPoint(ccp(0,0));

		bRet = true;
	} while (0);

	return bRet;
}

void Cat1::flyUpAnimation()
{
	float animationTime = 0.25f;
	this->runAction(CCRotateTo::actionWithDuration(animationTime,-20));
	foreWing->runAction(CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(CCRotateTo::actionWithDuration(animationTime,20),CCRotateTo::actionWithDuration(animationTime,0))));
	backWing->runAction(CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(CCRotateTo::actionWithDuration(animationTime,20),CCRotateTo::actionWithDuration(animationTime,0))));
}

void Cat1::flyDownAnimation()
{

	float animationTime = 0.25f;
	this->runAction(CCRotateTo::actionWithDuration(animationTime,20));
	foreWing->stopAllActions();
	backWing->stopAllActions();
	foreWing->runAction(CCRotateTo::actionWithDuration(animationTime,0));
	backWing->runAction(CCRotateTo::actionWithDuration(animationTime,0));

}

void Cat1::crashOnAWallAnimation()
{

}

void Cat1::deadAnimation()
{

}


float Cat1::getDensity()
{
	return 0.5f;
}

float Cat1::getFriction()
{
	return 0.1f;
}

float Cat1::getRestitution()
{
	return 0.5f;
}

b2Vec2* Cat1::getShape()
{
	return NULL;
}

