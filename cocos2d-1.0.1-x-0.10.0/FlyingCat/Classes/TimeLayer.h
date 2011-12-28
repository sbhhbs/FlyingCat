#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TimeLayer : public cocos2d::CCLayer
{
public:
	TimeLayer();

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	
	bool decreaseRestTime();
	bool decreaseCollisionTime();
	void setInitalTime(long);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(TimeLayer);
protected:
	bool _clockTick;
	long _initialTime;
	long _restTime;
	int _collisionUnitTime;
	CCLabelBMFont *_timeLabel;
};
