#ifndef __ACHIVEMENT_CORE_H__
#define __ACHIVEMENT_CORE_H__
#include "AchievementList.h"
#include "cocos2d.h"
#include <queue>
#define MAX_ACHIEVEMENT_COUNT 2

USING_NS_CC;

class AchivementCore
{
public:
	void setLayer(CCLayer* currentLayer);
	static AchivementCore* sharedCore();
	void forceUpdate();
	void update();
	int getDoneAchievementCount();
	int getTotalAchievementCount();
	BaseAchivement* getAchievementInstance(int count);
	void mycleanup(CCNode *sender);
private:
	AchivementCore();
	~AchivementCore();
	CCLayer *layer;
	static AchivementCore* _instance;
	BaseAchivement* _achievementList[MAX_ACHIEVEMENT_COUNT];
	bool lastStatus[MAX_ACHIEVEMENT_COUNT];
	std::queue<BaseAchivement*> toshowList;
};

#endif //__ACHIVEMENT_CORE_H__