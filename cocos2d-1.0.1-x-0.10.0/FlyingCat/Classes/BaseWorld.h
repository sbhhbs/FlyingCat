#pragma once

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class BaseWorld : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	//static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	//LAYER_NODE_FUNC(BaseWorld);


	virtual void enterDemo() = 0;			// 当未进入游戏时候时的主界面的背景
	virtual void enterGaming() = 0;			// 游戏开始以及开始之后的界面显示
	virtual void enterPausing() = 0;		// 游戏暂停时的界面显示
	virtual void resume() = 0;			    // 恢复游戏状态

};
