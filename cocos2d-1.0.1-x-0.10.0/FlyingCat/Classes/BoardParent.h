// @ Author: Trine
// @ Last Modified : 2012/1/30

#ifndef _BOARD_PARENT_H_
#define _BOARD_PARENT_H_

#include "cocos2d.h"
#include "BtnProtocal.h"
#include "Board.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class BoardParent : public CCLayerColor
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend to return the exactly class pointer
	static cocos2d::CCScene* scene();

	virtual void setItem1Descriptor(std::string);

	virtual void setItem2Descriptor(std::string);

	virtual void button1Func(CCObject*);

	virtual void button2Func(CCObject*);

	void setDelegate(BtnProtocal *iamadelegate);
	// implement the "static node()" method manually

	LAYER_NODE_FUNC(BoardParent);
	
protected:
	BtnProtocal   *_delegate;

};

#endif