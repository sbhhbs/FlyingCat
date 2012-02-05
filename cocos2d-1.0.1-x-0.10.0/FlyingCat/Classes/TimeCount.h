#pragma once

#include "cocos2d.h"
#include "BtnProtocal.h"

USING_NS_CC;

using namespace cocos2d;

class TimeCount : public cocos2d::CCLayer
{
public:
	TimeCount();

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	void increaseTime(ccTime);

	void setDelegate(BtnProtocal *);

	long getTime();

	void stopCount();

	void continueCount();

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(TimeCount);
protected:
	long _time;
	bool _stop;
	BtnProtocal *_delegate;
};
