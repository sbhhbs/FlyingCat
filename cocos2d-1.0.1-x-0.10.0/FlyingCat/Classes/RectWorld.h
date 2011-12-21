#ifndef __RECTORLD_SCENE_H__
#define __RECTORLD_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class RectWorld : public cocos2d::CCLayer
{
public:
	RectWorld();
	~RectWorld();

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_NODE_FUNC(RectWorld);

	virtual void ccTouchEnded(CCTouch*, CCEvent*);
	virtual bool ccTouchBegan(CCTouch*, CCEvent*);
	virtual void update(ccTime);

	void addTarget();

	void spriteMoveFinished(CCNode*); 

	void gameLogic(ccTime);


protected:
	CCSprite* _player;
	CCMutableArray<CCSprite*> *_barriers;
	CCParticleSystem* _particle;

	int _flyState;
	int _speed;
};

#endif  // __HELLOWORLD_SCENE_H__