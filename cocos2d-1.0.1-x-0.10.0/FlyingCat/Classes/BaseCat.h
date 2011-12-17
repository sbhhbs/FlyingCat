#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class BaseCat : public CCLayer
{
public:
	//play some animation here
	virtual void flyUpAnimation() = 0;
	virtual void flyDownAnimation() = 0;
	virtual void crashOnAWallAnimation() = 0;
	virtual void deadAnimation() = 0;
	
	//Physics related
	virtual b2Vec2* getShape() = 0;
	virtual float getDensity() = 0;
	virtual float getFriction() = 0;
	virtual float getRestitution() = 0;
	
};