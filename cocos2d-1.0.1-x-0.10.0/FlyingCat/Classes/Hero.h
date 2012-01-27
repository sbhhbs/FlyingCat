#pragma once

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "Cat1.h"

#ifndef PTM_RATIO
#define PTM_RATIO   32.0
#endif

#define NUM_PREV_VELS   5

USING_NS_CC;

class Hero: public CCSprite
{
public:
	b2World *_world;
	b2Body *_body;
	bool _awake;
	b2Vec2 _prevVels[NUM_PREV_VELS];
	int _nextVel;

	void wake();
	void dive();
	void limitVelocity();

	Cat1 * cat;

	bool initWithWorld(b2World * world);

	void update();
	void createBody();
};

