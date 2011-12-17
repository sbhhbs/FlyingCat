#pragma once
#include "BaseCat.h"
class Cat1 : public BaseCat
{
public:

	virtual bool init();

	LAYER_NODE_FUNC(Cat1);

	//play some animation here
	virtual void flyUpAnimation();
	virtual void flyDownAnimation();
	virtual void crashOnAWallAnimation();
	virtual void deadAnimation();

	//Physics related
	virtual b2Vec2* getShape();
	virtual float getDensity();
	virtual float getFriction();
	virtual float getRestitution();

private:
	CCSprite *body;
	CCSprite *foreWing;
	CCSprite *backWing;
};