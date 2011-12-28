#ifndef __RECTORLD_SCENE_H__
#define __RECTORLD_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
#include "BtnProtocal.h"

using namespace cocos2d;

class RectWorld : public cocos2d::CCLayerColor, public BtnProtocal
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
    virtual void menuPause(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_NODE_FUNC(RectWorld);

	virtual void ccTouchEnded(CCTouch*, CCEvent*);
	virtual bool ccTouchBegan(CCTouch*, CCEvent*);
	virtual void update(ccTime);

	void addTarget();

	void spriteMoveFinished(CCNode*); 

	void gameLogic(ccTime);

	void setType(int);

	void clockPassBy(ccTime);

	virtual void pauseResumePressed();
protected:
	CCMutableArray<CCSprite*> *_barriers;
	CCMutableArray<CCSprite*> *_stars;
	bool _gameOver;
	bool _running;
	int _flyState;
	int _type;
	float _gravityAccelerate;
	float _motiveAccelerate;
	float _currentSpeed;
};

#endif  // __HELLOWORLD_SCENE_H__