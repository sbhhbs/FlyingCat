#pragma once

#include "cocos2d.h"
#include "Box2D.h"

USING_NS_CC;

class BaseCat : public cocos2d::CCSprite
{
public:
	//play some animation here
	void flyUpAnimation() = 0;
	void flyDownAnimation() = 0;
	void crashOnAWallAnimation() = 0;
	void deadAnimation() = 0;
	

	//If you want to update something.
	//rewrite this.
	void update(ccTime dt) = 0;
	

	//Physics related
	b2Vec2[] getShape() = 0;
	float getDensity() = 0;
	float getFriction() = 0;
	float getRestitution() = 0;
	
};