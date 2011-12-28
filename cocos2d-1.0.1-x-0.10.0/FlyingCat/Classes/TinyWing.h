#pragma once

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "Terrain.h"
#include "Hero.h"


#define PTM_RATIO   32.0

USING_NS_CC;

class TinyWing : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    void update(ccTime dt);

    // implement the "static node()" method manually
    LAYER_NODE_FUNC(TinyWing);

	b2World * _world;
	Terrain * terrain;
	void setupWorld();
	void createTestBodyAtPostition(CCPoint position);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) ;
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;

	bool _tapDown;
	Hero * _hero;
};

