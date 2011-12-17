#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class MovingBackground : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	void update(ccTime dt);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(MovingBackground);
protected:
	CCSprite *_background;
};
