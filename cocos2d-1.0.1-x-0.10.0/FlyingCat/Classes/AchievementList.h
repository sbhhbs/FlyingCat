#ifndef __ACHIVEMENT_LIST_H__
#define __ACHIVEMENT_LIST_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class BaseAchivement
{
public:
	BaseAchivement();
	virtual bool isDone();
	virtual string getLockInfo() = 0;
	virtual string getLockTitle();
	virtual string getUnlockInfo() = 0;
	virtual string getUnlockTitle() = 0;
	virtual string getUnlockImagePath() = 0;
	virtual string getLockImagePath();
	virtual void forceLock();
	virtual void check() = 0;
protected:
	bool done;
	string storename;
};

class Achievement_Flying10000 : public BaseAchivement
{
public:
	Achievement_Flying10000();
	virtual string getLockInfo();
	virtual string getLockTitle();
	virtual string getUnlockInfo();
	virtual string getUnlockTitle();
	virtual string getUnlockImagePath();
	virtual string getLockImagePath();
	virtual void check();
};

class Achievement_Stars100 : public BaseAchivement
{
public:
	Achievement_Stars100();
	virtual string getLockInfo();
	virtual string getLockTitle();
	virtual string getUnlockInfo();
	virtual string getUnlockTitle();
	virtual string getUnlockImagePath();
	virtual string getLockImagePath();
	virtual void check();
};

#endif //__ACHIVEMENT_LIST_H__