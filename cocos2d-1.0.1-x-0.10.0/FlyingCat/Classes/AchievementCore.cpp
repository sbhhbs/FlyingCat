#include "AchievementCore.h"
#include "cocos2d.h"
#include "PixelRatio.h"
USING_NS_CC;

AchivementCore::AchivementCore()
{
	layer = NULL;

	_achievementList[0] = new Achievement_Flying10000();
	_achievementList[1] = new Achievement_Stars100();

	for(int i = 0; i < MAX_ACHIEVEMENT_COUNT ; i++)
	{
		lastStatus[i] = _achievementList[i]->isDone();
	}
}

void AchivementCore::setLayer( CCLayer* currentLayer )
{
	layer = currentLayer;
}

AchivementCore* AchivementCore::sharedCore()
{
	if(!_instance)
	{
		_instance = new AchivementCore();
	}
	return _instance;
}

void AchivementCore::update()
{
	static int count = 0;
	count++;
	if(count<50) 
		return;
	count = 0;
	for(int i = 0; i < MAX_ACHIEVEMENT_COUNT ; i++)
	{
		_achievementList[i]->check();
		if(_achievementList[i]->isDone() && lastStatus[i] == false)
		{
			lastStatus[i] = true;
			toshowList.push(_achievementList[i]);
		}
	}
	if(!toshowList.empty())
	{
		if(layer)
		{
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			CCSprite *bk = CCSprite::spriteWithFile("new_ac_bar.png");
			bk->setAnchorPoint(ccp(0.5,0));
			bk->setPosition(ccp(winSize.width / 2, winSize.height));
			bk->runAction(
				CCSequence::actions(
				CCMoveBy::actionWithDuration(0.2f,ccp(0,-bk->getContentSize().height ))
				,
				CCDelayTime::actionWithDuration(5.0f)
				,
				CCMoveBy::actionWithDuration(0.2f,ccp(0,bk->getContentSize().height ))
				,
				CCCallFuncN::actionWithTarget(layer,callfuncN_selector(AchivementCore::mycleanup))
				,
				NULL
				)
			);
			layer->addChild(bk);

			BaseAchivement* achieve = toshowList.front();
			toshowList.pop();
			CCLabelTTF* info = CCLabelTTF::labelWithString(achieve->getUnlockTitle().c_str(),"xx",15 * SCREEN_RATIO);
			info->setAnchorPoint(ccp(0.5,0));
			info->setColor(ccc3(0,0,0));
			info->setPosition(ccp(winSize.width / 2, winSize.height + info->getContentSize().height));
			info->runAction(
				CCSequence::actions(
				CCMoveBy::actionWithDuration(0.2f,ccp(0,-bk->getContentSize().height - 10 * SCREEN_RATIO))
				,
				CCDelayTime::actionWithDuration(5.0f)
				,
				CCMoveBy::actionWithDuration(0.2f,ccp(0,bk->getContentSize().height + 10 * SCREEN_RATIO))
				,
				CCCallFuncN::actionWithTarget(layer,callfuncN_selector(AchivementCore::mycleanup))
				,
				NULL
				)
				);
			layer->addChild(info);
		}
	}
}

int AchivementCore::getDoneAchievementCount()
{
	int result = 0;
	for(int i = 0; i < MAX_ACHIEVEMENT_COUNT ; i++)
	{
		if(_achievementList[i]->isDone())
			result++;
	}
	return result;
}

int AchivementCore::getTotalAchievementCount()
{
	return MAX_ACHIEVEMENT_COUNT;
}

BaseAchivement* AchivementCore::getAchievementInstance( int count )
{
	assert(count >= 0);
	assert(count < MAX_ACHIEVEMENT_COUNT);
	return _achievementList[count];
}

void AchivementCore::forceUpdate()
{
	for(int i = 0; i < MAX_ACHIEVEMENT_COUNT ; i++)
	{
		(_achievementList[i])->forceLock();
		lastStatus[i] = false;
	}
}

AchivementCore::~AchivementCore()
{
	for(int i = 0; i < MAX_ACHIEVEMENT_COUNT ; i++)
	{
		delete _achievementList[i];
	}
}

void AchivementCore::mycleanup( CCNode *sender )
{
	sender->removeFromParentAndCleanup(true);
}

AchivementCore* AchivementCore::_instance = NULL;
