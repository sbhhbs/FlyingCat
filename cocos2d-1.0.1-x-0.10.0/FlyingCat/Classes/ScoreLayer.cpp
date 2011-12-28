#include "ScoreLayer.h"


// on "init" you need to initialize your instance
bool ScoreLayer::init()
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


		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		bestLabel = CCLabelBMFont::labelWithString("Best:0","Bigfnt.fnt");
		starLabel = CCLabelBMFont::labelWithString("Star:0","Bigfnt.fnt");
		distanceLabel = CCLabelBMFont::labelWithString("Distance:0","Bigfnt.fnt");
		
		
		bestLabel->setAnchorPoint(ccp(1.0f,1.0f));
		bestLabel->setPosition(ccp(winSize.width,0));

		starLabel->setAnchorPoint(ccp(0.0f,0.0f));
		starLabel->setPosition(ccp(0,winSize.height));

		distanceLabel->setAnchorPoint(ccp(1.0f,0.0f));
		distanceLabel->setPosition(ccp(winSize.width,winSize.height));


		bestLabel->setScale(0.5f);
		starLabel->setScale(0.5f);
		distanceLabel->setScale(0.5f);


		this->addChild(bestLabel);
		this->addChild(starLabel);
		this->addChild(distanceLabel);



		bRet = true;
	} while (0);

	return bRet;
}

void ScoreLayer::setBest( long bestScore )
{
	best = bestScore;
	char buffer[64];
	sprintf(buffer,"Best: %d",best);
	bestLabel->setString(buffer);
}

void ScoreLayer::setCurrentStar( long star )
{
	currentStar = star;
	char buffer[64];
	sprintf(buffer,"Stars: %d",star);
	starLabel->setString(buffer);
}

void ScoreLayer::setCurrentDistance( long distance )
{
	currentDistance = distance;
	char buffer[64];
	sprintf(buffer,"Distance: %d",distance);
	distanceLabel->setString(buffer);
}

void ScoreLayer::appear()
{
	float animationTime = 0.25f;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	starLabel->runAction(
		CCEaseBounceOut::actionWithAction(
			CCMoveTo::actionWithDuration(animationTime,ccp(0,winSize.height - starLabel->getContentSize().height * starLabel->getScale()))
		
		)		
		);
	bestLabel->runAction(
		CCEaseBounceOut::actionWithAction(
		CCMoveTo::actionWithDuration(animationTime,ccp(winSize.width,bestLabel->getContentSize().height  * bestLabel->getScale()))

		)		
		);

	distanceLabel->runAction(
		CCEaseBounceOut::actionWithAction(
		CCMoveTo::actionWithDuration(animationTime,ccp(winSize.width,winSize.height - distanceLabel->getContentSize().height * distanceLabel->getScale()))

		)		
		);

}

void ScoreLayer::disappear()
{
	float animationTime = 0.25f;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	starLabel->runAction(
		CCEaseBounceOut::actionWithAction(
		CCMoveTo::actionWithDuration(animationTime,ccp(0,winSize.height))

		)		
		);
	bestLabel->runAction(
		CCEaseBounceOut::actionWithAction(
		CCMoveTo::actionWithDuration(animationTime,ccp(winSize.width,0))

		)		
		);

	distanceLabel->runAction(
		CCEaseBounceOut::actionWithAction(
		CCMoveTo::actionWithDuration(animationTime,ccp(winSize.width,winSize.height))

		)		
		);

}


long ScoreLayer :: getCurrentDistance()
{
	return currentDistance;
}

long ScoreLayer ::getCurrentStar()
{
	return currentStar;
}

long ScoreLayer :: getBest()
{
	return best;
}

ScoreLayer :: ScoreLayer()
{
	currentStar = 0;
	currentDistance = 0;
	best = 0;
}

